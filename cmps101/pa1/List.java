//Ian Feekes
//#1474914
//ifeekes@ucsc.edu
//PA1
//List.java

public class List
{
 private Node first;
 private Node last;
 private Node cursor; 
 private int length;

 List()//constructor for list. Default is empty
 {
  first = null;
  last = null; 
  cursor = null; 
  length = 0; 
 }

 private class Node 
 {
  int data; 
  Node prev;
  Node next; 

  Node(int d)//constructor for Node
  {
   this.data=d;
   prev=null;//since this is a double linked list we have both a next node and a previous node
   next=null;
  }
 
  public String toString()
  {
   return String.valueOf(data);
  }
 }

 //access functions
 
 int length()//returns number of elements in the list
 {
  return length;
 }

 int index()//if cursor is defined it returns cursor element else it returns -1
 {
  if(cursor!=null)
  { 
   Node A = first;
   int i = 0;
   while(A != null)
   {
    if(A == cursor)return i;
    A = A.next;
    i++;
   }
  }
  return -1;//default is -1 if we can't find anything
 }

 int front()//returns the front element if length() >0
 {
  if(length() > 0) return first.data;
  else throw new RuntimeException("Error: cannot compute front element of an empty list");
 } 

  int back()//returns the back element if length() > 0
  {
   if(length() > 0) return last.data;
   else throw new RuntimeException("Error: cannot compute back element of an empty list");
  }  

 int get()//returns cursor element assuming length and index are greater than or equal to 0
 {
  if((length() > 0)&&(index() >= 0)) return cursor.data;
  else 
  {
   throw new RuntimeException("cannot compute the cursor. Cursor is undefined or list is empty");
  }
 }

 boolean equals(List L)//returns true if the list and L are the same, ignoring the indexes of both
 {
  if(this.length!=L.length) return false;
  Node N = this.first;
  Node O = L.first;
  for(int i = 0; i<this.length; i++)
  {
   if(N.data != O.data) return false;
   N=N.next;
   O=O.next;
  }
  return true;
 }

 //Manipulation Procedures

 void clear()//resets the list to its original empty state
 {
  first = null;
  last = null;
  cursor = null; 
  length = 0;
 }

 void moveFront()//places the cursor to the front of the list if the list isn't empty. If it's empty do nothing
 {
  if(length()==0) return;
  cursor = first;
 }

 void moveBack()//places the cursor to the back of the list if the list isn't empty. If it's empty do nothing
 {
  if(length()==0) return;
  cursor = last;
 }

 void movePrev()//if cursor is defined and not at the front, move it one step closer to the front. If cursor is at the front it becomes undefined. If cursor is undefined do nothing. 
 {
  if(index()==-1) return;
  else if(cursor==first)
  {
   cursor=null;
  } 
  else cursor=cursor.prev;
 }

 void moveNext()//same thing just move it towards the back 
 { 
  if(index()==-1) return;
  else if(cursor==last)
  {
   cursor=null;
  }
  else cursor=cursor.next;
 }

 void prepend(int data)//new element goes at the front of the list. If list is non-empty put it before the front Node
 { 
  Node N = new Node(data);
  if(length()==0)
  {
   first = N;
   last = N;
   length = 1;
  }
  else
  {
  N.next=first;
  first.prev=N;
  first=N;
  length++;
  
  }
 }

 void append(int data)//new element at back
 {
  Node N = new Node(data);
  if(length() == 0)
  {
   first = N;
   last = N;
   length = 1;
  }
  else
  {
   N.prev=last;
   last.next=N;
   last = N;
   length++;
  }
 }

 void insertBefore(int data)//inserts a new element before the cursor assuming the length>=0 && index>=0
 {
  if(cursor==first) prepend(data);
  else if(length()>=0)
  { 
   Node N = new Node(data);
   N.prev = cursor.prev;
   N.prev.next = N; 
   cursor.prev=N;
   length++;
  }
 }

 void insertAfter(int data)//inserts a new element after the cursor assuming the length>=0 && index>=0
 {
  if(cursor==last) append(data);
  else if(length() >0)
  {
   Node N = new Node(data); 
   N.prev = cursor;
   N.next.prev = N;
   cursor.next = N;
   length++;
  }
 }

 void deleteFront()//deletes front element if length>0
 {
  if(length()>0)
  {
   first = first.next;
   first.next.prev=null;
   length--;
  }
   else throw new RuntimeException("Cannot delete the front Node of an empty list");
 }

 void deleteBack()//deletes back element if length>0
 {
  if(length()>0)
  {
   last = last.prev;
   last.prev.next = null;
    length--;
  }
  else throw new RuntimeException("Cannot delete the back Node of an empty list");
 }

 void delete()//deletes cursor element, making the cursor undefined. Pre: length>0, index>=0
 {
  if((length()>0)&&(index()>=0))
  {
   if(cursor==first)
   {
    deleteFront();
    cursor=null;
   }
   else if(cursor==last)
   {
    deleteBack();
    cursor=null;
   }
   else
   {
    cursor.prev.next = cursor.next;
    cursor.next.prev = cursor.prev;
    cursor = null;
    length--;
   }
  }
 }

 //Other Methods:
 
 public String toString()//writes out the list with spaces between each integer(each Node's data)
 {
  Node N = first;
  String str = "";
  while(N!=null)
  {
   str+= (N.data+" ");
   N = N.next;
  }
  return str; 
 }

 List copy()//returns an exact copy of your list, but with an undefined cursor
 {
  List L = new List(); 
  Node N = first;
  while(N!=null)
  {
   L.append(N.data);
   N = N.next;
  }
  return L;
 }

}
