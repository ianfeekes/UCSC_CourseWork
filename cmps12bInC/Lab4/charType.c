//charType.c
//created by Ian Feekes on December 11th 2017

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "charType.h"

#define MAX_STRING_LENGTH 100



int main(int argc, char* argv[])
{
    char* line;
    char* lineAlpha;
    char* lineNum;
    char* linePunct;
    char* lineWhitespace;
    FILE* in;
    FILE* out;
    int currentLine = 1;
    
    if(argc!=3)
    {
        printf("Error: Usage: fileName inFile outFile");
        exit(EXIT_FAILURE);
    }
    
    /* open input file for reading */
    if( (in=fopen(argv[1], "r"))==NULL ){
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    /* open output file for writing */
    if( (out=fopen(argv[2], "w"))==NULL ){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    /*allocate all the arrays we will be using to heap memory*/
    line=calloc(MAX_STRING_LENGTH+1, sizeof(char));
    lineAlpha = calloc(MAX_STRING_LENGTH+1, sizeof(char));
    lineNum = calloc(MAX_STRING_LENGTH+1, sizeof(char));
    linePunct = calloc(MAX_STRING_LENGTH+1, sizeof(char));
    lineWhitespace=calloc(MAX_STRING_LENGTH+1, sizeof(char));
    
    while( fgets(line, MAX_STRING_LENGTH, in) != NULL )
    {
        int valAlpha=0;
        int valNum=0;
        int valPunct=0;
        int valWhitespace=0;
        printf("line %d contains: \n",currentLine);
        
        extractChars(line, lineAlpha, lineNum, linePunct, lineWhitespace);
        printf("%d alphabetic characters: %s \n",(int)strlen(lineAlpha), lineAlpha );
        printf("%d numeric characters: %s \n",(int)strlen(lineNum), lineNum);
        printf("%d punctuation characters: %s \n",(int)strlen(linePunct), linePunct);
        printf("%d whitespace characters: %s \n",(int)strlen(lineWhitespace), lineWhitespace);
        currentLine++;
    }
    
    free(line);
    free(lineAlpha);
    free(lineNum);
    free(linePunct);
    free(lineWhitespace);
    
    fclose(in);
    fclose(out);
    
    exit(EXIT_SUCCESS);
}

void extractChars(char* s, char* a, char* d, char* p, char* w)
{
    int valAlpha =0;
    int valNum=0;
    int valPunct=0;
    int valWhitespace=0;
    int i=0;
    while((s[i]!='\0')&&(i<MAX_STRING_LENGTH))
    {
        if(isalpha(s[i]))
        {
            a[valAlpha++]=s[i];
        }
        if(isdigit(s[i]))
        {
            d[valNum++]=s[i];
        }
        if(ispunct(s[i]))
        {
            p[valPunct++]=s[i];
        }
        if(isspace(s[i]))
        {
            w[valWhitespace++]=s[i];
        }
        i++;
    }
    a[valAlpha]='\0';
    d[valNum]='\0';
    p[valPunct]='\0';
    
}

