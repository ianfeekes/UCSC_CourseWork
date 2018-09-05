#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0)
{
   DEBUGF ('~', this << " -> " << uvalue)
}

/*Big ints have their values and a boolean determining their sign*/ 
bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

bigint::bigint (const string& that) 
{
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+() const {
   return *this;
}

bigint bigint::operator-() const {
   return {uvalue, not is_negative};
}

/*-----------------------------------------------------------------
 * Beginning of bigint functions that are actually modified below
 * ---------------------------------------------------------------*/


/*Sign testing for which function to call on addition*/ 
bigint bigint::operator+ (const bigint& that) const 
{
   /*Adding two equal values always results in 0*/ 
   if (uvalue == that.uvalue)
   {
      if(is_negative!=that.is_negative)return{ubigint(0), 0};
      return {uvalue+uvalue, is_negative}; 
   }
   /*Testing for addition of values with the same signs*/ 
   if(is_negative == that.is_negative)
   {
      return{uvalue + that.uvalue, is_negative};
   }
   /*Testing for addition of values with different signs*/ 
   /*Replace the placement of the two values if b>a and base it on b's
    *sign for the resul and subtractt*/   
   if(uvalue < that.uvalue)
   { 
      return{that.uvalue - uvalue,that.is_negative};
   }
   /*else result = a-b, pending on whatever sign a is*/ 
   return{uvalue - that.uvalue, is_negative};
}

/*Sign testing for which function to call on subtraction*/ 
bigint bigint::operator- (const bigint& that) const 
{
   /*Different signs and equal values results in zero*/ 
   if (uvalue == that.uvalue and is_negative==that.is_negative) 
      return {ubigint(0), 0};
   /*Different signs results in addition of the two values*/ 
   if(is_negative != that.is_negative)
   {
      return{uvalue + that.uvalue, is_negative}; 
   }
   /*we know signs are same at this point so there are two cases*/
   if(uvalue < that.uvalue) return{that.uvalue - uvalue, !is_negative};
   return {uvalue - that.uvalue, is_negative};
}

/*Sign testing for which function to call on multiplication*/ 
bigint bigint::operator* (const bigint& that) const {
  /*If the signs are different, negative result, else positive result*/
  if(is_negative != that.is_negative) return{uvalue * that.uvalue, 1};
  return {uvalue * that.uvalue, 0};
}

/*Sign testing for which function to call on division*/ 
bigint bigint::operator/ (const bigint& that) const {
   /*Literally same thing as multiplication*/ 
   if(is_negative!=that.is_negative) return{uvalue/that.uvalue, 1};
   return{uvalue/that.uvalue, 0};
}

/*Simply calls modulus, doesn't test for signs because I don't think
 *you can have a negative remainder*/ 
/*I wasn't sure if a modulus could be negative or not*/ 
bigint bigint::operator% (const bigint& that) const {
   return {uvalue % that.uvalue, 0};
}

/*both signs and values must be the same and then calls equals*/ 
bool bigint::operator== (const bigint& that) const {
   return uvalue == that.uvalue and is_negative == that.is_negative;
}

/*Checks the signs first and then calls the < operator ubigint*/
bool bigint::operator< (const bigint& that) const {
   /*If signs are different it depends on the sign of this*/ 
   if (is_negative != that.is_negative) 
   {
      if(is_negative) return 0;
      return 1; 
   }
   if(!is_negative) return uvalue < that.uvalue; 
   /*When working with two negative numbers we must reverse logic*/
   return !(uvalue == that.uvalue) and !(uvalue < that.uvalue); 
}

/*This remains unchanged*/ 
ostream& operator<< (ostream& out, const bigint& that) {
   return out << (that.is_negative ? "-" : "")
              << that.uvalue;
}

