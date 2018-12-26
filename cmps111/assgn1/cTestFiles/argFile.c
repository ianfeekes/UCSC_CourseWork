/*Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 *cmps111 assgn1
 * 
 *argFile.c 
 *c file that takes in arguments and spits them out in the form of a println 
 *statement so that data redirection from myshell.c can be tested 
 */ 

#include<stdio.h>
#include<stdlib.h> 

 int main(int argv, char** argc) 
 {
 	printf("smokin meats here: \n"); 
	for(int i=0;argc[i]!=NULL; i++) 
 	{
		printf("%s ", argc[i]); 
	}
	printf("\n"); 
	exit(0); 
 }
