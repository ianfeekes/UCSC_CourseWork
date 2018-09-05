//Ian Feekes
//1474914
//PA5
//Queens.java
//Finds the possible placements of queens for a given chessboard by the user

public class Queens
{

 public static void main(String[] args)
 {
  int boardSize= Integer.parseInt(args[0]);
  int[] a = new int[boardSize];
  nextPermutation(a);
 }

 static void nextPermutation(int[] a)
 {
  int pivot =-1;
  int pivotIndex=-1;
  int successor=-1;
  for(int i=0;i<a.length-1;i++)			//Scans the array from right-to-left
   if(a[i]<a[i+1])				//if the current element is less than its right-hand neighbor
   {
    pivot=a[i];					//call current element the pivot
    pivotIndex=i;
    i=a.length;					//stop scanning
   }
  if(pivot==-1)
  {
   for(int i=0; i<a.length; i++)
   int[] b= new int[a.length];
   for(int i=0; i<a.length; i++)
   a[i]=b[(a.length-1)-i];			//reverse the array
   return;					//return
  }
  for(int i=0;i<a.length;i++)			//scan the array from right to left 
  {
   if(a[i]>pivot)				//if current element is larger than the pivot
   {
    a[i]=successor;				//call current element the successor
    i=a.length;					//stop scanning
   }
  }
  int temp=successor;
  successor=pivot;				//swap the pivot and the successor
  pivot=temp;
  return;					//returni
 }


 static boolean isSolution(int[]a,int n)
 {
  for(int i=0; i<n; i++)
  {
    						//finish code for this shit
  }
  return true;
 }

 static void printQueens(int[]a)
 {
  for(int i=0; i<a.length;i++)
  {
   System.out.print(a[i]);
  }
 }

}
