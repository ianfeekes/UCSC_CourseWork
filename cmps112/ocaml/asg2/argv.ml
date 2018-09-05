(* $Id: argv.ml,v 346.4 2014-11-17 13:52:06-08 - - $ *)

(*
* Illustrate access to the command line.
*)

open Printf;;								(*Opens printer*)

let printarg i s = printf "argv.(%d) = %s\n" i s;;

printf "basename argv.(0) = %s\n" (Filename.basename Sys.argv.(0));;   (*Prints basename argv.(0) = filename*)
printf "executable_name = %s\n" Sys.executable_name;;		       (*Prints executable_name = args*)
Array.iteri printarg Sys.argv;;					       (*Goes through args and prints*)

exit 0;

