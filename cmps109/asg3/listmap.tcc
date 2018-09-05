// $Id: listmap.tcc,v 1.11 2018-01-25 14:19:14-08 - - $

#include "listmap.h"
#include "debug.h"
/*Listmap.tcc 
 *Ian Feekes #1474914
 *ifeekes@ucsc.edu
 *contains all listmap template functions for asg3 cmps109
 *All work done without a partner*/ 


//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (node* next, node* prev,
                                     const value_type& value):
            link (next, prev), value (value) {
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//

/*template key value destructor method for listmap*/
/*Goes throug the listmap erasing all of its nodes, then deleting
 *the back nodes' data, setting them to nullptrs first*/  
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap() {
   DEBUGF ('l', reinterpret_cast<const void*> (this));
   if(size>0)
   {
      while(anchor()!=anchor()->next)
      {
         erase(begin()); 
      } 
   }
}

//
// iterator listmap::insert (const value_type&)
//
/*checks to see various cases for adding new data. If a key already
 *exists, we simply overwrite the value. If the listmap is empty then
 *we initialize the new node as the anchor values. Else we iterate
 *through to find the proper order for insertion of the new node, 
 *initialize it with the data arguments, and link it with the rest of
 *the listmap*/ 
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::insert (const value_type& pair) {
   DEBUGF ('l', &pair << "->" << pair);
   /*Case we are dealing with an emtpy listmap*/  
   if(size==0 or begin()==end())
      {
         /*This will be the one and only node in this listmap*/
         node* n = new node(anchor(), anchor(), pair);
         anchor()->next =n; anchor()->prev = n;
         ++size;
         return n;
      }
   /*If the pair passed into the arguments for insertion already has
    *an existing key in the listmap then we overwrite the value for 
    *the pre-existing key*/
   if(find(pair.first)!=nullptr and find(pair.first)!=end()) 
   {  
      iterator temp = find(pair.first); 
      temp->second = pair.second; 
      return temp; 
   }
   else /*Else we must insert a new node in a non-empty list*/ 
   {
         /*Else find the proper place to insert the new data, create
          *a new node, and link it with the rest of the list*/   
         iterator i = begin(); 
         node* n = anchor()->next; 
         while(i!=end() and less(i->first, pair.first))
         {
             ++i; 
             n=n->next; 
             if(i==nullptr) break; 
         } 
         node* toAdd = new node(n, n->prev, pair);
         n->prev->next = toAdd; 
         n->prev = toAdd; 
         ++size; 
         return toAdd; 
   }
} 

//
// listmap::find(const key_type&)
//
/*Starts at the beginning of the listmap. To avoid seg-faults and 
 *other strange errors, it first checks for the border case of 
 *calling find on an empty listmap. Else it parses through in O(n) 
 *time searching for the specified key and returns it when it is 
 *found. If the key passed into the arguments does not exist then it
 *will return a pointer to the back of the list*/ 
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) {
   DEBUGF ('l', that);
   node* n = anchor()->next; ; 
   if(size==0) return end(); 
   while(n!=anchor())
   { 
      if(n->value.first == that) return n;
      n=n->next; 
   }
   return end(); 
}

//
// iterator listmap::erase (iterator position)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::erase (iterator position) {
   DEBUGF ('l', &*position);
   /*If erase is called on an empty list we don't have to do nything
    *so immediately returning a null pointer lets us know it was 
    *called on an empty list and allows us to avoid seg faults*/   
   if(size==0) return nullptr; 
   node* n = anchor()->next; 
   /*Find the position of the node we want to erase*/ 
   while(n->value.first!=position->first and n!=anchor())
   {
      n = n->next; 
   } 
   /*If we have found the position iterator that we want to delete*/ 
   if(n!=anchor())
   {
      /*Link its neighbors with eachother for safe removal*/ 
      n->prev->next = n->next; 
      n->next->prev = n->prev; 
      /*destroy the node's data and then safely delete it*/ 
      n->next = nullptr;   
      n->prev = nullptr; 
      --size; 
      delete n; 
   }
   /*If we reached the end of the list without finding the node we 
    *want to erase we do nothing. iterator will point to the position
    *previously occupied by the node we just deleted, or the end of 
    *the list, pending on if it was found or not*/    
   return iterator(); 
}

/*Used to free the list*/ 
template<typename Key, typename Value, class Less>
void listmap<Key, Value, Less>:: freeNodes()
{
   if(size==0)return; 
   node* n = anchor()->next; 
   while(n!=anchor())
   {
      node* toFree = n; 
      n=n->next; 
      toFree->next=nullptr; 
      toFree->prev=nullptr; 
      delete toFree; 
   }
   size=0; 
}

/*Added listmap function for use of printing the entire listmap if the
 *user enters a '='. If listmap is empty it returns to avoid errors
 *and seg faults, else it iterates through each key and value (which
 *are already sorted) and outputs its contents in correct format*/ 
template<typename Key, typename Value, class Less>
void listmap<Key, Value, Less>:: toString()
{
   /*We want to avoid having strange errors and seg faults, so if the
    *listmap to be outputted is empty we simply create a new line and
    *return without reading the contents of any nodes*/   
   if(size==0)
   { 
      cout<<endl; 
      return; 
   }
   /*Create a node at the beginning of the listmap*/ 
   node* n = anchor()->next; 
   /*Iterate through listmap in O(n) time outputting keys and values 
    *of each listmap entry in lexicographical order in format based 
    *on assignment specifications*/    
   while(n!=anchor())
   {
      cout<<n->value.first<<" = "<<n->value.second<<endl;
      n=n->next; 
   }
}

/*Behaves very similarly to the normal toString in its algorithmic
 *behavior. It simply iterates through the list, outputting keys
 *that contain the given value, and if none exist it prints a message
 *indicating this to avoid user confusion*/ 
template<typename Key, typename Value, class Less> 
void listmap<Key, Value, Less>:: toStringVal(const value_type& pair)
{
   if(size==0)
   {
      cout<<"No keys found in empty list"<<endl; 
      return; 
   }
   node* n = anchor()->next;
   int numKeys = 0;  
   while(n!=anchor())
   {
      if(n->value.second == pair.first)
      {
         ++numKeys; 
         cout<<n->value.first<<" = "<<n->value.second<<endl; 
      }
      n=n->next; 
   }
   if(numKeys==0)cout<<"No keys found for given value"<< endl; 
} 

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type&
listmap<Key,Value,Less>::iterator::operator*() {
   DEBUGF ('l', where);
   return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type*
listmap<Key,Value,Less>::iterator::operator->() {
   DEBUGF ('l', where);
   return &(where->value);
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++() {
   DEBUGF ('l', where);
   where = where->next;
   return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator--() {
   DEBUGF ('l', where);
   where = where->prev;
   return *this;
}

//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator!=
            (const iterator& that) const {
   return this->where != that.where;
}

