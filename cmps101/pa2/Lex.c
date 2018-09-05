//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//Lex.c
//PA2
//Tantalo 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int n, count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;
   if( argc != 3 )//checks to make sure the user entered the files we needed 
   {
      printf("Error: Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL )//checks to make sure the files contain things to be read and written 
   {
      printf("Error: Unable to open reading file %s \n", argv[1]);
      exit(1);
   }
   if( out==NULL )
   {
      printf("Error: Unable to open writing file %s \n", argv[2]);
      exit(1);
   }
   while( fgets(line, MAX_LEN, in) != NULL)//parses through strings of reading file 
   {
      count++;
      n = 0;
      token = strtok(line, " \n");
      tokenlist[0] = '\0';
      while( token!=NULL )
      {
         strcat(tokenlist, "   ");
         strcat(tokenlist, token);
         strcat(tokenlist, "\n");
         n++;
         token = strtok(NULL, " \n");
      }
   }
   List A = newList();
   append(A, 0);
   for(int k = 1; k < n; k++)//we check to see if we need to prepend or append in this loop
   {
      moveFront(A);
      printf("Enter For Loop\n");
      if(strcmp(tokenlist[front(A)],tokenlist[get(A)]) > 0)
      {
         prepend(A, k);
         printf("Prepend\n");
      } 
      else
      {
         while(index(A) != -1 && strcmp(tokenlist[k],tokenlist[get(A)]) > 0)
         {
            moveNext(A);
         }
         if(index(A) == -1)
         {
            append(A, k);
            printf("Append\n");
         }
         else
         {
            insertBefore(A, k);
            printf("insertBefore\n");
         }
      }
   }

   for(moveFront(A); index(A)>=0; moveNext(A))//essentially prints indices into writing file. I might have been able to use a modified version of toString here 
   {
      fprintf(out, "%d\n", tokenlist[get(A)]);
   }


   /* closes files */
   fclose(in);
   fclose(out);

   return(0);
}
