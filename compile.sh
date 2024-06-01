#!/bin/bash
rm -f lex.yy.c
rm -f y.tab.c
rm -f exemplu
yacc -d YACC.y
lex LEX.l
gcc -Wno-implicit-function-declaration lex.yy.c y.tab.c -o exemplu
