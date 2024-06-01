%{   
    #include <stdio.h>
    #include <stdlib.h>   
    #include "y.tab.h" 
    #include <string.h>  
%}
%option noyywrap
%%
"returneaza"  { return RETURN; }
"inceput_main" { return BGIN; }
"sfarsit_main" { return END; }
"tip_propriu:" { return TYPE; }

 /* TIPURI DE DATE */
"intreg" { return INT; }
"real" { return FLOAT; }
"chara" { return CHAR; }
"bool" { return BOOL; }
"sir" { return STRING; }
"constant" { return CONSTANT; }
"fara_tip" { return VOID; }

 /* CONTROL STATEMENTS + FUNCTIONS*/

"daca" { return IF; }
"altfel" { return ELSE; }
"cat_timp" { return WHILE; }
"pentru" { return FOR; }

"functie:" { return FUNCTION; } /*o sa incepem apelul de functii scriind functie: */

 /* OPERATORI */
"==" { return EQUAL; }
"=" { return ASSIGNMENT; }
"=/=" { return NOT_EQUAL; }
"<=" { return LE; }
">=" { return GE; }
">" { return GT; }
"<" { return LT; }
"&&"|"si" { return AND; }
"~" { return NOT; }
"||"|"sau" { return OR; }
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"%" { return MOD; }

 /* CONSTANTE */
("adevarat"|"fals") {yylval.boolval = strdup(yytext); return BOOL_VAL; }
([-]?[1-9][0-9]*)|0 { yylval.numar = atoi(yytext); return NUMBER_INT; } 
[-]?(([1-9][0-9]*)|0)\.[0-9]* { yylval.numar = atof(yytext); return NUMBER_FLOAT; }
[ \t]* ;
"\n"|"\r\n" {yylineno++;} 

 /* IDENTIFICATORI */
@[a-zA-Z0-9_]* { yylval.sir_char = strdup(yytext); return ID; }
[A-Za-z0-9_]+ {yylval.sir_char=strdup(yytext);return STRING_CONST;}
. {return yytext[0];}

%%