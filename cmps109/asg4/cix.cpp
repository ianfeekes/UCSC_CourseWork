// $Id: cix.cpp,v 1.6 2018-07-26 14:18:32-07 - - $

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

/*THESE TWO INCLUDES ARE ADDED*/ 
#include<fstream>
#include<sstream>

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "protocol.h"
#include "logstream.h"
#include "sockets.h"

using wordvec = vector<string>; 

logstream log (cout);
struct cix_exit: public exception {};

/*This recognizes the first word a user enters in a line from cin and
 *maps it to a cix_command for processing purposes*/ 
unordered_map<string,cix_command> command_map {
   {"exit", cix_command::EXIT},
   {"help", cix_command::HELP},
   {"ls"  , cix_command::LS  },
   {"get" , cix_command::GET }, 
   {"put" , cix_command::PUT }, 
   {"rm"  , cix_command::RM  }
};

static const string help = R"||(
exit         - Exit the program.  Equivalent to EOF.
get filename - Copy remote file to local host.
help         - Print help summary.
ls           - List names of files on remote server.
put filename - Copy local file to remote host.
rm filename  - Remove file from remote server.
)||";

/*String processing function taken directly from asg2, it splits the
 *string (which in this program is a line) into a wordvec based on 
 *delimiters, which for this usage is the whitespace ' ' character*/ 
wordvec split (const string& line, const string& delimiters) {
   wordvec words;
   size_t end = 0;
   for (;;) {
      size_t start = line.find_first_not_of (delimiters, end);
      if (start == string::npos) break;
      end = line.find_first_of (delimiters, start);
      words.push_back (line.substr (start, end - start));
   }
   /*Only added logic from asg2: makes sure that after tokenizing the
    *line, it should only contain a wordvec of at maximum a 
    *cix_command and a filename*/  
   if(words.size()>2)
   {
      log << line << ": invalid command" << endl;
   }
   return words;
}

//calls library functions to turn an input file into a string
string fileToString(const ifstream& file)
{
   stringstream temp; 
   temp<<file.rdbuf();
   string toReturn = temp.str(); 
   return toReturn; 
}

/*Help has already been implemented for us. It simply spews out the
 *giant string above*/ 
void cix_help() {
   cout << help;
}

/*ls has already been done for us, it largely serves as a model for 
 *the other three functions we need to implement as they are all very
 *similar*/ 
void cix_ls (client_socket& server) {
   cix_header header;
   header.command = cix_command::LS;
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.command != cix_command::LSOUT) {
      log << "sent LS, server did not return LSOUT" << endl;
      log << "server returned " << header << endl;
   }else {
      char buffer[header.nbytes + 1];
      recv_packet (server, buffer, header.nbytes);
      log << "received " << header.nbytes << " bytes" << endl;
      buffer[header.nbytes] = '\0';
      cout << buffer;
   }
}

/*This function copies a local file into the socket (server) and 
 *causes the remote server to create or overwrite that file in its
 *directory.
 * It first initializes the header with the proper fields
 *and memset. It then checks for files in the local directory, and
 *prints a message indicating failure if the specified file does not
 *work. Else it takes in the file's contents, closes the file, 
 *allocates nbytes, and sends the header and payload packets. Lastly, 
 *it verifies that the request was successfully completed and logs*/ 
void cix_put(client_socket& server, const string& filename)
{
   //Create the header and clear the struct for memory allocation 
   cix_header header; 
   memset(&header, 0, sizeof(header)); 
   //Give the header the proper command field
   header.command = cix_command::PUT; 
   snprintf(header.filename, filename.length()+1, filename.c_str());
   //Initialize the input file
   ifstream in(header.filename);
   //if the file exists 
   if(in.is_open())
   {
      //calls new function to transfer the input file into a string
      string str = fileToString(in); 
      in.close(); 
      header.nbytes = str.size(); 
      log<<"sending header: "<<header<<endl; 
      //Send header to invoke server's put function
      send_packet(server, &header, sizeof(header)); 
      //Send payload
      send_packet(server, &str, header.nbytes);
      //Takes in packet response of server indicating success
      recv_packet(server, &header, sizeof(header)); 
      log<<"received header: "<<header<<endl; 
      /*ACK command response indicates that the request was 
       *successfuly completed. If it does not return ACK, we want to
       *write a message indicating this*/    
      if(header.command==cix_command::ACK)
      {
         log<<"File has been added to server: ACK response"<<endl;
      }
      else
      {
         /*These errors are sent to log and not cerr to follow the 
          *behavior of the cix_ls function - we are assuming that all
          *the functions should behave the same, even with their error
          *messages*/   
         log<<"Failure to add file to server: NAK response"<<endl; 
      }
   }
   else //if the file does not exist log a message indicating this
   {
      cerr<<"Error "<<header.filename<<": file not found" <<endl;
   }

}

/*Requests a file from the server, who's name is used both remotely 
 *and locally. */ 
void cix_get(client_socket& server, const string& filename)
{
   //First allocates proper header fields
   cix_header header; 
   memset(&header, 0, sizeof(header));  
   snprintf(header.filename, filename.length()+1, filename.c_str()); 
   header.command = cix_command::GET; 
   //Sends and receives header
   log<<"Sending header:  "<<header<<endl; 
   send_packet(server, &header, sizeof(header));
   recv_packet(server, &header, sizeof(header)); 
   log<<"Header received: "<<header<<endl; 
   //We only want to write a new local file if FILE response returned
   if(header.command == cix_command::FILE)
   {  
      //the payload length is the number of bytes sent in the payload
      char buffer[header.nbytes+1]; 
      recv_packet(server, buffer, header.nbytes); 
      log<<"Packet received: "<<header.nbytes<<" bytes of data"<<endl;
      /*The file contents must be terminated by a null character for
       *processing purposes before the file is written*/    
      buffer[header.nbytes]='\0'; 
      //create a file writer, write to the file, and close it
      ofstream out(filename);
      out.write(buffer, header.nbytes); 
      out.close(); 
   }
   /*If the get command does not receive a FILE response, log and 
    *throw complaints indicating this */   
   else 
   {
      /*Likewise, complaints are sent to log in this case, not cerr*/
      log <<"Failure for server to return FILE." <<endl; 
   }
}

/*Request to remove a file. Payload length is 0
 *Sets up the header with the proper fields, sends a packet to the
 *remote server, receives it, and the server should handle its 
 *removal. Logs message indicating success/failure of server's 
 *attempt to remove the file */ 
void cix_rm(client_socket& server, const string& filename)
{
   //sets the header and allocates memset
   cix_header header; 
   memset(&header, 0, sizeof(header));
   header.command = cix_command::RM; 
   header.nbytes = 0; 
   snprintf(header.filename, filename.length()+1, filename.c_str()); 
   //sends and receives the packet 
   log<<"Sending header: "<<header<<endl; 
   send_packet(server, &header, sizeof(header)); 
   recv_packet(server, &header, sizeof(header)); 
   log<<"Header received: "<<header<<endl; 
   //if the request was successfully completed, log success
   if((header.command == cix_command::ACK))
   {
      log<<"Server successefully removed file: ";
      log<<"Received ACK response"<<endl;
   }
   else //else log failure
   {
      log<<"Server failed to remove file: Received NAK response"<<endl;
   }
}

/*-------------------------END OF ADDED CIX FUNCTIONS---------------*/ 

void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

/*The main starts up an infinit loop after linking the client with 
 *the local host server. It continuously gets lines from cin and 
 *processes them with cix_commands. 
 *Largely the only things that have been modified from the original
 *function is line parsing logic so that it recognizes commands that
 *include filenames (like get, put, etc) and splits the line as such. 
 *It also has cases for the commands that I had to implement myself: 
 *rm, put, get. */ 
int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   if (args.size() > 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   log << to_string (hostinfo()) << endl;
   try {
      log << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      log << "connected to " << to_string (server) << endl;
      for (;;) {
         string line;
         getline (cin, line);
         //once it gets the line, it parses for whitespace, indicating
         //filenames that will mess with the usage for commands
         wordvec w = split(line, " "); 
         string filename; 
         if(w.size()>1)filename = w[1];
         //rather than creating a new variable to indicate the 
         //command name and write it into the arguments of each of the
         //function calls, it's best to just reassign line to the first
         //word in the vector we have already found. 
         line = w[0]; 
         if (cin.eof()) throw cix_exit();
         log << "command " << line << endl;
         const auto& itor = command_map.find (line);
         cix_command cmd = itor == command_map.end()
                         ? cix_command::ERROR : itor->second;
         switch (cmd) {
            case cix_command::EXIT:
               throw cix_exit();
               break;
            case cix_command::HELP:
               cix_help();
               break;
            case cix_command::LS:
               cix_ls (server);
               break;
            /*Get put and rm are the added functions. They have an
             *added filename argument field because all of them work
             *with files*/   
            case cix_command::GET: 
               cix_get(server, filename); 
               break;
            case cix_command::PUT:
               cix_put(server, filename); 
               break;
            case cix_command::RM:
               cix_rm(server, filename); 
               break; 
            default:
               log << line << ": invalid command" << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   return 0;
}

