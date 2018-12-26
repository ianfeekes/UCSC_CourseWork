/*
  Ian Feekes
  #1474914
  ifeekes@ucsc.edu 
  cmps111 assgn4
  littleBlock.c: file specifying system with block size of 512B
  FUSE: Filesystem in Userspace
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>		//fuse library 
#include <stdio.h>		//debugging 
#include <string.h>		//strcmp 
#include <errno.h>		//error messages 
#include <unistd.h> 	//allows system calls 
#include <time.h> 		//allows maintenance of the time 
#include <stdlib.h> 	//general useful functions 
#include <fcntl.h>
#include <dirent.h> 	//used in reaaddir: most FUSE filesystem examples use this


//Include files written in this assignment as well 
#include "fatblock.h" 
#include "superblock.h" 
#include "directory.h" 

#define BLOCKSIZE 8192 		//We define block size to be 512 bytes 
#define MAXPATHSIZE 75		//We assume that we won't be dealing with rediculous path sizes 

//Super Block is made global
struct superBlock super;
//Initializes the global fat table to NULL 
int32_t* fat=NULL; 
//array of directories: each directory is 64 bytes, so blocksize/64 directories per block 
struct directory directoryBlock[BLOCKSIZE/64]; 
//disk descriptor: This is gonna be used a LOT 
int dd; 


/*This is basically called any time we want to get the attributes of an inode 
  Path: path from the root directory to the node 
  st: data structure containing pointers to actual data within the inode 

  Returns 0 on success
 */ 
static int file_getattr(const char *path, struct stat *st)
{ 
	//res is the return value: 0 on success and 1 on failure 
	int res = 0;
	//void* dirPtr = calloc(sizeof(struct directory), 1); 
	struct directory *d = calloc(sizeof(struct directory), 1); 
	int offset;
	//if we're working with the root directory... 
	if(strcmp(path, "/")==0) 
	{
		st->st_mode = S_IFDIR | 07555; 
		st->st_nlink=2; 					
	}
	else 
	{
		st->st_ctime=d->creationTime;			//creation time set to now 
		st->st_atime=d->accessTime; 		    //access time set to now 
		st->st_mtime=d->modificationTime;	 	//move time set to now 
		st->st_nlink=1; 						//gets on link 
		st->st_size=super.totalBlocks*BLOCKSIZE;//this is all in one large file, so total*blocksize
		st->st_blksize=super.blockSize; 		//block size of super block 
		st->st_blocks=super.totalBlocks;		//For this file system 512B is a block so this is easy  
		//free the pointer to the directory 
		free(d);  
		return res; 
	}
	//likely to remain as 0 if it gets this far 
	return res;
}

/* This reads a directory for usage of ls type commands where we might want to see what 
 * it contains. 
 *
 * path: path of the directory
 * buffer: string to output containing the files/directories to spit out 
 * filler: function to format the output buffer
 * 
 * returns 0 on success 
 */ 
/*Find the first directory entry following the given offset (see below).
Optionally, create a struct stat that describes the file as for getattr (but FUSE only looks at st_ino and the file-type bits of st_mode).
Call the filler function with arguments of buf, the null-terminated filename, the address of your struct stat (or NULL if you have none), and the offset of the next directory entry.
If filler returns nonzero, or if there are no more files, return 0.
Find the next file in the directory.
Go back to step 2.*/ 
static int file_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	int res=0;

	return res; 
}

/* Open a file 
 *
 */
static int file_open(const char *path, struct fuse_file_info *fi)
{
	int res=0;

	return res; 
}


static int file_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	int res=0; 

	return res; 
}

static int file_write(const char *path,const char *buf, size_t size, off_t offset, 
			struct fuse_file_info *fi)
{	
	int res=0; 

	return res; 
}

static int file_mknod(const char *path, mode_t mode, dev_t dev)
{
	int res=0;

	return res; 
}

static int file_mkdir(const char *path, mode_t mode)
{
	int res=0;

	return res; 
}


//Map of fuse functions to functions for my file system 
static struct fuse_operations file_oper = {
	.getattr	= file_getattr,
	.readdir	= file_readdir,
	.open		= file_open,
	.mkdir 		= file_mkdir, 
	.write 		= file_write, 
	.read		= file_read,
};

/* Calls the fuse main with our map table as input parameters, so the library deals 
 * with a lot of the heavy lifting here. Before doing so, it takes in the local file
 * called "disk" which is assumed to be a disk image, and picks it apart for fields of
 * the superblock, the file allocation table, and the root directory. 
 * 	Unfortunately, since the other functions constantly failed to work, none of this can
 * be put to actual use
 */ 
int main(int argc, char *argv[])
{
	//Opens the disk's file descriptor and checks its validity 
	dd = open("disk", O_WRONLY | O_CREAT | O_TRUNC, 0777); 
	if(dd<0)
	{
		perror("Error: failure to open disk image\n");
		return -1; 
	}
	//calloc memory for the single super block 
	void* tempSuper = calloc(BLOCKSIZE, 1); 
	lseek(dd, 0, SEEK_SET); 
	read(dd, tempSuper, BLOCKSIZE); 
	//initializes super with appropriate data fields
	memcpy(&super, tempSuper, sizeof(super)); 
	//fills out the initial fat table: must be allocated after super 
	fat = calloc(BLOCKSIZE, super.numFatBlocks); 
	for(int i=0;i<super.numFatBlocks;i++)
	{
		//You want to read indexed at 1 for blocks  
		lseek(dd, (i+1)*BLOCKSIZE, SEEK_SET); 
		read(dd, (char*)fat+(i*BLOCKSIZE), BLOCKSIZE); 
	}
	memcpy(&fat, fat, BLOCKSIZE*super.numFatBlocks); 
	//set aside memory for our root directory 
	void* tempRoot = calloc(64, 1); 
	lseek(dd, BLOCKSIZE*(1+super.numFatBlocks), SEEK_SET);
	read(dd, tempRoot, 64);  
	memcpy(&directoryBlock[0], tempRoot, 64);
	//calls on the fuse main function after loading the disk 
	return fuse_main(argc, argv, &file_oper, NULL);
}
