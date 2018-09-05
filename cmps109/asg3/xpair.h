// $Id: xpair.h,v 1.4 2014-06-27 17:39:08-07 - - $

#ifndef __XPAIR_H__
#define __XPAIR_H__

#include <iostream>

using namespace std;
/*This class doesn't require any work. It simply functions like the
 *pair library. The template allows us to construct a pair with first
 *and second being two different (or possibly the same) types. This 
 *will likely be used in the key value functionality that I will be 
 *working on*/ 

//
// Class xpair works like pair(c++).
//
// The implicitly generated members will work, because they just
// send messages to the first and second fields, respectively.
// Caution:  xpair() does not initialize its fields unless
// First and Second do so with their default ctors.
//

template <typename First, typename Second>
struct xpair {
   First first{};
   Second second{};
   xpair(){}
   xpair (const First& first, const Second& second):
               first(first), second(second) {}
};

template <typename First, typename Second>
ostream& operator<< (ostream& out, const xpair<First,Second>& pair) {
   out << "{" << pair.first << "," << pair.second << "}";
   return out;
}

#endif

