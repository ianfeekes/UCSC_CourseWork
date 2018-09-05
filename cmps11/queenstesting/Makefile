#A makefile to run the Queens program

Queens: Queens.class
 echo Main-class: Queens > Manifest
 jar cvfm Queens Manifest Queens.class
 rm Manifest
 chmod u+x Queens

Queens.class: Queens.java
 javac -Xlint Queens.java

clean:
 rm -f Queens.class Queens

submit: Makefile Queens.java
        submit cmps011-pt.w16 PA5 Makefile Queens.java

