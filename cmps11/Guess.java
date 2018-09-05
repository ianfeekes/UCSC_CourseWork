//PA2
//Ian Feekes
//1474914
//CMPS 11 
//Generates a random integer between 1 and 10 and user has 3 guesses to find the integer.

import java.util.Scanner;
public class Guess
{
 public static void main(String[] args)
 {
  Scanner scan = new Scanner(System.in);//scanner is named "scan"
  System.out.println("I'm thinking of an integer in the range of 1 to 10. You have three guesses. ");
  int randomInt=(int)(1+Math.random()*10);//Int that they have to guess, 1 is added because math.random() generates zeros
  int playersGuess;                     //Compared to randomInt
  System.out.println();
  System.out.println("Enter your first guess: ");
  playersGuess=scan.nextInt();
  if(playersGuess==randomInt)
  {
   System.out.println("You win!");
   System.exit(0);			//No more is necessary if they already win so the program terminates
  } 
  else if(playersGuess>randomInt)
  {
   System.out.println("Your guess is too high.");
  }
  else if(playersGuess<randomInt)
  {
   System.out.println("Your guess is too low.");
  }
  System.out.println();
  System.out.println("Enter your second guess: ");
  playersGuess=scan.nextInt();
  if(playersGuess==randomInt)
  {
   System.out.println("You win!");
   System.exit(0);                     
  }
  else if(playersGuess>randomInt)
  {
   System.out.println("Your guess is too high.");
  }
  else if(playersGuess<randomInt)
  {
   System.out.println("Your guess is too low.");
  }
  System.out.println();
  System.out.println("Enter your third guess: ");
  playersGuess=scan.nextInt();
  if(playersGuess==randomInt)
  {
   System.out.println("You win!");
   System.exit(0);                  
  }
  else if(playersGuess>randomInt)
  {
   System.out.println("Your guess is too high.");
   System.out.println();
   System.out.println("You lose. The number was "+randomInt+"."); //message if the player loses
  }
  else if(playersGuess<randomInt)
  {
   System.out.println("Your guess is too low.");
   System.out.println();
   System.out.println("You lose. The number was "+randomInt+".");
  }
  System.out.println();
 }
}
