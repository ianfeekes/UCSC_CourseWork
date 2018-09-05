#!/bin/sh -x
# $Id: import-border.sh,v 1.1 2018-08-02 13:10:30-07 - - $

for i in hello-world \
         bonjour-le-monde ciao-mondo hallo-welt konnichiwa-sekai
do
   $i&
   sleep 10
   import -border -frame $i.image.ps
done
