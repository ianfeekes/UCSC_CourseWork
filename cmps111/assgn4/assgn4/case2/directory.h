/* 
 * Ian Feekes 
 * #1474914
 * ifeekes@ucsc.edu
 * cmps111 assgn4 
 * directory.h 
 * 
 * specifies the data held by a directory 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdint.h> 
#include <stdio.h> 

/* Word index		Content
 * 0-5				File name(null-terminated, up to 24 bytes w/null)
 * 6-7				creation time (64-bit)
 * 8-9				modification time (64 bit)
 * 10-11			access time	(64 bit)
 * 12				file length in bytes
 * 13 				start block 
 * 14				flags
 * 15 				unused
 */ 
struct directory{
	char name[24]; 
	uint64_t creationTime; 
	uint64_t modificationTime; 
	uint64_t accessTime; 
	uint32_t lengthInBytes; 
	uint32_t startBlock;
	/* The only flag that we maintain for a directory is the DIRECTORY
	 * flag, which is bit 0 of the flags entry. so if flag & 0 == 0 it 
	 * is a regular file, if 1 it is a directory 
	 */ 
	uint32_t flag;
	uint32_t unused; 
}; 
