%{

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
extern FILE* yyin;
extern char* yytext;
extern int yylineno;

int errors=0; //new
char* cur_type;
int cur_size;
int count=0;
int q;
char type[10];
extern int yylineno;
struct dataType {
        char * id_name;
        char * data_type;
        char * type;
        int intval;
        char * stringval;
        char * boolval;
        int isvector; // =1 daca memoreaza un vector
        int sizevector; // marimea vectorului
        int vector[100];
        int isconst;
        int line_no;
} symbol_table[40];

typedef struct param {
  char * id_name;
  char * data_type;
}param;

param buffer[40];
int count_params = 0;
int count_functions = 0;
struct functie {
  char * id_name;
  char * data_type;
  int nr; //nr parametri
  param params[100];
}function_table[40];

void insert_type() {
    strcpy(type, yytext);
}
int search(char *name) { 
    int i; 
    for(i=count-1; i>=0; i--) {
        if(strcmp(symbol_table[i].id_name, name)==0) {   
            return i; 
        }
    } 
    return -1;
}
void add(char c, char* name) {
  q=search(name);
  if(q==-1) { 
    if(c == 'V') {
      symbol_table[count].id_name=strdup(name);
      symbol_table[count].data_type=strdup(type);
      symbol_table[count].line_no=yylineno;
      symbol_table[count].type=strdup("Variable");   
      count++;  
    }  else if(c == 'A') {
      symbol_table[count].id_name=strdup(name);
      symbol_table[count].data_type=strdup(type);
      symbol_table[count].isvector = 1;
      symbol_table[count].line_no=yylineno;
      symbol_table[count].type=strdup("Array");   
      for(int i = 0; i < 100; i ++)
      {
        symbol_table[count].vector[i]=0;
      }
      count++;
}else printf("NU SE POATE REDECLARA VARIABILA CU NUMELE %s\n",name);
}
}
void change_value_int(char* name, int value) //new x3
{
    if(search(name)==-1 )
    {
        printf("VARIABILA %s NU POATE AVEA VALAOREA %d DEOARECE NU A FOST DECLARATA\n",name,value);
        return;
    }
    else if (is_const(name))
    {
        printf("VARIABILA %s NU ISI POATE SCHIMBA VALAOREA %d DEOARECE ESTE CONSTANTA\n",name,value);
        return;
    }
    int index = search(name);
    symbol_table[index].intval = value;
}
void change_value_char(char* name, char* value)
{
    if(search(name)==-1 )
    {
        printf("VARIABILA %s NU POATE AVEA VALAOREA %s DEOARECE NU A FOST DECLARATA\n",name,value);
        return;
    }
    else if (is_const(name))
    {
        printf("VARIABILA %s NU ISI POATE SCHIMBA VALAOREA %s DEOARECE ESTE CONSTANTA\n",name,value);
        return;
    }
    int index = search(name);
    symbol_table[index].stringval=strdup(value);
}
 void change_value_bool(char* name, char* bval)
{
    if(search(name)==-1 )
    {
        printf("VARIABILA %s NU POATE AVEA VALAOREA %s DEOARECE NU A FOST DECLARATA\n",name,bval);
        return;
    }
    else if (is_const(name))
    {
        printf("VARIABILA %s NU ISI POATE SCHIMBA VALAOREA %s DEOARECE ESTE CONSTANTA\n",name,bval);
        return;
    }
    int index = search(name);
    symbol_table[index].boolval=strdup(bval);
} 
void buffer_param(char * type2, char* name)
{
   buffer[count_params].id_name = strdup(name); buffer[count_params].data_type = strdup(type2); count_params++;
}
int search_function(char* type2, char* name)
{
  for(int i = 0 ; i < count_functions; i++ )
  {
    if ( strcmp(function_table[i].id_name, name)== 0 && strcmp(function_table[i].data_type, type2)==0 && count_params == function_table[i].nr)
    {
      for(int j = 0 ; j < count_params; j++)
      {
        char * nume_param = strdup(function_table[i].params[j].id_name);
        char * type_param = strdup(function_table[i].params[j].data_type);
        if ( strcmp(nume_param, buffer[j].id_name)!= 0 || strcmp(type_param, buffer[j].data_type) )
          return -1;
      }
      return i;
    }
  }
  return -1;
}
void add_function(char* type2, char* name)
{
  q = search_function(type2, name);
  if ( q==-1)// daca functia nu a mai fost declarata
  {
    function_table[count_functions].id_name = strdup(name);
    function_table[count_functions].data_type = strdup(type2);
    for(int i = 0 ; i < count_params; i++)
    {
      function_table[count_functions].params[i].id_name = strdup(buffer[i].id_name);
      function_table[count_functions].params[i].data_type = strdup(buffer[i].data_type);
      function_table[count_functions].nr++;
    }
    count_functions ++;
    count_params = 0;
  }
  else printf("FUNCTIA CU NUMELE %s DEJA A FOST DELCARATA\n", name);
}
void change_value_array(char* name, int value, int index)
{
  int position = search(name);
  if(position==-1)
  {
    printf("VECTORUL %s NU A FOST DECLARAT\n", name);
    return;
  }
  if ( index > symbol_table[position].sizevector )
  {
    printf("VECTORUL %s NU ARE ACCES LA POZITIA %d DEOARECE ARE MARIMEA DOAR %d\n", name, index, symbol_table[position].sizevector);
    return;
  }
  symbol_table[position].vector[index] = value;
  return;
}
int is_const(char* name)
{
  if (symbol_table[search(name)].isconst==1)
  return 1;
  else return 0;
}
%}

%union
{
    int numar;
    int numar_intreg;
    float numar_real;
    char* sir_char;
    char chara;
    char * boolval;
}
%token  RETURN INT FLOAT CHAR BOOL STRING VOID IF ELSE WHILE FOR FUNCTION CONSTANT BGIN END TYPE
%token <sir_char>STRING_CONST <numar_intreg>NUMBER_INT <numar_real>NUMBER_FLOAT <sir_char>ID 
%token EQUAL NOT_EQUAL ASSIGNMENT LE GE GT LT AND NOT OR ADD SUB MUL DIV MOD 
%token <boolval> BOOL_VAL

%type <numar_intreg> expr
%type <numar_intreg> nr
%type <sir_char> func_datatype
%type <sir_char> datatype

%left ADD SUB
%left MUL DIV MOD 

%start program


%%
program: program_structure block 
       ;
program_structure: declarations functions user_types 
                 | declarations functions 
                 | functions user_types 
                 | declarations
                 | functions
                 | user_types
                 ;
block: BGIN stmt_list END  
     |/*epsilon*/
     ;
/* TIP DEFINIT DE UTILIZATOR*/
user_types: type
          | user_types type
          ;
type: TYPE ID '{' in_type '}' 
    ;
in_type: member
       | in_type member
       ;
member: variable 
      | FUNCTION func_datatype ID '(' parameter_list_decl ')' '{' stmt '}' 
      ;
/*DECLARATII*/
declarations: variable 
           |declarations variable 
           ;
variable: datatype ID';' { add('V', $2); }
        |datatype ID ASSIGNMENT expr';'{ add('V', $2); change_value_int($2,$4);}
        |CONSTANT datatype ID ASSIGNMENT expr';'{ add('V',$3); change_value_int($3,$5); symbol_table[count-1].isconst=1; symbol_table[count].type=strdup("Constant"); }
        |datatype ID '[' NUMBER_INT ']' { add('A', $2); symbol_table[count-1].sizevector= $4;}';'
        |datatype ID ASSIGNMENT STRING_CONST';'{ add('V', $2); change_value_char($2,$4); }
        |ID ASSIGNMENT expr ';'{change_value_int($1,$3);}
        |ID ASSIGNMENT STRING_CONST ';'{change_value_char($1,$3);}
        |ID '.' ID ASSIGNMENT expr ';' 
        |ID '.' ID ASSIGNMENT STRING_CONST ';'
        |datatype ID ASSIGNMENT BOOL_VAL';'{ add('V', $2); change_value_bool($2,$4); } 
        |ID ASSIGNMENT BOOL_VAL ';'{change_value_bool($1,$3);} 
        |ID '[' NUMBER_INT ']' ASSIGNMENT expr';'{change_value_array($1, $6, $3); }
        |TYPE ID ID ';' //instantiere ex: person p1;
        ;                                    
datatype: INT { insert_type() ;}
        |FLOAT { insert_type() ;}
        |CHAR { insert_type() ;}
        |BOOL { insert_type() ;}
        |STRING { insert_type() ;}
        ;

/*FUNCTII cu (sau fara) parametri*/
functions: FUNCTION func_datatype ID { cur_type= strdup(type);} '(' parameter_list_decl')'{add_function(cur_type, $3);} '{' stmt '}'
         |functions FUNCTION func_datatype ID { cur_type= strdup(type);}'(' parameter_list_decl ')'{add_function(cur_type, $4);} '{' stmt '}' //ca sa putem scrie mai multe functii
         ;
func_datatype: datatype
             | VOID { insert_type() ;}
             ;
parameter_list_decl : /*epsilon*/
                    | datatype ID {buffer_param(type, $2);} { add('V', $2); } //parameter declaration
                    | parameter_list_decl ',' datatype ID { buffer_param(type, $4);} { add('V', $4); }
                    ;
/*STATEMENTS */
stmt_list: stmt
         | stmt_list stmt 
         ;

stmt: variable    //pt assignment
    | return_stmt
    | control_stmts
    | compound_stmt
    | function_call ';'
    ;

return_stmt: RETURN NUMBER_INT ';'
           | RETURN NUMBER_FLOAT ';'
           ;

compound_stmt:'{' stmt_list '}'
             ;

control_stmts: IF '(' bool_expr ')' '{' stmt_list '}' _else
             | WHILE '(' bool_expr ')' '{' stmt_list '}'
             | FOR '('init_for ';' bool_expr ';' inc_dec_expr ')' stmt
             ;

_else: ELSE '{'stmt'}'
     | ELSE IF '(' bool_expr ')' '{'stmt'}' _else
     | /* epsilon */
     ;

init_for: datatype ID ASSIGNMENT expr 
        ;
inc_dec_expr: ID ASSIGNMENT expr 
            ;
function_call:  ID '(' parameter_list ')' 
             ;
parameter_list: /*epsilon pt functiile void*/
              |param
              |parameter_list ',' param
              ;
param: expr
     ;
/*EXPRESSIONS*/
bool_expr: BOOL_VAL 
            | expr compare expr // 3<4 sau 3+2 < 6 etc.
            | composite_logic
            ;
composite_logic:
               |'(' bool_expr ')' logical_op '(' bool_expr ')' //(3<5) AND (2<3)
               ;
nr: ID { $$ = symbol_table[search($1)].intval;}
  | NUMBER_INT 
  | NUMBER_FLOAT 
  | ID '[' NUMBER_INT ']'{$$ = symbol_table[search($1)].vector[$3];}
  ;

compare: EQUAL
       | NOT_EQUAL
       | LE
       | GE
       | LT
       | GT
       ;

logical_op: AND
          | OR
          | NOT
          ;
expr: nr
    | function_call 
    | expr ADD expr { $$ = $1 + $3; }
    | expr SUB expr { $$ = $1 - $3; }
    | expr MUL expr { $$ = $1 * $3; }
    | expr DIV expr { $$ = $1 / $3; }
    | expr MOD expr { $$ = $1 % $3; }
    | '(' expr ')' { $$ = $2; }
    ;
%%
int yyerror(char * s){
printf("eroare: %s la linia:%d\n",s,yylineno);
errors++;
}

int main(int argc, char** argv)
{
    yyin = fopen(argv[1], "r");
    yyparse();
    if(errors==0){printf("Program corect sintactic.\n");} //new

    FILE* tabel;
    tabel = fopen("symbol_table.txt", "a");
	fprintf(tabel,"SYMBOL   DATATYPE   TYPE   LINE NUMBER    VALUE\n");
	fprintf(tabel,"__________________________________________________\n\n");
	int i=0;
	for(i=0; i<count; i++) {
		fprintf(tabel,"%s\t%s\t%s", symbol_table[i].id_name, symbol_table[i].data_type, symbol_table[i].type);
    fprintf(tabel,"\t%d\t", symbol_table[i].line_no);
        if(strcmp(symbol_table[i].data_type, "intreg")==0||strcmp(symbol_table[i].data_type, "real")==0)
        {
        if(symbol_table[i].isvector == 1)
        {
          fprintf(tabel, "\t");
          for(int j = 0 ; j < symbol_table[i].sizevector; j++)
          fprintf(tabel, "%d ", symbol_table[i].vector[j]);
          fprintf(tabel, "\n");
        }
        else
        {
          fprintf(tabel,"%d\n",symbol_table[i].intval);
        }
        }
        if(strcmp(symbol_table[i].data_type, "chara")==0||strcmp(symbol_table[i].data_type, "sir")==0)
        fprintf(tabel,"<%s>\n",symbol_table[i].stringval);
        if(strcmp(symbol_table[i].data_type, "bool")==0)
        fprintf(tabel,"<%s>\n",symbol_table[i].boolval); 
	}
	
  tabel=fopen("symbol_table.txt","w");
   FILE* tabel2;
    tabel2 = fopen(" symbol_table_functions.txt", "a");
	fprintf(tabel2,"SYMBOL   DATATYPE    PARAMS\n");
	fprintf(tabel2,"__________________________________________________\n\n");
	for(i=0; i<count_functions; i++) {
    fprintf(tabel2,"%s\t%s\t", function_table[i].id_name, function_table[i].data_type);
    for(int j = 0; j < function_table[i].nr; j++  )
    {
      fprintf(tabel2,"%s %s\t", function_table[i].params[j].data_type, function_table[i].params[j].id_name);
    }
    fprintf(tabel2,"\n");
}
  tabel2=fopen(" symbol_table_functions.txt","w");

}
