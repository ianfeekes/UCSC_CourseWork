//Ian Feekes
//ifeekes@ucsc.edu
//#1474914
//pa3
//ListTest.java

public class ListTest
{
 public static void main(String[] args)
 {
  List L = new List();
  List M = new List();
  //Creates two lists and performs some basic operations. Originally had a lot of println statements for debugging but I took them out
  for(int i=1; i<=20; i++)
  {
   L.append(i);
   M.prepend(i);
  }
  System.out.println(L);		//To make sure that the append and prepend functions work like I want them to
  System.out.println(M);
  for(L.moveFront(); L.index()>=0; L.moveNext()) System.out.print(L.get()+" ");	//makes sure the move front() function works
  System.out.println();
  for(M.moveBack(); M.index()>=0; M.movePrev()) System.out.print(M.get()+" ");
  System.out.println();
  L.moveFront();
  for(int i=0; i<5; i++) L.moveNext();  // at index 5
  L.insertBefore(-3);                   // at index 6 puts a -3
  for(int i=0; i<9; i++) L.moveNext();  // at index 15
  L.insertAfter(-2);			//puts in a -2
  for(int i=0; i<5; i++) L.movePrev();  // at index 10
  L.delete();
  System.out.println(L);
  System.out.println(L.length());
  L.clear();
  System.out.println(L.length());

   }
}

