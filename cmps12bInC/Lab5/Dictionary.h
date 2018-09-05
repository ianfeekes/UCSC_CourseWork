/*Dictionary.h - header file for Dictionary.c
 *Written by Ian Feekes December 12th 2017
 */

#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_

typedef struct DictionaryObj* Dictionary;

Dictionary newDictionary(void);

void freeDictionary(Dictionary* pD);

int isEmpty(Dictionary D);

int size(Dictionary D);

char* lookup(Dictionary D, char* k);

void insert(Dictionary D, char* k, char* v);

void delete(Dictionary D, char* k);

void makeEmpty(Dictionary D);

void printDictionary(FILE* out, Dictionary D);

#endif
