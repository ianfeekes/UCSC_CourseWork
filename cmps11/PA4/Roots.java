//Ian Feekes
//#1474914
//Cmps 11
//Roots.java PA4
//Finds the roots of a polynomial function inputed by the user

import java.util.Scanner;
public class Roots
{
 public static void main(String[] args)
 {
  Scanner scan=new Scanner(System.in);				//I like the name scan for reading the user input
  int degree=0;
  double resolution=.01;
  double tolerance=.0000001;
  double threshhold=.001;					//tolerance resolution and threshhold all initialized with the given values
  double leftEndpoint, rightEndpoint;
  System.out.println("Enter the degree:");
  degree=scan.nextInt();
  double [] coefficients = new double [(degree+1)];
  System.out.println("Enter "+(degree+1)+" coefficients:");
  for(int i=0; i<coefficients.length; i++)
  coefficients[i]=scan.nextDouble();
  System.out.println("Enter the left and right endpoints: ");
  leftEndpoint=scan.nextDouble();
  rightEndpoint=scan.nextDouble();
  System.out.println("TESTING: The value of f(x) at 1 is "+poly(coefficients, 1));
  if(leftEndpoint>rightEndpoint)				//If the user enters the endpoints not in respective order this if statement will numerically rearrange them
  {
   double d=rightEndpoint;
   rightEndpoint=leftEndpoint;
   leftEndpoint=d;
  }
  boolean noRoots=true;
  double[] derivative=diff(coefficients); 
  for(double i=leftEndpoint; i<rightEndpoint; i+=resolution)
  {
   if((poly(coefficients, i)>0 && poly(coefficients, i+resolution)<0)||(poly(coefficients, i)<0 && poly(coefficients, i+resolution)>0))
   {
    System.out.print("Root found at");
    System.out.printf("%.5f%n",findRoot(coefficients, i, i+resolution,tolerance));
    noRoots=false;
   }
   else if((poly(derivative, i)>0 && poly(derivative, i+resolution)<0)||(poly(derivative, i)<0 && poly(derivative, i+resolution)>0))
    if(poly(derivative, findRoot(derivative, i, i+resolution, tolerance))<threshhold)
   { 
    noRoots=false; 
    System.out.print("Root found at");
    System.out.printf("%.5f%n",findRoot(derivative, i, i+resolution,tolerance));
   }
  }
  if(noRoots==true) System.out.println("No roots found under the given interval for the given polynomial");
 }

 static double[] diff(double[] c)				//Computes and returns the derivative function for a corresponding polynomial function
 {
  double[] derivativeFunction=new double[(c.length -1)];
  for(int i=0; i<derivativeFunction.length; i++)
  derivativeFunction[i]=c[i+1]*(i+1);
  return derivativeFunction;
 }

 static double poly(double[] c, double x)			//Finds f(x)
 {
  double total=c[0];
  for(int i=1; i<c.length;i++)
  total+=c[i]*Math.pow(x,i);
  return total;
 }

 static double findRoot(double[] c, double a, double b, double tolerance)	//Finds the root of a given function
 {
  double width=b-a;
  double midpoint=0;
  while(width>tolerance)
  {
   midpoint=(a+b)/2;
   if(poly(c,a)*poly(c,midpoint )<=0)
   b=midpoint;
   else a=midpoint; 
   width=b-a;
  }
  return midpoint;
 }
}
