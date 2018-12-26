/* 
 * Ian Feekes 
 * #1474914
 * ifeekes@ucsc.edu
 * cmps111 assgn4 
 * fatMain.c
 * 
 * User space program to initialize a brand new fat file system   
 * 
 */ 

 #include <unistd.h> 
 #include <fcntl.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdint.h>
 #include <stdio.h>
 #include <time.h> 
 #include <sys/types.h> 
 #include <sys/stat.h> 
 #include "directory.h"
 #include "superblock.h"
 #include "fatblock.h"

 #define BLOCKSIZE 8192 
 #define MAGICNUM 0xfa91283e

//Was having trouble with includes so I pasted this bad boy here 
int writeBlock(int fd, int blockNum, void* blockToWrite)
{
	lseek(fd, blockNum*BLOCKSIZE, SEEK_SET); 
	return write(fd, blockToWrite, BLOCKSIZE); 
}

/*Initializes a super block, initializes the file allocation table, and initializes the 
  root directory, writing them all to disk then freeing the structures */ 
int main(int argc, char **argv){
	//Check the arguments for correct usage 
	if(argc!=3){
		printf("Error: usage: ./fatMain [filename] [numBlocks]\n"); 
		exit(1); 
	}
	//open the file and check to see if it's valid 
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777); 
	if(fd<0) 
	{
		perror("Error: unable to create file with given arguments.\n");
		exit(1); 
	}
	//Convert the second argument into an integer 
	int numBlocks = atoi(argv[2]); 
	//create a regular old block with no type so that we can blindly clear space in the disk 
	void* block = calloc(BLOCKSIZE, 1); 
	//Go write each block that the user requests with null characters 
	for(int i=0;i<numBlocks;i++){
		if(write(fd, block, BLOCKSIZE)<0)exit(1); 
	}
	//set our current parse in the main disk to the very beginning 
	lseek(fd,0,SEEK_SET); 
	//allocate our super block and all its data fields 
	struct superBlock * super = calloc(BLOCKSIZE, 1);
	//set the magic number to the macro given in the assignment prompt 
	super->magicNumber = MAGICNUM; 
	//set the superblocks # of blocks data field to the user's argument
	super->totalBlocks = numBlocks;
	//according to the assignment pdf...
	super->numFatBlocks= numBlocks/1024;
	//Block size is just based on our macros 
	super->blockSize=BLOCKSIZE;
	/*Rather than importing libraries to do math.ceiling, just test to see
	 *if the N/BLOCKSIZE math needs incrementation as it likely does 
	 */  
	if((numBlocks%BLOCKSIZE!=0))super->numFatBlocks++; 
	//The root block is at index k+1, the k+2nd block
	super->rootBlock=1+super->numFatBlocks; 
	//write it to the disk image 
	write(fd, super, BLOCKSIZE);  
	//Allocate blocks for the FAT table 
	//Each fat pointer is 4 bytes, and you need one for each block, including the super 
	int exactnumFatBlocksBytes = numBlocks*4; 
	//Find the remaining bits for the final entry of the FAT table to save data 
	while(exactnumFatBlocksBytes-BLOCKSIZE>0)exactnumFatBlocksBytes-=BLOCKSIZE; 
	// 0 - k
	for(int i=0;i<super->numFatBlocks;i++)
	{
		//define a fat table to be written into memory 
		struct fatblock *f = calloc(BLOCKSIZE, 1);
		//if(i<super->numFatBlocks-1)
		for(int j=0;j<BLOCKSIZE/4;j++)
		{
			f->dataEntry[j]=-1; 
		}
		//write the contents of the current fat block into memory with its entries 
		lseek(fd, BLOCKSIZE*(i+1), SEEK_SET); 
		read(fd, f, BLOCKSIZE); 
		//since it's a local structure, free it in the loop to avoid leakage 
		free(f);
	}
	//Create the root directory structure and allocate all of its values 
	struct directory* d = calloc(BLOCKSIZE, 1); 
	//Root directory is a directory  
	d[0].flag=1;
	d[0].creationTime=time(NULL); 
	//because it technically hasn't been modified or accessed 
	d[0].modificationTime=0; 
	d[0].accessTime=0; 
	//Directory entries in this file system are 64 bytes long 
	d[0].lengthInBytes=64;
	//Root directory is "/"  but the arrays require string copy to be used 
	strcpy(d[0].name, "/"); 
	d[0].startBlock=1+super->numFatBlocks; 
	lseek(fd, (1+super->numFatBlocks)*BLOCKSIZE, SEEK_SET);
	read(fd, d, BLOCKSIZE); 
	//Since they have all been written to our disk image, we can free the data structures now  
	free(super);
	free(d); 
	close(fd); 
	return 0; 
}
