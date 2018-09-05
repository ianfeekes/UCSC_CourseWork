// Lawn.java
// Ian Feekes
// #1474914
// PA1
// Takes in imputs of sizes of a house and a property and the rate of lawn
// mowing and computes it all in an output.
 import java.util.Scanner;
 public class Lawn
{
 public static void main(String[]args)
 { 
  Scanner scan= new Scanner(System.in); //Scanner named as scan to make things easier for me when I want to take in output
  double lotWidth, lotLength, houseWidth, houseLength, mowingRate, time;// all these integers are to be matched with the inputs plugged in
  double lawnArea;//not an input variable but an output variable so I didn't put it with the others
  int hours, minutes, seconds;//All integers so that they are displayed as whole numbers to the readers
  System.out.println("Enter the length and width of the lot, in feet: ");
  lotLength=scan.nextDouble();
  lotWidth=scan.nextDouble();
  System.out.println("Enter the length and width of the house, in feet: ");
  houseLength=scan.nextDouble();
  houseWidth=scan.nextDouble();
  lawnArea=(lotWidth*lotLength)-(houseWidth*houseLength);
  System.out.println("The lawn area is "+lawnArea +" square feet."); 
  System.out.println("Enter the mowing rate, in square feet per second" );
  mowingRate=scan.nextDouble();
  time=lawnArea/mowingRate;
  hours=(int)(time/3600);            //concatenated as integers so it fits the format described in the prompt
  minutes=(int)(time/60)-(hours*60); //subtracts hours*60 because we don't want to display the same value as minutes hours and seconds 
  seconds=(int) time-(hours*3600)-(minutes*60);
  String min="minutes";
  String sec="seconds";
  String hr="hours";
  if(hours==1) hr="hour";     //singularizes the strings if there is only 1 minute, 1 hour, or 1 second in the output
  if(seconds==1) sec="second";
  if(minutes==1) min="minute"; 
  System.out.println("The mowing time is "+hours +" "+hr+" "+minutes +" "+min+" "+seconds+" "+sec+".");
 }
}
