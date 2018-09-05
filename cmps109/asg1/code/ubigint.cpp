#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "ubigint.h"
#include "debug.h"
/*ubigint.cpp 
 *contains the computational functions for large vectors of digits, 
 *signs are taken care of in bigint.cpp 
 *cmps109 asg1 
 *Ian Feekes
 *ifeekes@ucsc.edu
 *#1474914
 */ 


/*Creates a ubigint with the values from a long, simply appending
 *each digit to our bigint until the long has run out of digits*/
ubigint::ubigint (unsigned long that) 
{
   while(that > 0)
   {
      ubig_value.push_back(that % 10);
      that /=10;
   }  
}

/*Creates a ubigint with the values from the string, reversing the
 *digits afterwards because of how they must be displayed*/ 
ubigint::ubigint (const string& that) 
{
   for(int i=0;i<that.size();i++)
   {
      ubig_value.push_back(that.at(i) - '0');
   }
  int n = ubig_value.size(); 
  for (int i = 0; i < n / 2; i++)
        swap(ubig_value.at(i), ubig_value.at(n-i-1));
}

/*This function is called for all addition purposes. It checks for 
 *trivial cases and if none are applicable then it adds the two 
 *numbers, digit-by-digit and carrying anything > 10. It then appends
 *remaining digits of the larger number and makes a last call for 
 *carries. It trims the result and returns it*/ 
ubigint ubigint::operator+ (const ubigint& that) const 
{
   /*Trivial cases of adding zero to the number results in itself*/
   if(*this==0) return that; 
   if(that==0) return *this; 
   /*The number of min digits is for our first loop of computation*/
   int minDigits = min(ubig_value.size(), that.ubig_value.size());
   /*Iterates through the digits of the numbers while they line up
    *and adds the values between them, taking into account the 
    *carries, appending them to toReturn*/  
   ubigint toReturn = 0;
   int carry = 0; 
   for(int i=0;i<minDigits;i++)
   {
      int currentDigit = ubig_value.at(i)+that.ubig_value.at(i)+carry;
      carry=currentDigit/10; 
      currentDigit%=10; 
      toReturn.ubig_value.push_back(currentDigit); 
   }
   int maxDigits = max(ubig_value.size(), that.ubig_value.size());
   /*We then iterate through the number with the larger quantity of
    *digits and append the remainder to toReturn. We still take the
    *carry into account for safety's sake*/  
   for(int j=minDigits;j<maxDigits;j++)
   {
      int currentDigit; 
      if(j<ubig_value.size()) currentDigit=ubig_value.at(j);
      else currentDigit=that.ubig_value.at(j);
      /*This carry stuff is a case only for the first iteration*/ 
      currentDigit+=carry;
      carry=currentDigit/10;
      currentDigit%=10; 
      toReturn.ubig_value.push_back(currentDigit); 
   }
   if(carry>0) toReturn.ubig_value.push_back(carry); 
   /*Call to trimZeros to refine our answer*/ 
   toReturn.trimZeros(); 
   return toReturn;   
}

/*This function is called every time we are subtracting a ubigint from
 *another and can handle giant lists of digits. It simply tests to see
 *if computation is needed and if not it iterates through the smaller
 *number, subtracting from the larger and handling borrow. It then 
 *appends the remaining digits to our difference, trims zeros and
 *returns our final computed value*/ 
ubigint ubigint::operator- (const ubigint& that) const {
   ubigint toReturn(0);
   int borrow = 0;
   for(int i=0;i<ubig_value.size();i++)
   {
      int currDigit = ubig_value.at(i) - borrow;
      /*For if we've already iterated through all of that's digits*/
      if(i<that.ubig_value.size()) currDigit-=that.ubig_value.at(i);
      //borrow = currDigit/10; 
      if(currDigit<0)
      {
         borrow=1; 
         currDigit+=10;
      }
      else borrow = 0; 
      toReturn.ubig_value.push_back(currDigit); 
   }
   toReturn.trimZeros(); 
   return toReturn;
}

/*This function handles the computation of multiplication. It first
 *looks for the trivial cases and then it iterates in a double
 *loop of digits to find the partial products and add up the partial
 *products after zeros have been added as digit holder sfor each 
 *partial product. It then trims the zeros of our final product and 
 *returns it. */ 
ubigint ubigint::operator* (const ubigint& that) const {
   /*Trivial cases settled*/
   if(*this == 0 or that == 0) return 0; 
   if(*this ==1) return that; 
   if(that==1) return *this;
   ubigint toReturn(0);
   for (int i=0;i<ubig_value.size();i++) 
   {
      /*p is for partial product, d is our current digit, carry */ 
      ubigint p(0);
      int d = 0;
      int carry = 0;
      for (int j = 0; j < that.ubig_value.size(); j++) 
      {
         /*Compute the current digit as well as a current carry*/
         d = (ubig_value.at(i) * that.ubig_value.at(j)) + carry;
         carry = d / 10;
         d %= 10;
         p.ubig_value.push_back(d);
      }
      /*If we have a carry we push it back too. This is necessary for 
       *the computation of the final digit of each of the partial
       *products*/    
      if(carry >= 1) p.ubig_value.push_back(carry);
      for(int k=0;k<i;k++)
      {
         /*We want to use insert rather than push back so that we 
          *append zeros to the end rather than the front from our
          *perspective*/   
         p.ubig_value.insert(p.ubig_value.begin(), 0); 
      }
      toReturn = toReturn + p;
      /*In order to avoid segmentation faults we clear the vector 
       *after each iteration of our initial for loop*/    
      p.ubig_value.clear();
   }
   toReturn.trimZeros(); 
   return toReturn;
}

/*This helper function will be called before returning the value in
 *almost all computational arithmetic functions. It deletes the zeros
 *at the end of a ubigint vector to avoid nasty problems*/ 
void ubigint::trimZeros()
{
   while(ubig_value.size()>0 and ubig_value.back()==0) 
   {
      ubig_value.pop_back();
   }
}

/*Since add has already been implemented and computational code isn't
 *required for this it just adds the number to itself because thats
 *how it was done in the ocaml lab of cs112*/ 
void ubigint::multiply_by_2() {
*this = *this + *this; 
}


/*Helper function for divide, it divides a bigint by 2 by iterating
 *through its digits with the understanding that there is no carry if
 *the original digit was even, and that it is 5 if the original digit
 *was odd. It then trims zeros*/
void ubigint::divide_by_2()
{
   int carry = 0; 
   for (int i = ubig_value.size()-1; i >= 0; i--) 
   {
      /*Our current digit as we iterate through all the digits of our
       *bigint is the carry from the previous digit, if any, plus
       *the actual digit divided by 2*/  
      int currDigit = 0 + carry + (ubig_value.at(i) / 2);
      carry=0;
      /*When dividing by 2, if a digit is even there is no
       *remainder, else we need to set it to 5 if it's an odd digit*/  
      if(ubig_value.at(i) % 2 !=0) carry = 5;
      ubig_value.at(i) = currDigit;
   }
   /*Call to trim zeros with *this gave me problems so pasted it in*/
   while (ubig_value.size() > 0 and ubig_value.back() == 0) 
   {
      ubig_value.pop_back();
   }
}

/*Method for computing both the quotient and the remainder. It is 
 *essentially the same algorithm as originally given, just modified
 *to work with big ints. It initially sets values for our divisor,
 *power of two, and remainder, and it loops through to find all the 
 *powers of two that can fit into our dividend. It then increments
 *the quotient by the powers of two that work best, starting from 
 *greatest to least, and for each of these it decrements the remainder
 *It then trims the zeros and returns the quotient and the remainder*/
ubigint::quot_rem ubigint::divide (const ubigint& that) const
{
   ubigint zero(0); 
   /*We want to throw an error when dividing by zero*/ 
   if(that==0) throw domain_error("Error: udivide by zero \n");
   /*All numbers go into zero 0 times with no remainder*/ 
   if(*this==0) return {*this,*this}; 
   ubigint pow2 = 1; 
   /*Quotient will eventually be incremented by powers of two*/ 
   ubigint quotient(0); 
   /*Remainder will be decremented by divisors*/ 
   ubigint remainder = *this; 
   /*We don't want to actually manipulate the divisor passed in*/ 
   ubigint divisor = that; 
   while(divisor < remainder)
   {
      divisor.multiply_by_2(); 
      pow2.multiply_by_2(); 
   }
   /*This is the important part computationally*/ 
   while(pow2 > zero)
   {
      /*If this current divisor^pow2 < remainder, increment quotient
       * and decrement remainder*/      
      if(remainder > divisor or remainder == divisor)
      {
         remainder = remainder - divisor; 
         quotient = quotient + pow2; 
     }
      /*continue to interate backwards through our powers of two */
      divisor.divide_by_2(); 
      pow2.divide_by_2(); 
   }
  /*Trim the zeros of the quotient and remainder*/ 
  quotient.trimZeros();
  remainder.trimZeros();  
  /*Quotient is the first value, for division, and remainder is the 
   *second value, for modulus as shown in below functions*/  
  return{quotient, remainder}; 
} 


/*Since our egyptian devision ought to cover both quotients and 
 *remainders these helper functions simply pull out whichever of the
 *two we are currently seeking*/ 
ubigint ubigint::operator/ (const ubigint& that) const 
{
   return divide(that).first;
}

/*Pulls out remainder from divide*/ 
ubigint ubigint::operator% (const ubigint& that) const
{
   return divide(that).second;
}

/*Fairly straightforward, checks if two bigints are equal by looking
 *at their sizes to see if its trivial. If they have equal sizes it 
 *iterates through each digit and checks for equality*/ 
bool ubigint::operator== (const ubigint& that) const 
{
   /*If the two numbers have a different quantity of digits then we
    *know they aren't equivalent already*/    
   if(ubig_value.size()!=that.ubig_value.size()) return 0; 
   /*I'm assuming nothing == nothing. Hopefully this case never needs
    *to be actually tested*/ 
   if(ubig_value.size()==0) return 1; 
   /*Else iterate through all the digits and compare to see if there 
    *are any inequalities*/   
   for(int i=ubig_value.size()-1; i>=0;i--)
   {
      if(ubig_value.at(i)!=that.ubig_value.at(i)) return 0;
   }
   return 1;
}

/*Operator to compare to see if this is less than that. First checks
 *the trivial cases of digit count. Only if the two numbers have the
 *same quantity of digits do we actually need to iterate through and
 *check*/ 
bool ubigint::operator< (const ubigint& that) const
{ 
   /*If that has more digits than this then we're done. It's true*/ 
   if(ubig_value.size() < that.ubig_value.size())return  1;
   if(*this==that)return 0;
   /*outlier case of nothing being compared needs to be dealt with*/
   if(ubig_value.size()==0)return 0;
   /*By now we know that this size is greater or equal to that size*/
   /*If the two numbers have the same quantity of digits then we must
    *iterate through and check*/   
   if(ubig_value.size()==that.ubig_value.size())
   {
      /*Starts backwards to look at higher-order digits*/ 
      for(int i=ubig_value.size()-1;i>=0;i--)
      {
         /*We must have an if/else for comparing the digits to find 
          *which is larger, if they are equal it will simply continue
          *to iterate until it finds a difference in digits as the
          *method already covers if the values are the same, so we 
          *already know at least one digit between the two bigints is
          *different by now. This was a huge bug for me.*/    
         if(ubig_value.at(i)>that.ubig_value.at(i)) return 0;
         else if(ubig_value.at(i)<that.ubig_value.at(i))return 1;
      }
   } 
   /*Else we know that this has more digits than that: return false*/ 
   return 0;
}


/*Properly formats our bigints as dc does. Checks to see if we need
 *to do anything, if so we represent our bigint as a string of chars
 *starting from high end digits and append them to output, adding
 *slashes and new lines when appropriate and then returning it*/ 
ostream& operator<< (ostream& out, const ubigint& that)
{
   /*We want to represent our output as a string of characters because
    *there may be positive or negative values, new lines, etc. that 
    *are not easily converted from just integers*/   
   string toReturn;
   /*Trivial case of printing nothing*/ 
   if(that.ubig_value.size()==0)
   {
       toReturn = '0';
       return out << toReturn; 
   }
   else
   {
     int charOnLine = 0; 
     /*Iterates starting from the higher-order digits of the big int,
      *if it is at the end of the line(lines are 70 chars in dc) then
      *it displays a '\' and continues to iterate on the line below. 
      *charOnLine is a separate variable used to keep track of this
      *because we don't want to manipulate i apart from the loop 
      *itself, and adding the slash character would require that.*/    
     for(int i=that.ubig_value.size()-1; i>=0;i--)
     {
        /*If statement deals with case of being at end of line*/ 
        if(charOnLine>0 and charOnLine%69==0)
        {
           /*Strings are treated as char vectors*/ 
           toReturn.push_back('\\'); 
           toReturn.push_back('\n');
           charOnLine=0;  
        }
        /*No matter what, we want to spit out the current digit of 
         *the bigint we are working with*/     
         toReturn.push_back(that.ubig_value.at(i) + '0');
         charOnLine++; 
      }
      /*Returns properly-formatted bigint char vector*/ 
      return out << toReturn;
   }
} 

