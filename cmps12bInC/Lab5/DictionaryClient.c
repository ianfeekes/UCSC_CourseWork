/*DictionaryClient.c
 *Created by Ian Feekes December 12th 2017
 *Used for standardized test of Dictionary.c
 *Originally created by UCSC cmps department professors
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"
#include"Dictionary.c"

#define MAX_LEN 180

int main(int argc, char* argv[])
{
   Dictionary A = newDictionary();
   char* k;
   char* v;
   char* word1[] = {"one","two","three","four","five","six","seven"};
   char* word2[] = {"foo","bar","blah","galumph","happy","sad","blue"};
   int i;

   for(i=0; i<7; i++)
   {
      insert(A, word1[i], word2[i]);
   }

   printDictionary(stdout, A);

   for(i=0; i<7; i++)
   {
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }
   delete(A, "one");
   delete(A, "three");
   delete(A, "seven");

   printDictionary(stdout, A);

   for(i=0; i<7; i++)
   {
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }
   printf("%s\n", (isEmpty(A)?"true":"false"));
   printf("%d\n", size(A));
   makeEmpty(A);
   printf("%s\n", (isEmpty(A)?"true":"false"));

   freeDictionary(&A);

   return(EXIT_SUCCESS);
}
