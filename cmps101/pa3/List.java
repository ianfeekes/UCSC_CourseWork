//Ian Feekes
//ifeekes@ucsc.edu
//#1474914
//pa3
//List.java


//Note that most of this is pretty much copied from my list in pa1, with only a little debugging to make it actually work.
import static java.lang.System.*;

public class List
{
 private Node first;		//characteristics of a list
 private Node last;
 private Node cursor;
 private int size;

 List()				//creates an empty list
 {
  first = null;
  last = null;
  cursor = null;
  size = 0;
 }

 private class Node
 {
  Object data; 			//characteristics of a node
  Node prev;
  Node next; 

  Node(Object insertData)	//creates an empty node
  {
   this.data = insertData; 
   this.prev = null;
   this.next = null;
  }

  public String toString()
  {
   return String.valueOf(data);
  }

  public boolean equals(Object x)
  {
   Node n; 
   if(x instanceof Node)
   {
    n = (Node)x;
    if(this.data.equals(n.data)) return true;
   }
   return false; 
  }
 }

 int length()
 {
  return size; 
 }

 int index()
 {
  if(cursor == null) return -1;
  else
  {
   Node n = first;
   int i = 0;
   while(n != null)
   {
    if(n == cursor) return i;
    n = n.next;
    i++;
   }
  }
  return -1;
 } 

 Object front()
 {
  if(length() > 0) return first.data;
  else throw new RuntimeException("Error: Cannot call front on an empty list\n");
 }

 Object back()
 {
  if(length() > 0) return last.data; 
  else throw new RuntimeException("Error: Cannot call back on an empty list\n");    
 }

 Object get()
 {
  if(length() > 0 && index() >= 0)return cursor.data;
  else
  {
   System.out.println("length = "+length() + " " +"index ="+index());
   throw new RuntimeException("Error: calling get on either an empty list or a list without an initialized cursor\n");
  }
 } 

 boolean equals(List L)
 {
  if(this.size != L.size) return false;
  Node X = this.first;
  Node Y = L.first;
  for(int i = 0; i<size ; i++)
  {
   if(X.data != Y.data){
               return false;
            }
            X = X.next;
            Y = Y.next;
         }
         return true;
   } 


 void clear()
 {
  first = null;
  last = null;
  cursor = null;
  size = 0;
 }
  
 
 //All of these methods moveFront moveBack movePrev moveNext just return, the pa didn't specify if an exception or error message should be displayed
 void moveFront()
 {
  if(length() == 0) return; 
  else cursor = first;
 }

 void moveBack()
 {
  if(length() == 0) return; 
  else cursor = last;
 }

 void movePrev()
 {
  if(index() == -1) return;
  else cursor = cursor.prev;
 }

 void moveNext()
 {
  if(index() == -1) return; 
  else cursor = cursor.next;
   }

  void prepend(Object data)
  {
   Node n = new Node(data);
  if(length() == 0){
        first = n;
        last = n;
        size = 1;
  }
  else
  {
   n.next = first; 
   first.prev = n;
   first = n;
   size++;			//increments size
  }
 }

 void append(Object data)
 {
  Node n = new Node(data);
  if(length() ==0)
  {
   first = n;
   last = n;
   size = 1;
  } 
  else
  {
   n.prev=last;
   last.next = n;
   last = n;
   size++;			//increments size
  }
 }

 void insertBefore(Object data)
 {
  if(cursor==first) prepend(data);
  else if(length()>0)
  {   
   Node n = new Node(data);
   n.prev = cursor.prev;
   n.next = cursor;
   n.prev.next = n;
   cursor.prev = n;
   size ++;			//increments size
  }
 }


 void insertAfter(Object data)
 {
  if(cursor == last) append(data);
  else if(length() > 0)
  {       
   Node n = new Node(data); 
   n.prev = cursor;
   n.next = cursor.next;
   n.next.prev = n;
   cursor.next = n;    
   size ++;			//increments size
     }
   }

 void deleteFront()
 {
  if(length()>0)		//precondition
  {
   first = first.next;
   first.next.prev = null;
   size--; 			//decrements size
  } 
  else throw new RuntimeException("Error: Cannot delete front of an empty list\n");
 }

 void deleteBack()
 {
  if(length()>0)		//precondition
  {
   last = last.prev;
   last.prev.next = null;
   size--; 			//decrements size
  }
  else throw new RuntimeException("Error: Cannot delete back of an empty list\n");
 }

 void delete()
 {
  if(length()>0 && index()>=0)	//checks precondition: doesn't throw an exception or display an error message. Should it??
  {
   if(cursor == first)		//we already have a method for deleting the first index
   {
    deleteFront();
    cursor = null;
   }
    else if(cursor == last)	//we have a method for this too
   {
    deleteBack();
    cursor = null;
   }
   else
   {
    cursor.prev.next = cursor.next;
    cursor.next.prev = cursor.prev;
    cursor = null;
    size--;			//decrements size
   }
  }
 }

 public String toString()
 {
  Node N = first;
  String str = "";
  while(N != null)
  {
   str += N.data + " ";
   N = N.next;
  }
  return str;
 }

}



 
