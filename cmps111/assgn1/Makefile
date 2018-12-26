#Ian Feekes
#ifeekes@ucsc.edu
#ID: 1474914
#CMPS111 assgn1
#Makefile 
#
#Creates the executable a.out for command line processing

Make: 
	flex lex.l
	cc -o myshell lex.yy.c myshell.c -lfl

clean:  
	rm lex.yy.c myshell
