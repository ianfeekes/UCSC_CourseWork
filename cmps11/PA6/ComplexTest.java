import java.util.Scanner;
import java.io.*;

class ComplexTest{
   
   public static void main(String[] args) throws IOException{
      Scanner in  = new Scanner(new File(args[0]));
      PrintWriter out = new PrintWriter(new FileWriter(args[1]));
      Complex[] C = new Complex[10];
      int i = 0;
      while(in.hasNextLine()){
         C[i] = new Complex(in.nextLine());
         i++;
      }
C[0] = C[0].add(C[1]);
      C[2] = C[2].sub(C[3]);
      C[3] = C[3].mult(Complex.I);
      C[4] = C[4].mult(C[5]);
      C[6] = C[6].conj().negate();
      C[7] = ( C[7].equals(Complex.ZERO) ? C[7].add(Complex.I) : C[7].recip() );
      C[8] = ( C[9].equals(Complex.ZERO) ? C[8].div(Complex.valueOf("1+i")) : C[8].div(C[9]) );
      C[9] = Complex.valueOf(C[9].abs(),C[0].arg());
      C[5] = Complex.valueOf(C[5].Im()).add(Complex.valueOf(C[5].Re()).mult(Complex.I));
       for(i=0; i<10; i++){
         out.println(C[i]);
      }
      
      
             in.close();
                   out.close();
                     
                        }
      
                        }
