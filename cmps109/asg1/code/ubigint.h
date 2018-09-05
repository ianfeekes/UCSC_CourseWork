// $Id: ubigint.h,v 1.11 2016-03-24 19:43:57-07 - - $

#ifndef __UBIGINT_H__
#define __UBIGINT_H__

#include <exception>
#include <iostream>
#include <limits>
#include <utility>
using namespace std;

#include "debug.h"
#include "relops.h"

class ubigint {
   friend ostream& operator<< (ostream&, const ubigint&);
   private:


      using udigit_t = unsigned char;
      using ubigvalue_t = vector<udigit_t>;
      ubigvalue_t ubig_value;


	/*He adds this shit*/ 
       using quot_rem = pair<ubigint,ubigint>;
	 quot_rem divide (const ubigint&) const;
      void multiply_by_2();
      void divide_by_2();
      void trimZeros(); 

	/*Original code we are prompted to replace*/ 
      /*using unumber = unsigned long;
      unumber uvalue {};*/ 
   public:

      ubigint() = default; // Need default ctor as well.
      ubigint (unsigned long);
      ubigint (vector<unsigned char>); /*might delete this later we'll see*/ 
      ubigint (const string&);

      ubigint operator+ (const ubigint&) const;
      ubigint operator- (const ubigint&) const;
      ubigint operator* (const ubigint&) const;
      ubigint operator/ (const ubigint&) const;
      ubigint operator% (const ubigint&) const;

      bool operator== (const ubigint&) const;
      bool operator<  (const ubigint&) const;
};

#endif

