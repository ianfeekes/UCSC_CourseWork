#Ian Feekes
#ifeekes@ucsc.edu 
#ID: 147914
#CMPS111 assgn4
#Makefile
#
#Creates the executable file system

Make:
	cc diskReader.c -o diskReader
	cc fatMain.c -o fatMain 
	cc bigBlock.c -o bigBlock `pkgconf fuse --cflags --libs`

clean: 
	rm bigBlock 
	rm diskReader
	rm fatMain  
