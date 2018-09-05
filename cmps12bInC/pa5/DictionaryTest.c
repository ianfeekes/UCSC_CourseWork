/* DictionaryTest.c 
 * Created by Ian Feekes December 12th 2017
 * Used for my own debugging and running of Dictionary.c
 */

/*NOTE: I use printf statements containing foo to debug to see where segmentation faults are*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"
#include"Dictionary.c"

int main()
{
    Dictionary D = newDictionary();
    printf("Testing isEmpty method should return 1 for true: %d \n",isEmpty(D));
    printf("Testing size method should return 0: %d \n", size(D));
    printf("Testing lookup() method on empty dictionary should be null %s \n", lookup(D, "k"));
    insert(D, "k1", "v1");          /*We now know that our insert method works*/
    insert(D, "k2", "v2");
    insert(D, "k3", "v3");
    insert(D, "k4", "v4");
    insert(D, "k4", "v3");          /*Testing to see if it detects trying to insert an already existing key*/
    insert(D, "k1", "v1");
    insert(D, "k2", "v3");
    insert(D, "k4", "v4");
    /*printf("foo \n");*/
    printf("Testing lookup() method for our dictionary now containing a value v1: %s \n", lookup(D, "k1"));
    delete(D, "k3");
    /*delete(D, "k5");*/            /*Testing to see if it detects delete is called on a nonexistent key*/
    /*printf("foo \n"); */
    printf("Testing to see if our deleted element is gone, should be null:  %s \n", lookup(D, "k3"));
    makeEmpty(D);                   /*Segmentation fault found in makeEmpty method. Lets fix this...*/
    /*printf("foo \n");*/           /*Segmentation fault fixed: while loop in makeEmptyList was wrong*/
    printf("Testing to see if our list is now empty  and that our makeEmpty method worked: %d \n", isEmpty(D));
    insert(D, "k1", "v1");
    insert(D, "k2", "v2");
    insert(D, "k3", "v3");
    insert(D, "k4", "v4");
    printf("\n");
    printDictionary(stdout, D);     /*Due to how the hash function works this will not necessarily be in order*/ 
    return(0);
}
