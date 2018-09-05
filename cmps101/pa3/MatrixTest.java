//Ian Feekes
//ifeekes@ucsc.edu
//#1474914
//pa3
//MatrixTest.java

public class MatrixTest
{
 public static void main(String[] args)
 {
  int i, j, n=100000;				//set n to 100000
  Matrix A = new Matrix(n);			//two matrices to be manipulated
  Matrix B = new Matrix(n);    
  System.out.println("Changing entries");	//changes the entries
  A.changeEntry(1,1,1); 
  B.changeEntry(1,1,1);
  A.changeEntry(1,2,2); 
  B.changeEntry(1,2,0);
  A.changeEntry(1,3,3); 
  B.changeEntry(1,3,1);
  A.changeEntry(2,1,4);
  B.changeEntry(2,1,0);
  A.changeEntry(2,2,5);
  B.changeEntry(2,2,1);
  A.changeEntry(2,3,6);
  B.changeEntry(2,3,0);
  A.changeEntry(3,1,7);
  B.changeEntry(3,1,1);
  A.changeEntry(3,2,8);
  B.changeEntry(3,2,1);
  A.changeEntry(3,3,9);
  B.changeEntry(3,3,1);
  System.out.println(A.getNNZ());
  System.out.println(A);			//checks the toString method as well as all our manipulation
  System.out.println(B.getNNZ());
  System.out.println(B);			//checks manipulation of second matrix
  Matrix C = A.scalarMult(1.5);
  System.out.println(C.getNNZ());
  System.out.println(C);			//should be the contents of A multiplied by 1.5 the mental math should be easy
  System.out.println("Scalar Multiplication demonstrated above");
  Matrix D = A.add(A);
  System.out.println(D.getNNZ());
  System.out.println(D);
  System.out.println("Addition demonstrated above");	//mostly to make testing easy for me to debug
  Matrix E = A.sub(A);
  System.out.println(E.getNNZ());
  System.out.println(E);
  System.out.println("Subtraction demonstrated above");
  Matrix F = B.transpose();
  System.out.println(F.getNNZ());
  System.out.println(F);
  System.out.println("Transposition demonstrated above");
  Matrix G = B.mult(B);
  System.out.println(G.getNNZ());
  System.out.println(G);
  System.out.println("Matrix multiplication demonstrated above");
  Matrix H = A.copy();
  System.out.println(H.getNNZ());
  System.out.println(H);
  System.out.println("Matrix copying demonstrated above");
  System.out.println(A.equals(H));
  System.out.println("Above should be true (I think)");
  System.out.println(A.equals(B));
  A.makeZero();
  System.out.println(A.getNNZ());
  System.out.println(A);
  System.out.println("A has been made zero so above should be an empty matrix");
 }
}

