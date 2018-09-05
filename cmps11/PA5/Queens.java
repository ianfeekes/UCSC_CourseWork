//Ian Feekes
//#1474914
//PA5
//Queens.java-finds solution to n queens problem

public class Queens
{
 public static void main(String[] args)
 {
  int X = Integer.parseInt(args[0]);
  enumerate(X);
 }
 
 public static void enumerate(int X)
 {
  int[] A = new int[X];
  enumerate(A, 0);
 }

 public static void enumerate(int [] a, int x)
 {
  int b=a.length;
  if(x==b) printSolutions(a);
  else 
  {
   for(int i=0;i<b;i++)
   {
    a[x]=i;
    if(isSolution(a)) enumerate(a, x+1);
   }
  }
 }

 public static void printSolutions(int [] a)
 {
  for(int i=0;i<a.length;i++)
   System.out.print(a[i]+" ");
  System.out.println();
 }

 static void nextPermutation(int[] A)
 {
  int pivot=-1;
  int pivotIndex=-1;
  int successor=-1;
  for(int i=0; i<(A.length-1);i++)		//scans the array from right-to-left
  {
   if(A[i]>A[i+1])				//if the current element is less than its right hand neighbor
   {
    pivot=A[i];					//call the current element the pivot					
    pivotIndex=i;
    i=A.length;					//stop scanning
   }
  }
  if(pivot==-1)					//if the left end was reached without finding a pivot
  {
   int B[] = new int[A.length];
   for(int i=0; i<A.length; i++) B[i]=A[i];
   for(int j=(A.length-1);j>=0;j--)
    A[j]=B[((A.length-1)-j)];			//reverse the array
   return;					//return
  }
  for(int i=0;i<A.length;i++)			//scan the array from right-to-left again
  {
   if(A[i]>pivot)				//if the current element is larger than the pivot
   {	
    successor=A[i];				//call the current element the successor
    i=A.length;					//stop scanning
   }
  }
  int temp=pivot;
  pivot=successor;
  successor=temp;				//swap the pivot and the successor
  int[]C=new int[A.length-pivotIndex];
  for(int i=(pivotIndex+1);i<A.length;i++)
  {
   A[i]=C[(A.length-i+(pivotIndex+1))];		//reverse the portion of the array right of where the pivot was found
  }
 }

 static boolean isSolution(int[] A)
 {
  boolean solution=true;			//default returns true
  for(int i=0;i<A.length;i+=2)			
  {
   for(int j=0;j<A.length;j+=2)			//loops through all the castles placed
   {
    if(((A[i]-A[j])==(A[i+1]-A[j+1]))&&((A[i]-A[j])!=0)) //compares current castle to all others; ignores if compared to self
     solution=false;				//if the x distance and y distance of castles are equal is not solution
    if(A[i]==A[j])solution=false;
    if(A[i+1]==A[j+1])solution=false;
   }
  }
  return solution;				//returns solution
 }


}
