/* 
 * Ian Feekes 
 * #1474914
 * ifeekes@ucsc.edu
 * cmps111 assgn4 
 * superblock.h 
 * 
 * specifies the data held by the superblock
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdint.h> 
#include <stdio.h> 

/* The superblock is block 0
 * Each of the data fields are stored in 32 bit words 
 * 
 * Word Index		Content
 * 0				Magic number: 0xfa91283e
 * 1				N: total number of blocks in the system
 * 2				k: number of blocks in FAT
 * 3 				block size which is 512B or 8KB 
 * 4				starting block of the root directory, k+1 
 */
struct superBlock{
	uint32_t magicNumber; 
	uint32_t totalBlocks; 
	uint32_t numFatBlocks;
	uint32_t blockSize; 
	uint32_t rootBlock;
};