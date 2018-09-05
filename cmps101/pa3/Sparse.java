//Ian Feekes
//ifeekes@ucsc.edu
//#1474914
//pa3
//Sparse.java

import java.io.*;
import java.util.Scanner;
   
//note the first 34 or so lines are pretty much copied from the input output file usage example on the webpage
class Sparse
{
 public static void main(String[] args) throws IOException
 {
  Scanner in = null;			//scanner to read the input file
  PrintWriter out = null;		//writes the output file
  String line = "";
  String[] token = null;
  int i, n, lineNumber = 0;
  List[] matrixA, matrixB = null; 
  if(args.length < 2)
  {
   System.err.println("Usage: FileIO infile outfile");
   System.exit(1);
  }    
  in = new Scanner(new File(args[0]));
  out = new PrintWriter(new FileWriter(args[1]));
  while(in.hasNextLine() )
  {
   lineNumber++;
   line += in.nextLine()+" ";    
   token = line.split("\\s+");  
  }
  n = token.length;
  int nSize = Integer.valueOf(token[0]);
  int matrixAlength = Integer.valueOf(token[1]);
  int matrixBlength = Integer.valueOf(token[2]);
  Matrix A = new Matrix(nSize);		//creates matrix A by parsing through 
  for(i=3; i<((matrixAlength * nSize)+3); i+=nSize) A.changeEntry(Integer.parseInt(token[i]), Integer.parseInt(token[i+1]), Double.parseDouble(token[i+2]));
  int start = (matrixAlength * nSize)+3;//it's annoying to write all that out, especially on one line so I made things a bit easier
  Matrix B = new Matrix(nSize);		//same with matrix B
  for(i = start; i<((matrixBlength * nSize)+start); i+=nSize) B.changeEntry(Integer.parseInt(token[i]), Integer.parseInt(token[i+1]), Double.parseDouble(token[i+2]));
					//demonstrates the necessary operations in correct formating      
  out.println("A=");
  out.println(A);   
  out.println("B="); 
  out.println(B);
  out.println("(1.5)*A =");
  out.println(A.scalarMult(1.5));
  out.println("A+B=");
  out.println(A.add(B));
  out.println("A+A=");
  out.println(A.add(A));
  out.println("B-A=");
  out.println(B.sub(A));
  out.println("A-A= should be zero");
  out.println(A.sub(A));
  out.println("Transpose(A) =");
  out.println(A.transpose());    
  out.println("A*B =");
  out.println(A.mult(B));    
  out.println("B^2 =");
  out.println(B.mult(B));
  in.close();				//closes scanner and file writer 
  out.close();
 }
}

