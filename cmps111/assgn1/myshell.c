/*Ian Feekes
 *ifeekes
 *#1474914
 *cmps111 assgn1 
 *myshell.c 
 * 
 *Shell that allows for argument processing of getline using the lex.yy.c
 *file. Supports exit() system call, commands with no arguments, commands with
 *arguments, and commands with or without arguments
 */ 

#include <stdio.h> 
#include <signal.h> 	//signal.h used for signal alarms
#include <unistd.h> 
#include <sys/time.h> 
#include <sys/wait.h> 
#include <sys/types.h>  //this include was in piazza 
#include <errno.h>
#include <stdlib.h>     
#include <string.h> 
#include <fcntl.h>      //this include allows open system call to function as desired with right setting

//For this programming assignment we kill processes after 15 seconds 
#	define		HOW_LONG	15

extern char **getline();
pid_t pid; 			//pid_t is signed int representing process id	
void doomsday();		//define the kill function 
void executeArguments();	//define the new process argument processing 
void redirectInput();		//function to redirect input
void redirectOutput();		//function to redirect output and append output as well
void processPipeline();		//function to process pipeline 
int whatHappened; 		//used for wait system calls. Taken from piazza
char **args;			//pointer to arguments is made global so both processes can access
int i;				//index we are currently iterating on in the arguments. Also global for forking
int argSize;			/*This is the number of commands. It is global so that forked processes
				  do not recalculate the number of arguments each time execute arguments
				  is called on the same command line as it leads to failure to nullify
				  dangling arguments with pipelining */  

/*Forks, then determines if the process is the parent or child. The parent (the main shell) waits
 *for its child to execute commands. The child executes the commands and processes the arguments*/ 
int main() {
    //Constantly processes arguments until the user calls exit 
    while(1) {
    	printf("myshell: ");   	 //illustrates the command prompt, differing from default for clarity  
     	args = getline();        //invokes get line to take in arguments
        //This line makes the user be able to print out nothing and it won't seg fault or dump core
	if(args[0]==NULL || args==NULL){} 
	else if(strcmp(args[0], "exit")==0) exit(0); 
	else { 
           pid=fork(); 
           /*If the process ID returned by forking is negative this means that
      	    *the process creation was unsuccessful and error must be thrown*/ 
	   //set the alarm 
	   signal(SIGALRM, doomsday); 
	   alarm(HOW_LONG); 
	   if(pid<0) { 
     	  	 perror("Error while forking... failed to create child process\n"); 
           	 exit(EXIT_FAILURE); 
           }
	   /*The pid will be positive to the parent which gets the pid of the child. In this
             case we wait for the child process to finish what its doing and to have no 
	     children before we check the arguments to kill the parent */ 
       	   else if(pid>0) { 
		//It throws warnings if we don't add an extra set of parenthesis 
          	while((pid=wait(&whatHappened)))if(pid==-1)break; 
	  	/*args must be checked for NULL before testing for exit command to 
           	*avoid some nasty seg faults*/ 
          	if(args==NULL){}
          	if(args[0]==NULL){} 
	  	/*Check for exit*/ 
		else if(strcmp(args[0], "exit")==0) exit(EXIT_SUCCESS);           
		signal(SIGALRM, SIG_IGN); 
		alarm(0); 
	  }
	  /*Fork returns a 0 to a newly created child process. First find out how many
	    arguments there are before executing: This way we can avoid some strange bugs
	    resulting from recursive execution ie. pipelining, after certain args have
	    been nullified */ 
     	  else if(pid==0) {
        	for(argSize=0;args[argSize]!=NULL;argSize++){}
	// 	argSize++;  
		executeArguments();  
	  }    
      }
   }
}

/*Murders a process with its ID as an argument and prints that it killed the process
 *because it took over "HOW_LONG" seconds (15)
 */ 
void doomsday() {
    kill(pid, SIGKILL);
    printf("No answer in %d seconds.\n", HOW_LONG); 
    fflush(stdout); 
}

/*This was probably the easiest to write. It checks to make sure that there exists an argument
 *with input to redirect. It then opens the file as read-only, checks to see if it is valid 
 *and then calls dup, and checks to make sure the call was a successful. It then rearranges the
 *arguments so that when it is to be executed later there are no problems processing args. It
 *finally increments i so that there is no redundant processing. 
 */ 

void redirectInput() {
       if(args[i+1]==NULL) { 
	    perror("Error: cannot redirect input from an empty file \n");
	    exit(EXIT_FAILURE); 
	}
	int fileDescriptor; 
	fileDescriptor = open(args[i+1], O_RDONLY, 00700);
	if(fileDescriptor < 0) {
	   perror("Error: failure to open file \n"); 
	   exit(EXIT_FAILURE);
	}
        int inputFlag = dup2(fileDescriptor, 0);
	if(inputFlag < 0) {
	   perror("Error: failure to sent data from file for input \n"); 
	   exit(EXIT_FAILURE); 
	}	
	args[i]=args[i+1];
	args[i+1]=NULL; 
	i++;
}

/*First makes sure that there is a filename to redirect output to. Then it searches to see
 *if there is another > character to determine if data needs to be overwritten or just appended. 
 *If data is to be appended, it finds the right spot using lseek, nullifies the args that we don't
 *want to deal with, and moves on to the next relevant arguments.
 *If data is to be overwritten, it opens the file with the O_TRUNC flag to flush out all the previous
 *data, else not everything would necessarily be overwritten. It sets lseek to the beginning (which
 *may be extranneous, but for this assignment I want to be careful). 
 *It then checks to make sure that the file opened exists, then calls dup to throw in the data to the
 *given file descriptor and moves onto the next argument 
 */  
void redirectOutput() { 
	//This is done first to avoid some strange errors 
	if(args[i+1]==NULL) { 
	    perror("Error: cannot redirect output to empty argument \n");
	    exit(EXIT_FAILURE);
	}
	int fileDescriptor;
	//if '>>'
	if(*args[i+1]=='>') {
	   fileDescriptor = open(args[i+2], O_WRONLY | O_CREAT, 00700); 
 	   lseek(fileDescriptor, 0, SEEK_END);
	   args[i]=NULL;
	   args[i+1]=NULL;
	   i++;
	}
	//if '>' 
	else { 
	   fileDescriptor = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 00700);
	   lseek(fileDescriptor, 0, SEEK_SET);
	   args[i]=NULL;
	}
	if(fileDescriptor < 0) { 
	    perror("Error: failure to open file for output redirection \n");
	    exit(EXIT_FAILURE); 
	}	
	int outputFlag = dup2(fileDescriptor, 1);
	if(outputFlag < 0) { 
	    perror("Error: failure to write to output file when redirecting output \n");
	    exit(EXIT_FAILURE); 
	}
  	close(fileDescriptor);
	i++; 	
}

/*Sets a pipeDescriptor which is just an array of two file descriptors for each end of the
 *pipeline. Forks the process and tests to see if we are dealing with the parent or child. The 
 *child process calls dup into itself and closes the parents file descriptor. It then kills all
 *arguments after the '|' character, because they have already been shifted to the left indices
 *so that execV doesn't fail later when it is called. 
 *The parent process calls dup on the first file descriptor, closes the child file descriptor, 
 *and waits for the child to stop executing. It kills the '|' character and shifts all arguments 
 *after the pipeline character to the leftmost indices so that recursive processing doesn't give
 *any strange errors. It then nullifies the rest of the arguments and calls it execute arguments 
 *recursively. 
 */ 
void processPipeline() { 
	int pipeDescriptor[2];
	pipe(pipeDescriptor);
	pid_t cpid = fork();
	//invalid process ID 
	if(cpid<0) {
	   perror("Error: invalid pid when forking during pipelining \n");
	   exit(EXIT_FAILURE);
	}
	//child process 
	else if(cpid==0) { 
	   dup2(pipeDescriptor[1],1);
	   close(pipeDescriptor[0]);
	   for(;i<argSize;i++)args[i]=NULL;
	}
	//parent process 
	else {
	   dup2(pipeDescriptor[0],0);
	   close(pipeDescriptor[1]);
	   while((pid=wait(&whatHappened))){if(pid==-1)break;}
	   args[i]=NULL;
	   i++;
	   int j;
           for(j=0;j<argSize;j++) { 
		args[j]=args[i+j];
	   }
	   //This line is very important and took forever to debug. Decrement argSize for recursion. 
	   argSize-=i; 	
	   //Sometimes there will be strange errors if this isn't set to null 
	   args[j+1]=NULL;
           executeArguments();  
	}	
}

/*This is where most work for this assignment has gone. It parses through the arguments testing for
  the specified flags > < >> | and executes necessary system calls and nullifies the arguments for 
  each flag. With pipelining, execute arguments can become recursive*/ 
void executeArguments() { 
	if(args==NULL) return; 
        if(args[0]==NULL) return; 

	for(i=0; i<argSize;i++) {
	    if(*args[i]=='<') {
	    	redirectInput(); 
	    } 
	    else if(*args[i]=='>') {
	    	redirectOutput();  
	    } 
             else if(*args[i]=='|') {
	        processPipeline(); 
	    }
	}
	if(execvp(args[0], args)<0) {
	    perror("Failure executing file"); 
	    exit(EXIT_FAILURE); 
	}
	exit(EXIT_SUCCESS); 	
}
