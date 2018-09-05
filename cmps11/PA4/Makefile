#Ian Feekes
#1474914
#CMPS 11 PA4
#Makefile
#A makefile for the Roots program
Roots: Roots.class
	jar cvfm Roots Manifest Roots.class
	chmod u+x Roots

Roots.class: Roots.java
	javac -Xlint Roots.java

clean:
	rm -f Roots.class Roots

submit: Makefile Roots.java
	submit cmps011-pt.w16 PA4 Makefile Roots.java
