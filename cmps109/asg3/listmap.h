// $Id: listmap.h,v 1.14 2018-02-20 14:59:38-08 - - $

#ifndef __LISTMAP_H__
#define __LISTMAP_H__

#include "xless.h"
#include "xpair.h"

/*Ian Feekes
 *#1474914 
 *ifeekes
 *listmap.h*/ 

/*This requires no modification. It's purpose it to illustrate the 
 *functionality of C++ templates*/ 

template <typename Key, typename Value, class Less=xless<Key>>
class listmap {
   public:
      using key_type = Key;
      using mapped_type = Value;
      using value_type = xpair<const key_type, mapped_type>;
   private:
      Less less;
      struct node;
      struct link {
         node* next{};
         node* prev{};
         link (node* next, node* prev): next(next), prev(prev){}
      };
      struct node: link {
         value_type value{};
         node (node* next, node* prev, const value_type&);
      };
      /*anchor is just the node it is pointing to, it is given a link
       *with itself initially*/   
      node* anchor() { return static_cast<node*> (&anchor_); }
      link anchor_ {anchor(), anchor()};
      int size{}; /*Added field for keeping track of the size of the listmap*/ 
   public:
      class iterator;
      listmap(){};
      listmap (const listmap&);
      listmap& operator= (const listmap&);
      ~listmap();
      iterator insert (const value_type&);
      iterator find (const key_type&);
      iterator erase (iterator position);
      iterator begin() { return anchor()->next; }
      iterator end() { return anchor(); }
      bool empty() const { return begin() == end(); }
      /*Added for use of users inputting "=" where the entire listmap
       *needs to be outputted, which cannot be properly implemented 
       *in main.cpp, so it becomes a listmap function*/  
      void toString(); 
      /*Outputs all keys matching the value argument like toString*/
      void toStringVal(const value_type&); 
      /*Removes all data necessary*/ 
      void freeNodes();
};

template <typename Key, typename Value, class Less>
class listmap<Key,Value,Less>::iterator {
   private:
      friend class listmap<Key,Value,Less>;
      listmap<Key,Value,Less>::node* where {nullptr};
      iterator (node* where): where(where){};
   public:
      iterator(){}
      value_type& operator*();
      value_type* operator->();
      iterator& operator++(); //++itor
      iterator& operator--(); //--itor
      void erase();
      bool operator== (const iterator&) const;
      bool operator!= (const iterator&) const;
};

#include "listmap.tcc"
#endif

