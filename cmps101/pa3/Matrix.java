//Ian Feekes
//ifeekes@ucsc.edu
//#1474914
//pa3
//Matrix.java

import static java.lang.System.*;

public class Matrix
{	
 private int nZero;		//characteristics of a matrix
 private int nSize;
 private List[] rows;	

 Matrix(int n)			//creates a new matrix
 { 
  if(n>=1)
  {
   rows = new List[n+1];			
   for(int i = 1; i<=n; i++) rows[i] = new List();
   nSize = n;
   nZero = 0;
  }
  else throw new RuntimeException("Matrix Error: N is not greater than or equal to 1");
 }

private class Entry
{
 private int column;		//characteristics of an entry
 private double value;
      	
 Entry(int n, double x)		//creates a new entry
 {
  this.column = n;
  this.value = x;
 }

	   
public String toString()	//toString for entry returns both column and value
{
 return ("("+this.column+", "+this.value+")");
}

		
public boolean equals(Object a)	//tests to see if two entries are equal
{
 Entry b;
 if( a instanceof Entry)
 {
  b = (Entry)a;
  if(b.column == this.column && b.value == this.value) return true;
 }
 return false;			//if it doesn't find an equal value between the entries it returns false by default
 }
}


   	
int getSize()
{
 return nSize;
} 

int getNNZ()
{
 return nZero;
} 
	
public boolean equals(Object x)
{
 Matrix y;
 if(x instanceof Matrix)
 {
  y = (Matrix)x;			
  if(y.getSize() != this.getSize()) return false;
  System.out.println("Equals");
  for(int i=1; i<=nSize; i++)
  {
   if(!(y.rows[i].equals(this.rows[i]))) return false;
  }	
 }
 return true;
} 

	
void makeZero()			//clears all the rows and sets nzero and nsize to 0
{
 for(int i=1; i<=nSize; i++) rows[i].clear();
 nZero = 0;
 nSize = 0;
} 

Matrix copy()
{
 Matrix n = new Matrix(getSize());
 for(int i = 1; i<= getSize(); i++)
 {
  rows[i].moveFront();
  while(rows[i].index() >= 0)
  {
   Entry temp = (Entry) rows[i].get();
   n.changeEntry(i, temp.column, temp.value);
   rows[i].moveNext();
  }
 }
 return n;
}	 

void changeEntry(int i, int j, double x)
{		
 if(1<=i && i<=getSize() && 1<=j && j<=getSize())
 {
  List L = rows[i];
  boolean colTrue = false;
  L.moveFront();			
  while(L.index() >= 0)
  {				
   Entry e = (Entry) L.get();
   colTrue = (e.column == j ? true : false);
   if(colTrue)
   {
    if(x != 0.0)
    {
     e.value = x;
     return;
    }
   else if(x == 0.0)
   {
    L.delete();
    return;
   }
  }
  L.moveNext();
 }
 if(!colTrue && x != 0.0)
 {
  L.moveFront();
  if(L.index() == -1)
  {
   L.append(new Entry(j, x));
   nZero++;
   return;
  }
  else
  {
   while(L.index() > -1 && ((Entry)L.get()).column < j) L.moveNext();
   if(L.index() > -1)
   {
    L.insertBefore(new Entry(j, x));
    nZero++;
    return;
   }
   else
   {
    L.append(new Entry(j, x));
    nZero++;
    return;
   }
  }
 }
}
else throw new RuntimeException("Error: Column or row of incorrect size");
}

	
Matrix scalarMult(double x)
{
 Matrix temp = this.copy();
 for(int i = 1; i <= temp.getSize(); i++)
 {
  temp.rows[i].moveFront();
  while(temp.rows[i].index() >= 0)
  {
   Entry ent = (Entry) temp.rows[i].get();
   temp.changeEntry(i, ent.column, (x*ent.value));
   temp.rows[i].moveNext();
  }
 }
 return temp;
}
	
Matrix add(Matrix M)
{
 if(getSize() != M.getSize()) throw new RuntimeException("Error: Cannot add matrices of different sizes");
 Matrix Ans = new Matrix(getSize());
 for(int i = 1; i <=nSize; i++)
 {
  List One = this.rows[i];
  List Two = M.rows[i];
  List Result = addHelper(One, Two);
  Ans.rows[i] = Result;
 }
 return Ans;
}
    
Matrix sub(Matrix M)		//functions just like add except we multiply all the values of one of the matrices by -1 before adding. 
{				//I probalby could have made this easier by just doing the scalar multiplication and then just calling add
 if(getSize() != M.getSize()) throw new RuntimeException("Error: Cannot subrtract matrices of different sizes");
 Matrix Ans = new Matrix(getSize());
 Matrix InM = M.scalarMult(-1);
 for(int i = 1; i <=nSize; i++)
 {
  List One = this.rows[i];
  List Two = InM.rows[i];
  List Result = addHelper(One, Two);
  Ans.rows[i] = Result;
 }
return Ans;
}
	
	
Matrix transpose()
{
 Matrix Ans = new Matrix(getSize());	//for all of these functions Ans is the matrix that I want to manipulate and eventually return 	
 for(int i = 1; i <= getSize(); i++)
 {
  rows[i].moveFront();
  while(rows[i].index() >= 0)
  {
   Ans.changeEntry(((Entry)rows[i].get()).column, i, ((Entry)rows[i].get()).value);
   rows[i].moveNext();
  }
}
return Ans;
}
	
Matrix mult(Matrix M)
{		
 if(getSize() != M.getSize()) throw new RuntimeException("Error: cannot multiply matrices of diffeing sizes");	
 Matrix Tran = M.transpose();
 Matrix Ans = new Matrix(getSize());
 for(int i = 1; i <= getSize(); i++)
 {		
  if(rows[i].length() == 0) continue;		//makes sure our matrix has enough rose
  for(int k = 1; k <= getSize(); k++)
  {			
   if(Tran.rows[i].length() == 0) continue;	//makes sure the transpose matrix has enough rows
   Ans.changeEntry(i, k, dot(rows[i], Tran.rows[k]));
  }
 }
return Ans;
}
	
public String toString()
{
 String str = "";
 for(int i = 1; i <= getSize(); i++) if(rows[i].length() > 0) str += (i + ":" + rows[i] + "\n");	//my formatting on this line might irritate a lot of people 
 return str;
}
	
private static double dot(List L, List K)
{	
 L.moveFront();
 K.moveFront();
 double ans = 0.0;		
 while(L.index() >= 0 && K.index() >= 0)
 {
  Entry e1 = (Entry)L.get();
  Entry e2 = (Entry)K.get();
  if(e1.column > e2.column) K.moveNext();
  else if(e1.column < e2.column) L.moveNext();
  else if(e1.column == e2.column)
  {
   ans += (e1.value * e2.value);
   L.moveNext();
   K.moveNext();
  }
 }
 return ans;
}


private List addHelper(List K, List Q)			//L is what we're returning and has the solutions so I called these lists to be added K and Q
{
 K.moveFront();
 Q.moveFront();
 List L = new List();		
 while(K.index() >= 0 || Q.index() >= 0)
 {
  if(K.index() >= 0 && Q.index() >= 0)
  {
   Entry Kent = (Entry)K.get();
   Entry Qent = (Entry)Q.get();
   if(Kent.column < Qent.column)
   {
    Entry ent = new Entry(Kent.column, Kent.value);
    L.append(ent);
    K.moveNext();
   }
   else if(Kent.column > Qent.column)
   {
    Entry ent = new Entry(Qent.column, Qent.value);
    L.append(ent);
    Q.moveNext();
   }
   else if(Kent.column == Qent.column)
   {
    Entry ent = new Entry(Kent.column, Kent.value + Qent.value);
    if(ent.value != 0) L.append(ent);
    K.moveNext();
    Q.moveNext();
   }
  }
  else if(K.index() >= 0 && Q.index() < 0)
  {
   Entry one = (Entry)K.get();
   Entry e = new Entry(one.column, one.value);
   L.append(e);
   Q.moveNext();
  }
  else if(K.index() < 0 && Q.index() >= 0)
  {
   Entry two = (Entry)Q.get();
   Entry e = new Entry(two.column, two.value);
   L.append(e);
   Q.moveNext();
  }
 }
 return L;
}
    
}


