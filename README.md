# Calculator

Execute the makefile and it will generate a calc exe, execute `./calc -h` to show the usage and type the expression string.
$ ./calc -h			// show help
* -h --help
* -t, --print-tree         		Print the expression tree.
* -p, --print-expression   	Print the inline expression.
* -e, --expand            			Expand all parenthesised operands in multiplication statements.

$ echo "(1+2)*(3+4)" | ./calc -t
$ echo  "(1+2)*(3+4)"  | ./calc -e -t