(* $Id: bigint.ml,v 1.5 2014-11-11 15:06:24-08 - - $ *)
(* bigint.ml - 
   contains functions for computing arithmetic for use in dc.ml 
   asg2 
   Ian Feekes
   ID: 1474914
   
   Miriam del Cerro
   ID: 1450240 
 *)


open Printf
open List   (* for easy access of fuctions like length *) 

module Bigint = struct   (*bigint.mli is the module we are using*)

    (*there is a type called sign which is pos or neg, enum type dec*)
    type sign     = Pos | Neg 
    type bigint   = Bigint of sign * int list
    let  radix    = 10
    let  radixlen =  1

    let car       = List.hd
    let cdr       = List.tl
    let map       = List.map
    let reverse   = List.rev
    let strcat    = String.concat
    let strlen    = String.length
    let strsub    = String.sub
    let zero      = Bigint (Pos, [])

    let charlist_of_string str = 
        let last = strlen str - 1
        in  let rec charlist pos result =
            if pos < 0
            then result
            else charlist (pos - 1) (str.[pos] :: result)
        in  charlist last []

    let bigint_of_string str =
        let len = strlen str
        in  let to_intlist first =
                let substr = strsub str first (len - first) in
                let digit char = int_of_char char - int_of_char '0' in
                map digit (reverse (charlist_of_string substr))
            in  if   len = 0
                then zero
                else if   str.[0] = '_'
                     then Bigint (Neg, to_intlist 1)
                     else Bigint (Pos, to_intlist 0)

    let string_of_bigint (Bigint (sign, value)) =
        match value with
        | []    -> "0"
        | value -> let reversed = reverse value
                   in  strcat ""
                       ((if sign = Pos then "" else "-") ::
                        (map string_of_int reversed))

(*--------------------------------------------------------------*)
(*--------ADDED CODE BELOW--------------------------------------*)
(*--------------------------------------------------------------*)

(* helper function used for pretty much all evaluations of arithmetic*)
(* compares the absolute value of 2 lists, returns 1 if list1>list2 
   returns -1 if list1<list2 and returns 0 if list1=list2 *) 
let cmp list1 list2 = 
   if (length list1) > (length list2) then 1  
   else if (length list1) < (length list2)then -1   
       (* compare each individual value when equal length *)
   else (*else we reverse the lists and compare their values directly*)
            (let abs1 = rev list1
                 in let abs2 = rev list2
                        in if abs1 > abs2 then 1
                           else if abs1 < abs2 then -1
                           else 0)  

(* implement the trim zeros function from the example programs - 
 it kills off the zeros from the end of the list because the 
 list is represented in reverse order *)
let trimzeros list =
    let rec trimzeros' list' = match list' with
        | []       -> []
        | [0]      -> []
        | car::cdr ->
             let cdr' = trimzeros' cdr
             in  match car, cdr' with
                 | 0, [] -> []
                 | car, cdr' -> car::cdr'
    in trimzeros' list

    (*This function handles adding recursively, 
      accepts two values with a carry as parameters*)
    let rec add' list1 list2 carry = match (list1, list2, carry) with
        | list1, [], 0       -> list1
        | [], list2, 0       -> list2
        | list1, [], carry   -> add' list1 [carry] 0
        | [], list2, carry   -> add' [carry] list2 0
        | car1::cdr1, car2::cdr2, carry ->
          let sum = car1 + car2 + carry
          in  sum mod radix :: add' cdr1 cdr2 (sum / radix)

     (* Recursive subtract function very similar to add function *) 
     let rec sub' list1 list2 carry = match (list1, list2, carry) with
        | list1, [], 0       -> list1 
        | [], list2, 0       -> list2
        | list1, [], carry   -> trimzeros (sub' list1 [carry] 0)
        | [], list2, carry   -> trimzeros (sub' [carry] list2 0)
        | car1::cdr1, car2::cdr2, carry ->
          if (car1 - carry) < car2   
          (*if our first value is larger than our second value*)
                then let dif = (10 + car1) - (car2 + carry)     
                (*Then we want to get the next digit *)
                in  dif mod radix :: trimzeros (sub' cdr1 cdr2 1)
                (*trimzeros needs to be called here too if it's not base case *)
          else let dif = car1 - car2 - carry                   
          (* else - just normal subtraction *)
               in  dif mod radix :: trimzeros (sub' cdr1 cdr2 0)
            (*normal subtraction assuming the difference is >0 *)

    (* Evaluates the signs of both lists/values and then 
       recursively call either add' or sub' if we have 
       exactly one value with negative signs *) 
    let add (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        if neg1 = neg2 
        then Bigint (neg1, add' value1 value2 0) 
        (*call the recursive function between the two values with no initial carry *) 
                    (*Other cases for add*)
        else if neg1 = Neg || neg2 = Neg  
        (*if one of the signs betwn the lists is negative we subtract*)
        then (if (cmp value1 value2) >= 0 then Bigint (Pos, trimzeros (sub' value1 value2 0))
              else Bigint (Neg, trimzeros (sub' value2 value1 0)))
        else zero

    (* Evaluates the signs of both lists/values to see if we 
       want to add or subtract them. In this it matters that 
       we're subtracting val2 from val1 *)
    let sub (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
        if neg1 = neg2  (*if the signs are the same... *)
           then (if (cmp value1 value2) >= 0
                    then Bigint (Pos, trimzeros (sub' value1 value2 0))
                else Bigint (Neg, trimzeros (sub' value2 value1 0)))
        else if neg1 = Neg 
             then Bigint (Neg, add' value1 value2 0)
        (* verify proper sign for mis matched signs *) 
        else if neg2 = Neg
             then Bigint (Pos, add' value1 value2 0)
        else zero

    (* recursive multiplication function, 
       code taken and modified from muldivrem example code *)
    let rec mul' (multiplier, powerof2, multiplicand') = 
        if (cmp powerof2 multiplier) > 0 then multiplier, [0] 
        else let remainder, product = mul' (multiplier, add' powerof2 
                 powerof2 0, add' multiplicand' multiplicand' 0)
            in if (cmp powerof2 remainder) > 0 then remainder, product
               else trimzeros (sub' remainder powerof2 0), 
                               add' product multiplicand' 0
 
    (* egyptian multiplication to assist us 
       in processing recursively multiplying lists*)
    let egyptMul (multiplier, multiplicand) = 
       let _, product = mul' (multiplier, [1], multiplicand) in product

    (* Evaluates signs for multiplication before 
       throwing in recursive multiplication calculator *) 
    let mul (Bigint (neg1, multiplier)) (Bigint (neg2, multiplicand)) =
      if neg1 = neg2 then Bigint (Pos, egyptMul (multiplier, multiplicand))    
      (* result will always be positive *) 
        else Bigint (Neg, egyptMul (multiplier, multiplicand))    
	(* else result will always be negative *) 


    (* Recursive division function, 
       also with code modified from class webiste *)
    let rec divrem' dividend powerof2 divisor =
        if (cmp divisor dividend) > 0 
                then [0], dividend            
        else let quotient, remainder =
                divrem' dividend (add' powerof2 powerof2 0) 
                                 (add' divisor divisor 0)
                in if( cmp remainder  divisor) < 0
                       then quotient, remainder
                    else (add' quotient powerof2 0), 
                         (sub' remainder divisor 0)

    (* Division helper function taken 
       and modified from examples on class website *) 
    let divrem dividend divisor = divrem' dividend [1] divisor

    (* Evaluates signs for division before 
      throwing in recursive devision calculator *) 
    let div (Bigint (neg1, dividend)) (Bigint (neg2, divisor)) =
        (*if same signs then result is positive *)
        if neg1 = neg2 then let quotient, _ = 
                  divrem dividend divisor in Bigint(Pos, quotient) 
        (*if exactly one sign is negative, then result is negative *)
        else let quotient, _ = divrem dividend divisor 
                               in Bigint(Neg, quotient) 

    (* Evaluates signs for remainder before calling recursive 
    division function. Same as div except it uses different arguments*)
    let rem (Bigint (neg1, dividend)) (Bigint (neg2, modulus)) =
        (*if same sign, result is positive *)
        if neg1 = neg2 then let _, remainder = divrem dividend modulus 
                                               in Bigint(Pos, remainder)
        (*else result is negative*)
        else let _, remainder =  divrem dividend modulus 
                                 in Bigint(Neg, remainder) 


    (* Helper function for even to divide a number for us *) 
    let callDivrem (dividend, divisor) =
       let  _, remainder = divrem dividend divisor
       in remainder


    (* Fancy function for return "number%2==0" *) 
    let even number = 
       let modulus = callDivrem (number, [2])
              in if cmp modulus [0] = 0 then true
                    else false  
     
     (* Recursive power function taken and 
        modified from mathfns example code *)
     let rec pow' base exponent toReturn = match exponent with
        | [0]                           -> toReturn
        | exponent when even exponent   -> pow' 
          (let _,b = mul' (base, [1], base) in b) 
          (let e,_ = divrem' exponent [1] [2] in e) toReturn
        | exponent                      -> pow' base 
          (sub' exponent [1] 0) 
          (let _,b = mul' (base, [1], toReturn) in b)


    (* Evaluates if we have a negative exponent or not 
       and computes it if it is negative into our 
       recursive power function  *)
    let pow (Bigint (neg1, base)) (Bigint (neg2, exponent)) =
	(*if exponent is neg, return 0 *)
        if neg2 = Neg then Bigint (Pos, [])  
        else if even exponent then Bigint (Pos, pow' base exponent [1])
        else if neg1 = Neg && even exponent then Bigint 
                                          (Pos, pow' base exponent [1]) 
        (*else if neg1 then Bigint (Neg, pow' base exponent [1])*) 
        else if neg1 = Pos then Bigint (Pos, pow' base exponent [1])
        (*else look to see if even or odd *)
        else Bigint (Neg, pow' base exponent [1]) 


end

