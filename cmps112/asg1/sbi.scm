#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/racket/bin/mzscheme -qr
;; $Id: sbi.scm,v 1.3 2016-09-23 18:23:20-07 - - $
;;
;; NAME
;;    sbi.scm - silly basic interpreter
;;
;; SYNOPSIS
;;    sbi.scm filename.sbir
;;
;; DESCRIPTION
;;    The file mentioned in argv[1] is read and assumed to be an SBIR
;;    program, which is the executed.  Currently it is only printed.
;;
;; Ian Feekes
;; #1474914
;; ifeekes@ucsc.edu
;; asg1 sbi.scm

;Puts labels into a label table line-by-line
(define(label-finder  filename program)				
	(map (lambda (line)
	;(printf("debugging..."))
        	(when (not (null? (cdr line)))				; when we're not dealing with a null cdr or a pair we add it to the label-table
            		(when (not(pair? (cadr line)))
                		(hash-set! *label-table* (cadr line)  line)))
        ) program)  
)

;defines the symbol table for functions, label-table, and variable-table 
(define *symbol-table* (make-hash))
(define *label-table* (make-hash))
(define *variable-table* (make-hash))

;necessary function for implementing the symbol table in terms of adding in pairs 
(define (symbol-put! key value)
        (hash-set! *symbol-table* key value)
)

; gets the symbol
(define (symbol-get key)
        (hash-ref *symbol-table* key)
)

; same functions pretty much copied and pasted from above but with label tables and variable tables respectively 
(define (label-put! key value)
	(hash-set! *label-table* key value)
)

(define (label-get key)
	(hash-ref *label-table* key)
)

(define (variable-put! key value)
	(hash-set! *variable-table* key value)
)

(define (variable-get key)
	(hash-ref *variable-table* key)
)                     

;hash table creation for testing recursion - code largely taken from hashexample.scm and modified to involve more operators
(define ht (make-hash))                                         	; we have an object ht and we create a hash table 
(for-each                                                       	; for each
    (lambda (item) (hash-set! ht (car item) (cadr item)))       	; function item, which calls hash-set on the hash table object with arguments of the statement's car and cadr
    	`(                                                		; when we see a 'plus' sign we call a function that adds
      		(+ ,(lambda (x y) (+ x y)))                     	; same with subtract, multiply, and vector calls
      		(- ,(lambda (x y) (- x y)))
      		(* ,(lambda (x y) (* x y)))
      		;(vec ,(make-vector 10 0.0))				This was part of the original code but I don't think I want this
      		(/ ,(lambda (x y) (/ x (+ y 0.0))))			;division is a little different
		(expt,(lambda (x y) (expt(x y))))
		(<>,(lambda (x y)(not (eq? x y))))
       	)
      
)

;function for dealing with "print" labels 
(define (print-sbir statement)
	(if(null? statement)
		(display "\n")						; checks to see if the statement is null first
		(begin							; else...
			(if(not(string? (car statement)))
				(display(label-helper(car statement)))	; go to our helper statement for the car 
				(display(car statement)))
			(print-sbir(cdr statement))
		)	
	)
)

;function for dealing with "dim" labels to create arrays
(define (dim-sbir statement)
    (if(not(null? statement))
    	(begin(variable-put! (caar statement) (make-vector (label-helper (cadar statement))))
    	(symbol-put! (caar statement) 
		(lambda(function) 
    			(vector-ref (variable-get (caar statement))(- function 1)))))
    (exit))								; because you can't have an if without an else in this language
)

;function for dealing with "let" labels to create variables 
(define (let-sbir statement)
    (if not (vector? statement)
        (display "Error: let called on invalid array")			; let can only work if we are setting a variable to something 
    )
    (if (not(pair? (car statement)))
     	(variable-put! (car statement) (label-helper (cadr statement)))
     	(vector-set! (variable-get (caar statement))
     	(- (label-helper 1 (cadar statement))) (label-helper (cadr statement)))
    )
)

;THIS FUNCTION NEEDS WORK 
;function for dealing with "goto" labels to jump to the label
(define (goto-sbir label statement)
    (if(null? label)
        (display "Error: undefined label called on goto")		; checks if its null and if so it displays an error message 
    (begin((execute statement (label-get (car label))))))		; gets the key of the car from the *label-table* 
)

;function for dealing with "input" incomplete. 
(define(input-sbir expr)
	(expr)
)

;helper function for conversion of statements for the different labels that it may need to execute
(define (label-helper statement)
  (if (not(pair? statement))						; if we're not dealing with a pair 
    (begin    
      (cond ((not(number? statement)) (variable-get statement))         ; If our argument is not a number we get it from the variable table       
          (else statement)))						
    (apply (symbol-get (car statement)) (map label-helper (cdr statement))))  ; else it may be a function 
)

;never got around to implementing if expression evaluation 
(define(if-sbir expr)
	(expr)
)


;creates the symbol table, code modified from symbol.scm 
(for-each
        (lambda (pair)
                (symbol-put! (car pair) (cadr pair)))
        `(
                (log10_2 0.301029995663981195213738894724493026768189881)
                (sqrt_2  1.414213562373095048801688724209698078569671875)
                (e       2.718281828459045235360287471352662497757247093)
                (pi      3.141592653589793238462643383279502884197169399)
                (div     ,(lambda (x y) (floor (/ x y))))
                (log10   ,(lambda (x) (/ (log x) (log 10.0))))
                (mod     ,(lambda (x y) (- x (* (div x y) y))))
                (quot    ,(lambda (x y) (truncate (/ x y))))
                (rem     ,(lambda (x y) (- x (* (quot x y) y))))
                (%       ,(lambda (x y) (- x (* (/ x y) y))))           ; just wanted to make sure in case mod was used 
                (+       ,+)
                (^       ,expt)
                (ceil    ,ceiling)
                (exp     ,exp)
                (floor   ,floor)
                (log     ,log)
                (sqrt    ,sqrt)
		(-      ,-)
                (*      ,*)
                (/      ,/)
                (sin    ,sin)
                (asin   ,asin)
                (cos    ,cos)
                (acos   ,acos)
                (tan    ,tan)
                (atan   ,atan)
                (abs    ,abs)
                (round  ,round)
                (trunc  ,truncate)
                (=      ,=);I may wanna take these out later - we'll see based on how my if-sbir works 
                (<      ,<)
                (>      ,>)
                (<=     ,<=)
                (>=     ,>=)
                (<>     ,=)
		;functions that they might want
		(print  ,print-sbir)
                (dim    ,dim-sbir)
                (let    ,let-sbir)
                (goto   ,goto-sbir)
                (if     ,if-sbir)
                (input  ,input-sbir)
        )
)

;allows us to recognize pi and especially for inputting purposes
(for-each
    (lambda (pair)
            (variable-put! (car pair) (cadr pair)))
    `(
        (pi      3.141592653589793238462643383279502884197169399)
        (e       2.718281828459045235360287471352662497757247093)
     )
)

;these 3 functions need a lot of work and improvement with the goto labels 
(define (eval-helper statement infile)
	(when (not (hash-has-key? *symbol-table* (car statement)))
        	(display "Error: in eval-helper with invalid statement")
         	(void))) 

;works with execute-line to work like evaluate expression as it goes from line 0 to 
(define(evaluate-lines infile linenum)
	(when (not(>= linenum (length infile)))
        	(let((line (list-ref infile linenum)))
			(cond						;bunch of if/else statements 
				((= 3 (length line))
					(set! line (cddr line))		;if the line has a length of 3 
                   			(execute-line (car line) infile linenum))
				((and (= 2 (length line) ) (list? (cadr line)))
					(set! line (cdr line))
					 (execute-line (car line) infile linenum))
				 (else
                   (evaluate-lines infile (+ 1 linenum)))  		; else we're done and ready to move onto the next line               
             )
         )
     )
)

;recursive evaluate expression
(define (execute-line statement infile linenum)
	(if (not(null? statement))
  		(begin (eval-helper statement infile)			;checks to see if the statement is valid with the hashing first before evaluating the expression 
  			(cond ((eqv? (car statement) 'goto)
      			(evaluate-lines infile (- 1 (label-get (cadr statement)))))
   	 ((eqv? (car statement) 'if)
      		(if (not(equal? (label-helper (cadr statement))#t ))	;if false 
        		(evaluate-lines infile (+ 1 linenum))
        		(evaluate-lines infile (- 1 (label-get (caddr statement))))
        	)
    	)	  
    	(else
      		((symbol-get (car statement)) (cdr statement))
     		(evaluate-lines infile (+ 1 linenum))			; call evaluate lines for the next line when we're finished no matter what 
	)))
    	(evaluate-lines infile (+ 1 linenum)))
)


;-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
;;PRE-EXISTING FUNCTIONS WITH LITTLE MODIFICATIONS ARE BELOW
;-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

(define *stderr* (current-error-port))

(define *run-file*
    (let-values
        (((dirpath basepath root?)
            (split-path (find-system-path 'run-file))))
        (path->string basepath))
)

(define (die list)
    (for-each (lambda (item) (display item *stderr*)) list)
    (newline *stderr*)
    (exit 1)
)

(define (usage-exit)                                                    ;;variable called usage-exit
    (die `("Usage: " ,*run-file* " filename"))                          ;; die 
)

(define (readlist-from-inputfile filename)
    (let ((inputfile (open-input-file filename)))                       ;;inputfile is something returned from open
         (if (not (input-port? inputfile))                              ;; if we can't open it
             (die `(,*run-file* ": " ,filename ": open failed"))        ;; die and say it didn't work
             (let ((program (read inputfile)))                          ;; else it sets program to what read gets from inputfile
                  (close-input-port inputfile)                          ;; close the input-port we named inputfile
                         program))))                                    ;; return program 


(define (main arglist)							;;main function definition
    (if (or (null? arglist) (not (null? (cdr arglist))))		;; if argument list is null or the cdr of the argument list is null then exit
        (usage-exit)								
        (let* ((sbprogfile (car arglist))				;; sbprogrgile is the car of the argument list
              (program (readlist-from-inputfile sbprogfile)))		;; program is defined as a call to the function readlist-from-inputfile sbprogfile, now has entire file
;my own functions implemented here now that we have our program read 

	      ( label-finder sbprogfile program)			; starts hashing 
	      ( evaluate-lines program 0 ) 				; goes through line-by-line and controls things like output, starting from line 0  
			)))			

(main (vector->list (current-command-line-arguments)))		
