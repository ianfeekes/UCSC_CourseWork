//PA3 GCD
//Ian Feekes
//1474914
//CMPS 11
import java.util.Scanner;
public class GCD
{
 public static void main(String[] args)
 {
  Scanner scan = new Scanner(System.in);           //I like the name scan more for organizational purposes
  System.out.println("Enter a positive integer: ");
  boolean loopKeeper=true;                        //Used to verify that the user enters a positive integer
  int firstInt=0;				  //Initialized to zero because program bugged out otherwise
  int  secondInt=0;
  while(loopKeeper==true)                        //Double while loop firstly ensures they enter an integer and seondly ensures the integer is positive
  {
   while(!scan.hasNextInt())
   {
    scan.next();
    System.out.println("Please enter a positive integer: ");
   }
   firstInt=scan.nextInt();
   if(firstInt>0) loopKeeper=false;
   else System.out.println("Please enter a positive integer: ");
  }
  System.out.println("Enter another positive integer: ");
  while(loopKeeper==false)
  {
   while(!scan.hasNextInt())
   {
    scan.next();
    System.out.println("Please enter a positive integer: ");
   }
   secondInt=scan.nextInt(); 
   if(secondInt>0) loopKeeper=true;
   else System.out.println("Please enter a positive integer: ");
  }
  int divisorA=0;                                //divisorA is used to keep place for dividing purposes
  int divisor=0;				 //divisor and remainder are used when finding the lowest common denominator
  int remainder=0;
  if(firstInt>=secondInt)
  {
   divisor=secondInt;
   remainder=firstInt%secondInt;
  }
  else 
  {
   remainder=secondInt%firstInt;
   divisor=firstInt;
  }
  while(remainder!=0)
  {
   divisorA=remainder;                          //because of the while loop it will keep doing this until a GCD is found, even if it is 1
   remainder=divisor%remainder;
   divisor=divisorA;
  }
  System.out.println("The GCD of "+firstInt+" and "+secondInt+" is "+divisor);
 }
} 
