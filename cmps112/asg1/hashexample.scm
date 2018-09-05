#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/racket/bin/mzscheme -qr


; a utility function to make printing easier, because we don't have a printf statement it instead uses "display." Maybe I will do this for my lab. 
(define (show label it)						; function called show with parameters "label" and "it" 
    (display label)
    (display " = ")
    (display it)
    (newline)
)

;creates a hash table and puts in some functions and variables 
(define ht (make-hash))						; we have an object ht and we create a hash table 
(for-each							; for each
    (lambda (item) (hash-set! ht (car item) (cadr item)))	; function item, which calls hash-set on the hash table object with arguments of the statement's car and cadr
    `(;(var 34)							; when we see a 'plus' sign we call a function that adds
      (+ ,(lambda (x y) (+ x y)))				; same with subtract, multiply, and vector calls
      (- ,(lambda (x y) (- x y)))
      (* ,*)
      (vec ,(make-vector 10 0.0)))
      ;)
)
;NOTE: I am commenting out the make-vector and the var 34 to see how the make-hash is implemented-------------------------------

;prints out the hash table 
(hash-for-each ht (lambda (key value) (show key value)))	; function name "hash-for-each" calls show" with the key and value put in
(newline)							; and then prints a new line 


;shows the value of a simple variable 
;the last argument, "#f" causes hash-ref to return it rather than crashing the program on failure to find a nonexistent variable 
;(show "var" (hash-ref ht 'var #f))				

;sets a vector element, prints it and the whole vector 
(vector-set! (hash-ref ht 'vec #f) 5 3.1415926535)
(show "vec[5]" (vector-ref (hash-ref ht 'vec) 5))
(show "vec" (hash-ref ht 'vec #f))

;some examples 
(show "(+ 3 4)" (apply (hash-ref ht '+ #f) '(3 4)))
(show "not found" (hash-ref ht 'foo #f))


;STEAL THIS CODE!!!
;------------------------------------------------------------------------------
;outlines how to recursively evaluate a list
(define (evalexpr expr)
   (cond ((number? expr) expr)
         ((symbol? expr) (hash-ref ht expr #f))
         ((pair? expr)   (apply (hash-ref ht (car expr))
                                (map evalexpr (cdr expr))))
         (else #f))
)
;------------------------------------------------------------------------------

;Now we print out the values of several expressions 
(for-each
    (lambda (expr) (show expr (evalexpr expr)))
    '( ;(* var 7)
       (- 3 4)
       ;(+ (* var 7) (- 3 4))
))

;Just a verification of finishing. 
(display "DONE.") (newline)					; at the end of the file we display done with a new line 

