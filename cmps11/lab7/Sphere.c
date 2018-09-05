/*Ian Feekes*/
/*1474914*/
/*lab 7*/
/*Sphere.c*/
/*takes in a radius and computes the volume and surface area using C code*/
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int main()
{
 float r;
 const double pi=3.141592654;
 float volume;
 float surfaceArea;
 printf("Enter the radius of the sphere: ");
 scanf("%f", &r);
 volume=(4.0/3)*pi*r*r*r;
 surfaceArea=4*pi*r*r;
 printf("The volume is %.3f and the surface area is %.3f \n", volume, surfaceArea);
 return 0;
}
