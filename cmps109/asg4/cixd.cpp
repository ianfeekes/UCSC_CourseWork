// $Id: cixd.cpp,v 1.7 2016-05-09 16:01:56-07 - - $

/*Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *CMPS109 ASG4
 *cixd.cpp 
 *This is a file with primary modifications for the usage of client-
 *server implementation*/ 

#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
#include <sstream> 
using namespace std;
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>
#include "protocol.h"
#include "logstream.h"
#include "sockets.h"

logstream log (cout);
struct cix_exit: public exception {};

//calls library functions to turn an input file into a string
string fileToString(const ifstream& file)
{
  stringstream temp;
  temp<<file.rdbuf();
  string toReturn = temp.str();
  return toReturn;
}
            

/*Server ls processing has already been implemented for us. It serves
 *to model the other functions for user command processing S->C */ 
void reply_ls (accepted_socket& client_sock, cix_header& header) {
   const char* ls_cmd = "ls -l 2>&1";
   FILE* ls_pipe = popen (ls_cmd, "r");
   if (ls_pipe == NULL) { 
      log << "ls -l: popen failed: " << strerror (errno) << endl;
      header.command = cix_command::NAK; 
      header.nbytes = errno;
      send_packet (client_sock, &header, sizeof header);
      return; 
   }
   string ls_output;
   char buffer[0x1000];
   for (;;) {
      char* rc = fgets (buffer, sizeof buffer, ls_pipe);
      if (rc == nullptr) break;
      ls_output.append (buffer);
   }
   int status = pclose (ls_pipe);
   if (status < 0) log << ls_cmd << ": " << strerror (errno) << endl;
              else log << ls_cmd << ": exit " << (status >> 8)
                       << " signal " << (status & 0x7F)
                       << " core " << (status >> 7 & 1) << endl;
   header.command = cix_command::LSOUT;
   header.nbytes = ls_output.size();
   memset (header.filename, 0, FILENAME_SIZE);
   log << "sending header " << header << endl;
   send_packet (client_sock, &header, sizeof header);
   send_packet (client_sock, ls_output.c_str(), ls_output.size());
   log << "sent " << ls_output.size() << " bytes" << endl;
}

/*Response to the client requesting a server file being sent as a 
 *local file. Creates a new file, takes the contents by invoking the
 *fileToString function, and closes the file. Sets the header fields
 *properly, and sends the header. Then sends the payload with the
 *file contents. If it fails to send the file it sets the header 
 *command to NAK and logs messages indicating this failure */ 
void reply_get(accepted_socket& client_sock, cix_header& header)
{
   //create an input file stream to be parsed
   ifstream in(header.filename); 
   if(in.is_open()) 
   {
      //if successfully opened, set the command to FILE 
      header.command = cix_command::FILE; 
      string str = fileToString(in);  
      in.close(); 
      header.nbytes = str.size(); 
      memset(header.filename, 0, FILENAME_SIZE); 
      log<<"sending header: "<<header<<endl; 
      //send header packet
      send_packet(client_sock, &header, sizeof(header)); 
      //send payload packet 
      log<<"sending payload: "<<str<<endl; 
      send_packet(client_sock, &str, str.size()); 
      log<<"sent "<<str.size()<< "bytes" <<endl; 
   }
   else
   {
      //if failure to open file, log error message
      log<<header.filename<<": failed to read file. ";
      log<<"Setting command to NAK"<<endl;  
      //set header command to nake for cix processing
      header.command = cix_command::NAK; 
      log<<"sending header: "<<header<<endl; 
      send_packet(client_sock, &header, sizeof(header)); 
   }
}

/*Server response to the client attempting to add a local file onto 
 *the remote server. Logs the data received, and creates a write
 *file. It the output file is able to be opened, it writes the buffer
 *and sets the command to show it has been accurately written. Else 
 *it logs a message indicating failure and sets the header command to 
 *NAK. It then sends the header that it has modified to the client for
 *processing by cix. */ 
void reply_put(accepted_socket& client_sock, cix_header& header)
{
   log<<"received : "<<header.nbytes<< " bytes" <<endl;
   //we must create a buffer with nbytes terminated by null char
   char buffer[header.nbytes+1]; 
   recv_packet(client_sock, buffer, header.nbytes); 
   buffer[header.nbytes]='\0';
   //create an outfile with the proper filename
   ofstream out(header.filename); 
   //if it is opened successfully, write the file and set command ACK 
   if(out.is_open())
   { 
     log<<"Successfully opened file. Setting command to ACK"<<endl;  
     //we need to write to the file before calling memset
      out.write(buffer,header.nbytes);
      memset(&header.nbytes, 0, sizeof(header.nbytes)); 
      header.command=cix_command::ACK; 
      out.close(); 
   }//if failure with writing outfile set header response to NAK
   else 
   {
      log<<"Failure to open write file. ";
      log<<"Setting command to NAK"<<endl; 
      header.command = cix_command::NAK; 
   }
    //log message and send packet
   log<<"sending header : "<<header<<endl; 
   send_packet(client_sock, &header, sizeof header);  
}

/*unlinkes the file passed into the arguments. If the unlinking is 
 *successful it logs a message indicating this and invokes memset. 
 *If unlinking is unsuccessful it logs this and set teh command to
 *NAK. It then sends the header it has modified for cix processing*/
void reply_rm(accepted_socket& client_sock, cix_header& header)
{
   //unlink deletes file
   if(unlink(header.filename)==0)
   {
      //if the unlink is successful respond with ACK to confirm
      log<<"Success in removing file. Setting command to ACK"<<endl;
      header.command = cix_command::ACK; 
      memset(&header.nbytes, 0, sizeof(header.nbytes)); 
   }
   else
   {
      //if there is a failure to remove, log and set NACk command
      log<<header.filename<<": failure to remove file."<<endl;
      log<<"Setting command to NAK"<<endl;  
      header.command = cix_command::NAK; 
   }
   //send our header packet 
   log<<"sending header: "<<header<<endl; 
   send_packet(client_sock, &header, sizeof(header)); 
}

//This waits for client commands for processing.Three functions added
void run_server (accepted_socket& client_sock) {
   log.execname (log.execname() + "-server");
   log << "connected to " << to_string (client_sock) << endl;
   try {   
      for (;;) {
         cix_header header; 
         recv_packet (client_sock, &header, sizeof header);
         log << "received header " << header << endl;
         switch (header.command) {
            case cix_command::LS: 
               reply_ls (client_sock, header);
               break;
            /*Added functions for processing client requests*/ 
            case cix_command::GET: 
               reply_get(client_sock, header); 
               break;
            case cix_command::PUT: 
               reply_put(client_sock, header); 
               break; 
            case cix_command::RM: 
               reply_rm(client_sock, header); 
               break; 
            default:
               log << "invalid header from client:" << header << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   throw cix_exit();
}

/*This needs no modification*/ 
void fork_cixserver (server_socket& server, accepted_socket& accept) {
   pid_t pid = fork();
   if (pid == 0) { // child
      server.close();
      run_server (accept);
      throw cix_exit();
   }else {
      accept.close();
      if (pid < 0) {
         log << "fork failed: " << strerror (errno) << endl;
      }else {
         log << "forked cixserver pid " << pid << endl;
      }
   }
}

/*This needs no modification*/ 
void reap_zombies() {
   for (;;) {
      int status;
      pid_t child = waitpid (-1, &status, WNOHANG);
      if (child <= 0) break;
      log << "child " << child
          << " exit " << (status >> 8)
          << " signal " << (status & 0x7F)
          << " core " << (status >> 7 & 1) << endl;
   }
}

/*This needs no modification*/ 
void signal_handler (int signal) {
   log << "signal_handler: caught " << strsignal (signal) << endl;
   reap_zombies();
}

/*This needs no modification*/ 
void signal_action (int signal, void (*handler) (int)) {
   struct sigaction action;
   action.sa_handler = handler;
   sigfillset (&action.sa_mask);
   action.sa_flags = 0;
   int rc = sigaction (signal, &action, nullptr);
   if (rc < 0) log << "sigaction " << strsignal (signal) << " failed: "
                   << strerror (errno) << endl;
}

/*This needs no modification*/ 
int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   signal_action (SIGCHLD, signal_handler);
   in_port_t port = get_cix_server_port (args, 0);
   try {
      server_socket listener (port);
      for (;;) {
         log << to_string (hostinfo()) << " accepting port "
             << to_string (port) << endl;
         accepted_socket client_sock;
         for (;;) {
            try {
               listener.accept (client_sock);
               break;
            }catch (socket_sys_error& error) {
               switch (error.sys_errno) {
                  case EINTR:
                     log << "listener.accept caught "
                         << strerror (EINTR) << endl;
                     break;
                  default:
                     throw;
               }
            }
         }
         log << "accepted " << to_string (client_sock) << endl;
         try {
            fork_cixserver (listener, client_sock);
            reap_zombies();
         }catch (socket_error& error) {
            log << error.what() << endl;
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

