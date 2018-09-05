/*Ian Feekes
 *#1474914
 *CMPS 11
 *GCD.c
 *Computes the greatest common divisor of two inputs by the user through C
*/
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int main()
{
 int int1=0;
 int int2=0;
 printf("Enter a positive integer: ");
 scanf("%i",&int1);
 while(int1<=0) 
 {
  printf("Please enter a positive integer: ");
  scanf("%i",&int1);
 }
 printf("Enter another positive integer: ");
 scanf("%i",&int2);
 while (int2<=0)
 {
  printf("Please enter a positive integer: ");
  scanf("%i",&int2);
 } 
 int divisor=0;
 int divisorA=0;
 int remainder=0;
 if(int1>=int2)
 {
  divisor=int2;
  remainder=int1%int2;
 }
 else
 {
  divisor=int1;
  remainder=int2%int1;
 }
 while(remainder!=0)
 {
  divisorA=remainder;                     
  remainder=divisor%remainder;
  divisor=divisorA;
 } 
 printf("The GCD of %i and %i is %i \n",int1, int2, divisor);
 return 0;
} 
