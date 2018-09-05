// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"
/*Added all includes that are allowed based on the assignment
 *specifications and piazza discussions*/ 
#include <regex> 
#include <cassert> 
#include <cerrno> 
#include <fstream> 
#include <iomanip> 
#include <stdexcept> 
#include <typeinfo> 

/*Main.cpp this is the main program of asg3 
 *Ian Feekes #1474914 ifeekes
 *cmps109 asg3 
 *All work done alone (no partner work) 
 */

/*These lines allow for listmap implementation*/ 
using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

/*This is already functioning it doesn't require additional work*/ 
void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         default:
            complain() << "-" << char (optopt) << ": invalid option"
                       << endl;
            break;
      }
   }
}

/*processLine is used when taking in lines from either a file or from
 *cin. It uses regular expressions to figure out which function 
 *from listmap standard input is invoking, and then performs those
 *functions on the listmap str_str_map argument passed in*/ 
void processLine(std::string l, const int lineNum,
                 str_str_map& keyVals,const string filename)
{
   regex empty {R"(^\s*?$)"};
   /*# followed by 0 or more characters means that anything beginning
    *with the '#' will activate this regex  */
   regex comment {R"(^\s*(#.*)?$)"};
   regex keyEqVal {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
   regex key {R"(^\s*(.*)\s*?$)"};
   regex keyEq {R"(^\s*(.*)\s*=\s*$)"};
   regex eq {R"(^\s*[=]\s*$)"};
   regex eqVal {R"(^\s*[=]\s*(.*?)\s*$)"};
   str_str_pair pair;
   smatch result;
   /*This is done first to aviod unnecessary computation. Also, since
    *this is my first time using regexes, if this is not done first
    *then the logic will recognize this as trying to find a key and 
    *throw error messages, which is undesirable*/   
   if(regex_search(l,result,comment) or regex_search(l,result,empty))
      cout << filename << ": " << lineNum <<": "<<l <<endl;
   /*Case the user enters '=' we need to print the entire listmap*/
   else if(regex_search(l, result, eq))
   {
      cout << filename << ": " << lineNum << ": "<< "=" << endl;
      keyVals.toString(); 
   }
   /*Case the user enters '=[value]' we need to find all keys that
    *hold the value*/ 
   else if(regex_search(l, result, eqVal))
   {
      cout << filename << ": "<< lineNum;
      cout<< ": "<<"=" << result[1] << endl;
      str_str_pair pair(result[1], result[2]); 
      keyVals.toStringVal(pair); 
   }
   /*Case the user enters '[key]=' we need to erase the entry*/ 
   else if(regex_search(l, result, keyEq))
   {
      cout<<filename << ": " << lineNum << ": " << result[1] << endl;
      if(keyVals.end()==keyVals.find(result[1]))
      {
         string str = result[1]; 
         cerr<<str<<": key not found"<<endl; 
      }
      else {keyVals.erase(keyVals.find(result[1]));} 
   }     
   /*Case the user enters '[key]=[value]' */ 
   else if(regex_search(l, result, keyEqVal))
   {
      cout << filename << ": "<< lineNum<<": ";
      cout <<result[1]<<"="<<result[2]<<endl;
      cout << result[1] << " = " << result[2] <<endl;
      str_str_pair pair(result[1], result[2]);
      keyVals.insert(pair);
   }
   /*This takes in the key that the user inputs, checks to make sure
    *that it exists within the listmap(if not it throws an error), and
    *finds the value if it exists, outputing it to cout*/  
   /*Case the user enters '[key]'*/ 
   else if(regex_search(l, result, key))
   {
      /*No matter what, we still need to echo the user input*/ 
      cout<<filename<<": "<<lineNum<<": "<<result[1]<<endl;
      /*If the value doesn't exist, throw an error and complain*/ 
      string str = result[1]; 
      if(keyVals.end() == keyVals.find(result[1]))
      {
         cerr<<str<<": key not found"<<endl; 
      }
      /*Else we output the result*/ 
      else{cout<<str<<" = ";
           cout<<keyVals.find(result[1])->second<<endl;}
   }
}

/*Detects program usage. If the program has a filename arg, it opens
 *the file and processes it, line-by-line. Else it goes to standard 
 *input if the flag has been specified after the file, or if no 
 *files were passed into the arguments. When this is over, it deletes
 *the listmap being used, and frees all relevant memory, and exits*/ 
int main (int argc, char** argv) {
   /*Initialize the map for keys and values in the argument files*/ 
   str_str_map keyVals;
   int lineNum;         //used for processing lines when parsing
   std::string line;    //this is the line in cin or the file
   /*If no files have been specified read from cin*/ 
   if(argc==1)
   {
      lineNum=0; 
      while(std::getline(cin, line))
      {
          ++lineNum;
          /*When getting input from cin use "-" rather than filename*/
          processLine(line, lineNum, keyVals, "-");
      }
   }
   /*If there are arguments, we parse through each of the files, 
    *assigning it a filename and opening it after checking if it is 
    *valid. We parse through it line-by-line using processLine to 
    *check the file's commands using regular expressions, calling the
    *necessary listmap functions with each command. On each of the 
    *arguments, if it is a "-" we process the lines from cin*/   
   else if(argc > 1)
   { 
      for(size_t i = 1; i<argc; ++i)
      {
         lineNum=0;
         fstream file;
         file.open(argv[i]); 
         string fileName = argv[i]; 
         if(file.is_open()) 
         { 
            while(std::getline(file, line))
            {
               ++lineNum; 
               processLine(line, lineNum, keyVals, fileName);
            }
            file.close();
         }
         /*If the filename being specified is "-" then you read from
          *command line input*/     
         else if(fileName=="-")
         {
            while(std::getline(cin, line))
            {
               ++lineNum; 
               /*When getting input from cin use "-"*/
               processLine(line, lineNum, keyVals, "-"); 
            }
         }
         /*Throw an error if the file cannot be opened*/ 
         else cerr << "keyvalue: "<<fileName<<
              ": No such file or directory" << endl;    
      }
   }
   /*Deletes the listmap to make sure we don't have any memory leaks*/ 
   //str_str_map::iterator itor = keyVals.begin();
   //keyVals.erase (itor);
   //delete keyVals*; 
   //keyVals.freeNodes(); 
   return EXIT_SUCCESS;
}

