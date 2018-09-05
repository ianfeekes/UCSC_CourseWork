// $Id: ubigint.cpp,v 1.14 2016-06-23 17:21:26-07 - - $

#include <cctype>
#include <cstdlib>
#include <exception>
#include <algorithm> /*ADDEDDDDD*/ 
#include <stack>
#include <stdexcept>
using namespace std;

#include "ubigint.h"
#include "debug.h"

ubigint::ubigint (unsigned long that) {
   while (that > 0) {
      ubig_value.push_back(that % 10);
      that = that/10;
   }

   DEBUGF ('~', this << " -> " << that)
}

ubigint::ubigint (const string& that) {
   for (char digit : that) {
      ubig_value.push_back(digit - '0');
   }

   reverse(ubig_value.begin(), ubig_value.end());
}

/*Code mofified to compute addition two giant lists of integers*/
/*Tests to see if it needs to do anything (if it is computing 
 *anything) and if so it loops through adding the individual digits
 *of the two numbers, keeping track of the value to carry if any. 
 *Once we have dealt with adding digits, we add the final carry and
 *then append the remaining digits of the larger number (because they
 *are represented from back to front. Return our final answer*/ 
/*We don't need to test for sineage because this is handled in 
 *bigint.cpp, not ubigint.cpp. We just assume they are of the same
 *sign */  
ubigint ubigint::operator+ (const ubigint& that) const 
{
   /*Two cases of adding 0 to a value. Just return the value*/ 
   if(ubig_value.size() == 0) return that;
   else if (that.ubig_value.size() == 0) return *this;                  
   /*Else we must perform actual computation*/ 
   else
   {
      /*toReturn is aptly named to be our final answer return value*/ 
      ubigint toReturn(0);
      /*numDigits so we know the relevant digits to add between*/ 
      int numDigits = min(ubig_value.size(), that.ubig_value.size());
      int carry = 0;
      for(int i=0; i<numDigits;i++)
      {
         int digitSum=ubig_value.at(i)+that.ubig_value.at(i)+carry; 
         carry=0; 
         if(digitSum>=10)
         {
            carry=digitSum/10;
            digitSum%=10; 
         }
         toReturn.ubig_value.push_back(digitSum); 
      }
      /*Add the carry for the final digit*/ 
      if(carry>0)toReturn.ubig_value.push_back(carry); 
      /*Now for any remaining digits in the likely event the numbers 
       *are of different lengths. Loops will append remaining*/ 
      int i=numDigits;   
      while(i < ubig_value.size()) 
      {
         toReturn.ubig_value.push_back(ubig_value.at(i));
         i++;
      }
      while(i < that.ubig_value.size()) 
      {
         toReturn.ubig_value.push_back(that.ubig_value.at(i));
         i++;
      }
     /*Trimming zeros. Modified from code in part 5c of the prompt*/
     /*while (size() > 0 and back() == 0) pop_back()*/ 
     while (toReturn.ubig_value.size() > 0 and 
            toReturn.ubig_value.back() == 0) 
         toReturn.ubig_value.pop_back();
     return toReturn;
   }
} 

/*Code modified to compute the subtraction of two giant lists
 *of Integers*/ 
/*Checks to see if any actual computation needs to be done first, 
 *then subtracts digit by digits, continuing to borrow until the 
 *second number runs out of digits. Then it appends the rest of the
 *digits from the first number, trims zeros and returns our value*/ 
ubigint ubigint::operator- (const ubigint& that) const {
   /*Testing for case that we are subtracting too large a number*/ 
   if (that > *this) 
   {
      throw domain_error 
      ("Error: subtracting larger number from a smaller number \n");
   } 
   ubigint toReturn(0);
   /*If we are subtracting two equal values we can simply return 0*/ 
   if(*this == that) return toReturn; 
   /*Else we must perform actual computation*/ 
   /*borrow is initially set to 0 and is set to 1 when "that" digit 
    *is larger than "this" digit. Its set back to 0 after debts have
    *been payed   */  
   int borrow = 0;   
   int currDigit; 
   /*Compute the actual subtraction*/   
   for(int i=0;i<that.ubig_value.size();i++)
   {
      currDigit=ubig_value.at(i); 
      currDigit-=borrow;
      borrow=0; 
      currDigit-=that.ubig_value.at(i);
      if(currDigit<0)
      {
         borrow=1;
         currDigit+=10; 
      }
      toReturn.ubig_value.push_back(currDigit); 
   }
   /*Check for any final borrows that were not carried out in the
    *for loop*/    
   int i=that.ubig_value.size(); 
   currDigit=ubig_value.at(i)-borrow; 
   toReturn.ubig_value.push_back(currDigit); 
   /*Append the rest of the digits*/ 
   for (int j=i; j < ubig_value.size(); j++) 
   {
      toReturn.ubig_value.push_back(ubig_value.at(j));
   }
   /*Another call to TZ. I might just make it a function. We'll see*/ 
   while (toReturn.ubig_value.size() > 0 and 
          toReturn.ubig_value.back() == 0) 
   toReturn.ubig_value.pop_back();
   return toReturn;
}


ubigint ubigint::operator* (const ubigint& that) const {
   ubigint toReturn(0);
   /*Checks to see if we're multiplying by 0 to save on computation*/
   if(ubig_value.size() == 0 ||
      that.ubig_value.size()==0) return toReturn;    
   /*Algorithmic copying of given code in assignment prompt*/
   /* for i -> [O,m): */ 
   for (int i = 0; i < that.ubig_value.size(); i++) 
   {
      ubigint partialProduct(0);
      /* c <- 0 */ 
      int carry=0; 
      /* for j -> [0,n): */ 
      for (int j = 0; j < ubig_value.size(); j++) 
      {
         /* d <- p(i+j)+u(i)v(j)+c */
         int currentDigit = that.ubig_value.at(i) * ubig_value.at(j) + carry;
         currentDigit%= 10;
         /* p(i+j) <- drem10 */ 
         partialProduct.ubig_value.push_back(currentDigit);
         /* c <- d/10 */  
         carry = currentDigit / 10;
      }
      if(carry>0)partialProduct.ubig_value.push_back(carry);
      /* p(i+n) <- c */ 
      /* Add a bunch of zeros to our current partial product so that
       * we can line it up properly with our final product */ 
      for(int k=0;k<i;k++)
      {
         partialProduct.ubig_value.insert(partialProduct.ubig_value.begin(),0);
      }
      toReturn = toReturn +  partialProduct;
   }
   /* MAKE A FUNCTION FOR TRIM ZEROS */ 
   while (toReturn.ubig_value.size() > 0 and toReturn.ubig_value.back() == 0) toReturn.ubig_value.pop_back();
   return toReturn;
}


/*THIS NEEDS MODIFICATION OR POSSIBLE DELETION*/ 
void ubigint::multiply_by_2() {
int carry = 0;
   for (int i = 0; i < ubig_value.size(); i++) {
      int digitProduct = (ubig_value.at(i) * 2) + carry;
      carry = 0;
if (digitProduct > 9) {
         carry = digitProduct / 10;
         digitProduct = digitProduct % 10;
      }

      ubig_value.at(i) = digitProduct;
   }
 if (carry > 0) {
      ubig_value.push_back(carry);
     }   
   
   
   while (ubig_value.size() > 0 and ubig_value.back() == 0) ubig_value.pop_back();
}

/*THIS WILL NEED MODIFICATION OR POSSIBLE DELETION*/ 
void ubigint::divide_by_2() {
  /* int remainder = 0; // because we're only ever dividing by two, remainder can only equal 0 or 5
for (int i = ubig_value.size()-1; i >= 0; i--) {
      int digitQuotient = 0;
      if (remainder > 0) {
         digitQuotient += remainder;
         remainder = 0;
      }

      digitQuotient += ubig_value.at(i) / 2;

      if (ubig_value.at(i) % 2) { // if (ubig_value.at(i) is odd) {
         remainder = 5;
      }

      ubig_value.at(i) = digitQuotient;
   }

   while (ubig_value.size() > 0 and ubig_value.back() == 0) ubig_value.pop_back();*/
   ubigvalue_t newVector(ubig_value.size());
	char carry = 0;
	for(int i = ubig_value.size()-1; i>=0; --i){
		if(ubig_value[i]  % 2 == 1){
			newVector[i] = (ubig_value[i] / 2) + carry;
			carry = 5;
		}
		else{
			newVector[i] = (ubig_value[i] / 2) + carry;
			carry = 0;
		}
	}
	
	while (newVector.size() > 0 and newVector.back() == 0) 
		newVector.pop_back();
	ubig_value = newVector; 
} 



ubigint::quot_rem ubigint::divide (const ubigint& that) const {
   if(that.ubig_value.size()==0) throw domain_error("Error: divisor is 0 \n"); 
   /*tempDivisor is a sort of placeholder for this since we don't 
    *want to alter the value of our actual divisor but we need to do
    *so in order to correctly implement egyptian division*/ 
   ubigint tempDivisor = that;
   /*Initially set our power of 2 to equal 1. It will be incremented
    *throughout the loop*/  
   ubigint pow2 = ubigint(1); 
   /*This method deals with both quotients and remainders so we must
    *initialize two separate variables for them*/  
   ubigint divideReturn = ubigint(0);
   ubigint remReturn = *this; 
   while(tempDivisor < *this)
   {
     pow2.multiply_by_2(); 
     tempDivisor.multiply_by_2(); 
   }
   ubigint loopHolder = ubigint(0);
   while(pow2 > loopHolder)
   {
      if((tempDivisor < remReturn) or (tempDivisor == remReturn))
      {
         remReturn = remReturn - tempDivisor; 
         divideReturn = divideReturn + pow2; 
         
      }
      /*THESE CAUSE SEG FAULTS DELETE LATER*/ 
      tempDivisor.divide_by_2();
      pow2.divide_by_2(); 
   }
   while (divideReturn.ubig_value.size() > 0 and divideReturn.ubig_value.back() == 0) divideReturn.ubig_value.pop_back();
   while (remReturn.ubig_value.size() > 0 and remReturn.ubig_value.back() == 0) remReturn.ubig_value.pop_back();
   return {divideReturn, remReturn}; 
  /*   static const ubigint zero = ubigint("0");
   if (that == zero) throw domain_error ("ubigint::divide: by 0");
   ubigint power_of_2 = 1;
   ubigint divisor = that; // right operand, divisor
   ubigint quotient = 0;
   ubigint remainder = *this; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      //This is bullshit
      //return{divisor, remainder}; 
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {quotient, remainder};*/
}  

ubigint ubigint::operator/ (const ubigint& that) const {
   return divide(that).first;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return divide(that).second;
}

/* Comparison operations */
bool ubigint::operator== (const ubigint& that) const {
   if (ubig_value.size() == that.ubig_value.size()) {
      for (int i = 0; i < ubig_value.size(); i++) {
         if (ubig_value.at(i) != that.ubig_value.at(i)) {
            return 0;
         }
      }
 return 1;
   } else return 0;
}

bool ubigint::operator< (const ubigint& that) const {
if (*this == that) return 0;
   if (ubig_value.size() < that.ubig_value.size()) return 1;

   if (ubig_value.size() == that.ubig_value.size()) {
if (ubig_value.size() == 0) return 0;

      for (int i = ubig_value.size()-1; i >= 0; i--) {
         if (ubig_value.at(i) > that.ubig_value.at(i)) {
            return 0;
         }
      }
 return 1;
   }
return 0;
}

ostream& operator<< (ostream& out, const ubigint& that) {
   string digitBuffer;
   int lineLength = 70;
   if (that.ubig_value.size() > 0) {
      int charCount = 0;

      for (int i = that.ubig_value.size()-1; i >= 0; i--) {
 if (charCount%(lineLength-1) == 0 and charCount != 0) out << "\\" << endl;
         out << static_cast<char>(that.ubig_value.at(i) + '0');
         charCount++;
      }
   } else { // else if ubig_value is empty, then that represents 0.
      out << '0';
   }

   return out;
}

