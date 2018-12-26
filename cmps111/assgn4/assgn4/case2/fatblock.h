/* 
 * Ian Feekes 
 * #1474914
 * ifeekes@ucsc.edu
 * cmps111 assgn4 
 * dataBlock.h
 * 
 * specifies the data held by a regular old data block that can
 * be found in the file allocataion table (FAT) 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdint.h> 
#include <stdio.h> 

#define BLOCKSIZE 8192

/* Since each block pointer in the FAT is 32 bits, each FAT block
 * can hold 1024 block pointers, so you need N/1024 FAT blocks, but
 * obviously at least one. 
 * The first k+1 FAT pointers (0-k) are unused 
 * The remainder (k+1 and higher) are available for use in files and
 * directories 
 */ 
struct fatblock{
	int32_t dataEntry[BLOCKSIZE]; 
};
