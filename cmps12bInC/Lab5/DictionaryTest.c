/* DictionaryTest.c
 * Created by Ian Feekes December 12th 2017
 * Used to do my own personal bugging of Dictionary.c
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"
#include"Dictionary.c"

#define MAX_LEN 180

int main()
{
    Dictionary D = newDictionary();
    printf("Testing isEmptyMethod should return true (1): %d \n", isEmpty(D));
    //(insert(D, "k", "testString1"));
    //lookup(D, "k");
    printf("Testing size method should return 0: %d \n", size(D));
    lookup(D, "k");
    insert(D, "k", "v");
    printf("Testing to see if lookup works. Should return v... %s \n", lookup(D, "k"));
    printf("Testing isEmptyMethod should return false (0): %d \n", isEmpty(D));
    printf("Testing size method should return 1: %d \n", size(D));
    insert(D, "k1", "v1");
    insert(D, "k2", "v2");
    //insert(D, "k2", "v2");
    delete(D, "k1");
    printf("Testing to see if k1 was successfully deleted. Should return NULL %s \n", lookup(D, "k1"));
    return(0);
}
