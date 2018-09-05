//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//pa1
//Lex.java
import java.util.Scanner;
import java.io.*;

public class Lex
{ 
 public static void main(String[] args) throws IOException
 {
  //takes in the first two words in args, designating the first one to the input file and the second one to the output file
 

  //checks for proper command line arguments
  if(args.length < 2)
  {
   System.out.println("Error. Usage: FileIO inputFile outputFile");
   System.exit(1);
  }
  
  //all the variables and the objects that we need
  String str = "";
  String[] token = null;
  int i = 0;
  int j = 0;
  int lineNumber = 0;
  Scanner input = null;
  PrintWriter output = null;
  
  input = new Scanner(new File(args[0]));		//I pretty much copied these lines from the FileIO.java example posted on the webpage and it still doesn't work. 
  output = new PrintWriter(new FileWriter(args[1]));    //Just kidding I needed to specify that it throws an IOException
  
  while(input.hasNextLine())//parses through the input file and checks the amount of lines. Appends each line to str and splits it into tokens as done in lab 2 of data structures
  {
   lineNumber++;
   str+=(input.nextLine()+" ");
   token = str.split("\\s+");
  }
  
  j = token.length;//amount of strings
  List M = new List();
  M.append(0);
  int x = 1;
  for(int  k=1; k< j; k++);//checks if we need to prepend increment or append
  {
   M.moveFront();
   System.out.println(x);
   if(token[M.front()].compareTo(token[M.get()])>0)
   {
    System.out.println("prepending");
    M.prepend(x);
   }
   else
   {
    System.out.println("incrementing");
    while((M.index()!= -1)&&(token[x].compareTo(token[M.get()])>0))
    {
     M.moveNext();
    }
    if(M.index()== -1)
    {
     System.out.println("appending");
     M.append(x);
    }
    else
    {
     System.out.println("inserting");
     M.insertBefore(x);
    }
   }
   x++;//because I was having trouble using k in the for loop that led to compile errors I had x equal k
  }
  
  System.out.println(M.toString());
  for(M.moveFront(); M.index()>=0; M.moveNext())
  {
   System.out.print(token[M.get()]+" ");
  }

  input.close();//close the input and output scanners and filewriters when we're done
  output.close();
 }
}
