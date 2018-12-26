/* 
 * Ian Feekes 
 * #1474914
 * ifeekes@ucsc.edu
 * cmps111 assgn4 
 * diskReader.c 
 * 
 * User space program for testing the building of file systems and data structures 
 */ 

#include <stdio.h>			//used for printf and output 
#include <fcntl.h>			//used in system calls 
#include <unistd.h> 		//used in system calls 
#include <stdlib.h>			//used for pretty much everything 
#include <string.h>			//strcmp
#include <ctype.h>
#include "directory.h"      //FAT system data structures 
#include "superblock.h"
#include "fatblock.h"

/*Reads the disk image into a file buffer (using the read system call produced weird results) 
  and initializes a superblock to the first block of the disk, spitting out its data fields. 
  Initializes each of the FAT blocks and spits out their values that are non-zero for testing 
  purposes, because seeing every index for a large FAT that has not been allocated gives way
  too much output
  */ 
int main(int argc, char **argv)
{
	//check arguments for validity 
	if(argc!=2){
		printf("Usage: ./diskReader [diskimage]\n");
		exit(1); 
	}
    //buffer to store the super block 
    char buf[BLOCKSIZE];
	//open the disk image for reading 
    int f = open(argv[1], O_RDONLY);
    //read the first block (the super block) into the buffer 
    struct superBlock super;
    read(f,buf, BLOCKSIZE); 
    memcpy(&super, buf, sizeof(super));
    int32_t *fat = calloc(BLOCKSIZE, super.numFatBlocks);
    //create the entire fat table for every fat block 
    read(f, fat, BLOCKSIZE*super.numFatBlocks); 
    printf("---------------------------------------\n");
    printf("Fields of SuperBlock:                \n");
    printf(" magic number:                     %x\n", super.magicNumber);
    printf(" total number of blocks: 		 %d\n", super.totalBlocks);
    printf(" number of fat blocks:	           %d\n", super.numFatBlocks);
    printf(" block size (according to super:   %d\n", super.blockSize); 
    printf(" Root directory starting block     %d\n", super.rootBlock);
    printf("----------------------------------------\n");
    printf("\n"); 
    free(&super); 
    int once=0;					//used for formatting 
    printf("---------------------------------------\n");
    printf("non-zero Fields of File Allocation Table:\n");
    for (int i = 0; i < super.totalBlocks; i++) 
    {
    	//This saves us from outputting a billion free entries for a fresh system 
    	if(fat[i]!=0)
    	{
    		if(!once)			//Print this just once, but only if there's nothing 
    		{
    			printf("index              value\n");
    			once =1; 
    		}
    		printf("%d                    %d\n",i, fat[i]); 
    	}
    }
    //If all entries are free then indicate it rather than weird formatting 
    if(!once)printf("All accessible entries are available\n"); 
    printf("---------------------------------------\n");
    printf("\n");
    //close the file 
    //fclose(f);
    close(f); 
    return 0;
}
