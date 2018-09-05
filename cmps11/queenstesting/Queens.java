//Ian Feekes
//#1474914
//Queens.java
//Finds and prints out all solutions to queens.java

public class Queens
{

 public static void main(String[] args)
 {
  boolean printVerbose=false;
  int boardSize=0;
  if(args[0].equals("-v"))
  {
   printVerbose=true;
   boardSize=Integer.parseInt(args[1]);			//checks to run the program slightly differently if user wants verbose input
  }
  else boardSize=Integer.parseInt(args[0]);    		//standard if user doesn't want verbose input
  if(!args[0].equals("-v")&&!(boardSize>=0)) //prints error message if the user enters an input that isn't "-v" or some integer then quits the program.
  {
   System.out.println("please enter a standard input.");
   System.exit(0);
  }
  int[] pieceRowLocation = new int[boardSize];
  int[] rookSolution = new int[boardSize];
  int[] queenSolution = new int[boardSize];
  boolean foundRookSolution=false;
  boolean foundQueenSolution=false;
  int queenSolutionCount =0;
  int rookSolutionCount=0;
  int[]Rookcoordinates=new int[boardSize*2];
  int[]queencoordinates=new int[boardSize*2];      
  for(int i=0;i<boardSize;i++)pieceRowLocation[i]=0;	//Initialize the row locations for each piece. One piece per column

  while(!allSolutionsTested(pieceRowLocation, boardSize))
  {
   
   if(isRookSolution(pieceRowLocation, boardSize))	//if is rooks solution
   {
    foundRookSolution=true;
    rookSolutionCount++;
    for(int i=0;i<boardSize;i++) rookSolution[i]=pieceRowLocation[i];
    if(isQueenSolution(pieceRowLocation, boardSize))	//if is queens solution too
    {
     foundQueenSolution=true;
     queenSolutionCount++;
     for(int i=0;i<boardSize;i++) queenSolution[i]=pieceRowLocation[i];
    }
   } 
   if(foundRookSolution==true)
   {
    if(isQueenSolution(pieceRowLocation, boardSize)&&printVerbose)
    {
     System.out.print("(");
     for(int i=0;i<boardSize;i++)
     {
      if(i==boardSize-1)System.out.print(i+", "+queenSolution[i]);
      else  System.out.print(i+", "+queenSolution[i]+", ");
     }
     System.out.println(")");
    }
   }
   foundRookSolution=false;
   nextPermutation(pieceRowLocation, boardSize);
  }
  if(queenSolutionCount<=1)System.out.println(boardSize+" queens has "+queenSolutionCount+" Solution");//pluralism for the number of solutions
  System.out.println(boardSize+" queens has "+queenSolutionCount+" Solutions");
 }


 static boolean isQueenSolution(int[] pieceRowLocation, int size)//determines if the solution to n rooks can be applied to the queens
 {
  boolean isSolution=true;
  for(int i=0;i<size;i++)
  {
   for(int j=0;j<size;j++)
   {
    if(i!=j)
    {
     if(Math.abs(i-j)==Math.abs(pieceRowLocation[i]-pieceRowLocation[j])) isSolution=false;
    }
   }
  }
  return isSolution;
 }
 
 static boolean isRookSolution(int[] pieceRowLocation, int size)//determines if there is a rook solution that applies
 {
  boolean foundSolution=true;
  int columnOne=0;
  int columnTwo=1;
  boolean done=false;
  while(!done&&(columnOne<size-1))
  {
   if((columnOne==size-2)&&(columnTwo==size-1)) done=true;
   if(pieceRowLocation[columnOne]==pieceRowLocation[columnTwo])
   {
    done=true;
    foundSolution= false;
   }
   else if(columnTwo==size-1)
   {
    columnOne++;
    columnTwo=columnOne+1;
   }
   else columnTwo++;
  }
   return foundSolution;
 }
 
 static boolean allSolutionsTested(int[]pieceRowLocation, int size)
 {
  boolean allTested=true;
  int i=0;
  boolean done=false;
while(!done&&(i != (size-1)))
  {
   if(pieceRowLocation[i] != (size-1))
   {
    allTested=false;
    done=true;
   }
   else i=i+1;
  }
 return allTested;
 }

 static void nextPermutation(int[]pieceRowLocation, int size)//moves the piece to the next permutation row location
 {
  boolean done=false;
  int column=size-1;
  boolean debug=false;
  if(debug)
  {
   System.out.print("input=(");
   for(int i=0;i<size;i++) System.out.print(pieceRowLocation[i]);
   System.out.println(")");
  }

  while(!done&&(column>=0))
  {
   if(pieceRowLocation[column]==(size-1))
   {
    pieceRowLocation[column]=0;
    column--;
   }
   else
   {
    pieceRowLocation[column]++;
    done=true;
   }
  }
  if(debug)
  {
   System.out.print("output=(");
   for(int i=0;i<size;i++) System.out.print(pieceRowLocation[i]);
   System.out.println(")");
  }
 }

}
