/*FileReverse.c
 *Written by Ian Feekes December 7th 2017
 *Takes in two command line arguments as inputs, reads the words in each input file, then prints it backwards on a line by itself.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FileReverse.h"

void stringReverse(char* s)
{
    char temp;
    int x = strlen(s)-1;
    for(int i=0;i<x;i++)
    {
        temp = s[i];
        s[i]=s[x];
        s[x]=temp;
        x--;
    }
}

int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("Error: user must input 2 files: FileReverse inputFile outputFile \n");
        exit(EXIT_FAILURE);
    }
    
    FILE* in;
    FILE* out;
    char word[256]; /*only will read 256 characters*/
    
    in=fopen(argv[1], "r");
    if(in==NULL)
    {
        printf("Error: input file is empty. Unable to read from file %s \n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    out=fopen(argv[2], "w");
    if(out==NULL)
    {
        printf("Error: output file is empty. Unable to write to file %s \n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    /* read words from input file, print on separate lines to output file*/
    while( fscanf(in, " %s", word) != EOF ) //while we are currently scanning a string named word from the in file and it is not the end of the file
    {
        stringReverse(word);
        fprintf(out, "%s\n", word); //Print the string followed by a new line onto the end of the out file.
    }
    
    
    
    
    fclose(in);
    fclose(out);
    
    exit(EXIT_SUCCESS);
    return 0;
}

