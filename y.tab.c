/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "YACC.y"


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
}
// si pentru classe daca se poate cu draguta seriosiztte
else printf("NU SE POATE REDECLARA VARIABILA CU NUMELE %s\n",name);
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

#line 262 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    RETURN = 258,                  /* RETURN  */
    INT = 259,                     /* INT  */
    FLOAT = 260,                   /* FLOAT  */
    CHAR = 261,                    /* CHAR  */
    BOOL = 262,                    /* BOOL  */
    STRING = 263,                  /* STRING  */
    VOID = 264,                    /* VOID  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    WHILE = 267,                   /* WHILE  */
    FOR = 268,                     /* FOR  */
    FUNCTION = 269,                /* FUNCTION  */
    CONSTANT = 270,                /* CONSTANT  */
    BGIN = 271,                    /* BGIN  */
    END = 272,                     /* END  */
    TYPE = 273,                    /* TYPE  */
    STRING_CONST = 274,            /* STRING_CONST  */
    NUMBER_INT = 275,              /* NUMBER_INT  */
    NUMBER_FLOAT = 276,            /* NUMBER_FLOAT  */
    ID = 277,                      /* ID  */
    EQUAL = 278,                   /* EQUAL  */
    NOT_EQUAL = 279,               /* NOT_EQUAL  */
    ASSIGNMENT = 280,              /* ASSIGNMENT  */
    LE = 281,                      /* LE  */
    GE = 282,                      /* GE  */
    GT = 283,                      /* GT  */
    LT = 284,                      /* LT  */
    AND = 285,                     /* AND  */
    NOT = 286,                     /* NOT  */
    OR = 287,                      /* OR  */
    ADD = 288,                     /* ADD  */
    SUB = 289,                     /* SUB  */
    MUL = 290,                     /* MUL  */
    DIV = 291,                     /* DIV  */
    MOD = 292,                     /* MOD  */
    BOOL_VAL = 293                 /* BOOL_VAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define RETURN 258
#define INT 259
#define FLOAT 260
#define CHAR 261
#define BOOL 262
#define STRING 263
#define VOID 264
#define IF 265
#define ELSE 266
#define WHILE 267
#define FOR 268
#define FUNCTION 269
#define CONSTANT 270
#define BGIN 271
#define END 272
#define TYPE 273
#define STRING_CONST 274
#define NUMBER_INT 275
#define NUMBER_FLOAT 276
#define ID 277
#define EQUAL 278
#define NOT_EQUAL 279
#define ASSIGNMENT 280
#define LE 281
#define GE 282
#define GT 283
#define LT 284
#define AND 285
#define NOT 286
#define OR 287
#define ADD 288
#define SUB 289
#define MUL 290
#define DIV 291
#define MOD 292
#define BOOL_VAL 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 193 "YACC.y"

    int numar;
    int numar_intreg;
    float numar_real;
    char* sir_char;
    char chara;
    char * boolval;

#line 400 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_RETURN = 3,                     /* RETURN  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_FUNCTION = 14,                  /* FUNCTION  */
  YYSYMBOL_CONSTANT = 15,                  /* CONSTANT  */
  YYSYMBOL_BGIN = 16,                      /* BGIN  */
  YYSYMBOL_END = 17,                       /* END  */
  YYSYMBOL_TYPE = 18,                      /* TYPE  */
  YYSYMBOL_STRING_CONST = 19,              /* STRING_CONST  */
  YYSYMBOL_NUMBER_INT = 20,                /* NUMBER_INT  */
  YYSYMBOL_NUMBER_FLOAT = 21,              /* NUMBER_FLOAT  */
  YYSYMBOL_ID = 22,                        /* ID  */
  YYSYMBOL_EQUAL = 23,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 24,                 /* NOT_EQUAL  */
  YYSYMBOL_ASSIGNMENT = 25,                /* ASSIGNMENT  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_GE = 27,                        /* GE  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_LT = 29,                        /* LT  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_OR = 32,                        /* OR  */
  YYSYMBOL_ADD = 33,                       /* ADD  */
  YYSYMBOL_SUB = 34,                       /* SUB  */
  YYSYMBOL_MUL = 35,                       /* MUL  */
  YYSYMBOL_DIV = 36,                       /* DIV  */
  YYSYMBOL_MOD = 37,                       /* MOD  */
  YYSYMBOL_BOOL_VAL = 38,                  /* BOOL_VAL  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* '('  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_43_ = 43,                       /* ';'  */
  YYSYMBOL_44_ = 44,                       /* '['  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_46_ = 46,                       /* '.'  */
  YYSYMBOL_47_ = 47,                       /* ','  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_program_structure = 50,         /* program_structure  */
  YYSYMBOL_block = 51,                     /* block  */
  YYSYMBOL_user_types = 52,                /* user_types  */
  YYSYMBOL_type = 53,                      /* type  */
  YYSYMBOL_in_type = 54,                   /* in_type  */
  YYSYMBOL_member = 55,                    /* member  */
  YYSYMBOL_declarations = 56,              /* declarations  */
  YYSYMBOL_variable = 57,                  /* variable  */
  YYSYMBOL_58_1 = 58,                      /* $@1  */
  YYSYMBOL_datatype = 59,                  /* datatype  */
  YYSYMBOL_functions = 60,                 /* functions  */
  YYSYMBOL_61_2 = 61,                      /* $@2  */
  YYSYMBOL_62_3 = 62,                      /* $@3  */
  YYSYMBOL_63_4 = 63,                      /* $@4  */
  YYSYMBOL_64_5 = 64,                      /* $@5  */
  YYSYMBOL_func_datatype = 65,             /* func_datatype  */
  YYSYMBOL_parameter_list_decl = 66,       /* parameter_list_decl  */
  YYSYMBOL_67_6 = 67,                      /* $@6  */
  YYSYMBOL_68_7 = 68,                      /* $@7  */
  YYSYMBOL_stmt_list = 69,                 /* stmt_list  */
  YYSYMBOL_stmt = 70,                      /* stmt  */
  YYSYMBOL_return_stmt = 71,               /* return_stmt  */
  YYSYMBOL_compound_stmt = 72,             /* compound_stmt  */
  YYSYMBOL_control_stmts = 73,             /* control_stmts  */
  YYSYMBOL__else = 74,                     /* _else  */
  YYSYMBOL_init_for = 75,                  /* init_for  */
  YYSYMBOL_inc_dec_expr = 76,              /* inc_dec_expr  */
  YYSYMBOL_function_call = 77,             /* function_call  */
  YYSYMBOL_parameter_list = 78,            /* parameter_list  */
  YYSYMBOL_param = 79,                     /* param  */
  YYSYMBOL_bool_expr = 80,                 /* bool_expr  */
  YYSYMBOL_composite_logic = 81,           /* composite_logic  */
  YYSYMBOL_nr = 82,                        /* nr  */
  YYSYMBOL_compare = 83,                   /* compare  */
  YYSYMBOL_logical_op = 84,                /* logical_op  */
  YYSYMBOL_expr = 85                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  26
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   408

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  229

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,     2,     2,    47,     2,    46,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   218,   218,   220,   221,   222,   223,   224,   225,   227,
     228,   231,   232,   234,   236,   237,   239,   240,   243,   244,
     246,   247,   248,   249,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   260,   261,   262,   263,   264,   268,
     268,   268,   269,   269,   269,   271,   272,   274,   275,   275,
     276,   276,   279,   280,   283,   284,   285,   286,   287,   290,
     291,   294,   297,   298,   299,   302,   303,   304,   307,   309,
     311,   313,   314,   315,   317,   320,   321,   322,   324,   325,
     327,   328,   329,   330,   333,   334,   335,   336,   337,   338,
     341,   342,   343,   345,   346,   347,   348,   349,   350,   351,
     352
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "RETURN", "INT",
  "FLOAT", "CHAR", "BOOL", "STRING", "VOID", "IF", "ELSE", "WHILE", "FOR",
  "FUNCTION", "CONSTANT", "BGIN", "END", "TYPE", "STRING_CONST",
  "NUMBER_INT", "NUMBER_FLOAT", "ID", "EQUAL", "NOT_EQUAL", "ASSIGNMENT",
  "LE", "GE", "GT", "LT", "AND", "NOT", "OR", "ADD", "SUB", "MUL", "DIV",
  "MOD", "BOOL_VAL", "'{'", "'}'", "'('", "')'", "';'", "'['", "']'",
  "'.'", "','", "$accept", "program", "program_structure", "block",
  "user_types", "type", "in_type", "member", "declarations", "variable",
  "$@1", "datatype", "functions", "$@2", "$@3", "$@4", "$@5",
  "func_datatype", "parameter_list_decl", "$@6", "$@7", "stmt_list",
  "stmt", "return_stmt", "compound_stmt", "control_stmts", "_else",
  "init_for", "inc_dec_expr", "function_call", "parameter_list", "param",
  "bool_expr", "composite_logic", "nr", "compare", "logical_op", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-92)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     307,   -92,   -92,   -92,   -92,   -92,   394,   167,    -5,    32,
      23,     9,    25,   -92,   312,   -92,    28,    74,   -92,   -92,
      30,    52,    -6,    -7,    69,    88,   -92,   267,   -92,    90,
     -92,   104,   -92,    74,    24,   394,    25,   -92,    57,    84,
     331,    93,   -92,   -92,    59,   100,    39,   -92,   -92,   105,
      99,   125,   -10,   108,   117,   118,    65,   267,   -92,   247,
     -92,   -92,   -92,   -92,   119,   128,   141,    25,    34,   -92,
     144,   155,   137,    39,   -92,   394,    79,   -92,   -92,   -92,
      39,   159,   -92,    80,    39,    39,    39,    39,    39,   -92,
     158,     7,   143,   145,     0,     0,   167,   187,   -92,   -92,
     -92,   146,   153,   333,   135,   -92,   167,   338,   162,   -92,
     -92,    -3,   -92,   371,   156,   -92,    97,    97,   -92,   -92,
     -92,    39,   160,   349,   -92,   -92,   -92,     0,   164,   -92,
     328,   165,   182,   173,   -92,   -92,   -92,   -92,   -92,   177,
     186,    49,   -92,   180,   -92,    39,   -92,   354,   -92,   -92,
     181,   268,   185,   -92,   -92,   -92,   -92,   -92,   -92,    39,
     189,   211,     0,   195,   167,   -92,   -92,   167,   167,   -92,
     -92,   124,   267,   371,   267,    39,   198,   -92,    60,   -92,
     204,   222,    82,   -92,   -92,   -92,   215,   207,   227,   371,
     226,   -92,   267,   -92,   219,     0,   250,   -92,   238,   234,
     229,   241,   -92,   267,   236,    -4,   -92,    39,   267,   267,
     -92,   243,   -92,   246,   267,   371,   -92,   244,   -92,     0,
     248,   -92,   251,   -92,   259,   267,   260,   250,   -92
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    34,    35,    36,    37,    38,     0,     0,     0,     0,
       0,    10,     8,    11,     6,    18,     0,     7,    46,    45,
       0,     0,     0,     0,     0,     0,     1,     0,     2,     0,
      12,     0,    19,     4,     0,     0,     5,    39,     0,     0,
       0,     0,    81,    82,    80,     0,     0,    94,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,     0,
      52,    55,    57,    56,     0,     0,     0,     3,     0,    20,
       0,     0,     0,     0,    33,     0,     0,    14,    16,    27,
      71,     0,    31,     0,     0,     0,     0,     0,     0,    26,
       0,     0,     0,     0,    78,    78,     0,     0,     9,    53,
      58,     0,     0,     0,     0,    42,    47,     0,     0,    13,
      15,     0,    72,    74,     0,   100,    95,    96,    97,    98,
      99,     0,     0,     0,    59,    60,    75,    78,     0,    77,
       0,     0,     0,     0,    61,    25,    30,    21,    23,     0,
       0,     0,    22,     0,    70,     0,    83,     0,    29,    28,
       0,     0,     0,    84,    85,    86,    87,    89,    88,     0,
       0,     0,    78,     0,    47,    48,    40,     0,    47,    73,
      32,     0,     0,    76,     0,     0,     0,    24,     0,    49,
       0,     0,     0,    90,    92,    91,     0,     0,     0,    68,
       0,    43,     0,    50,     0,    78,    67,    63,     0,     0,
       0,     0,    51,     0,     0,     0,    62,     0,     0,     0,
      41,     0,    79,     0,     0,    69,    64,     0,    17,    78,
       0,    44,     0,    65,     0,     0,     0,    67,    66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -92,   -92,   -92,   -92,    62,     6,   -92,   214,   -92,     5,
     -92,     2,   285,   -92,   -92,   -92,   -92,   -28,   -43,   -92,
     -92,   -54,   -57,   -92,   -92,   -92,    81,   -92,   -92,   -27,
     -92,   178,   -91,   -92,   -92,   -92,   -92,   -22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    10,    11,    28,    12,    13,    76,    77,    14,    58,
     163,    16,    17,    72,   180,   139,   200,    20,   141,   179,
     202,    59,    60,    61,    62,    63,   206,   133,   199,    47,
     111,   112,   128,   129,    48,   159,   186,   130
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      64,    49,    99,    97,   131,    15,   213,    71,    19,    21,
      92,    93,    41,    42,    43,    44,    39,    22,    30,    32,
      42,    43,    44,    26,    83,    27,   122,    42,    43,    44,
      64,    45,    64,    40,    46,   214,   150,    19,   126,   144,
      99,   127,    30,    29,   145,    78,   103,   108,    46,    68,
      34,   107,    37,   101,    42,    43,    44,    23,   113,    42,
      43,    44,   116,   117,   118,   119,   120,    69,    70,   123,
      64,   176,   102,    30,    38,    46,    24,    19,    25,    36,
      46,    78,    73,     1,     2,     3,     4,     5,    35,    50,
      23,   166,    29,    75,     7,    67,   167,    31,   132,   147,
      80,     9,   191,    81,   204,   151,    80,   167,   140,    24,
      51,    25,    65,    84,    85,    86,    87,    88,   187,   109,
     188,   178,   115,   113,   194,   182,    66,    74,   222,   167,
      99,    99,    86,    87,    88,   201,    79,   173,    84,    85,
      86,    87,    88,    82,    90,    64,   211,    64,    89,    94,
      91,   216,   217,   189,   183,   184,   185,   220,    95,    96,
      64,    64,   100,    39,   104,    64,   140,    40,   226,   181,
     140,     1,     2,     3,     4,     5,    64,   105,   106,   114,
     138,    64,    64,   121,   143,   215,   124,    64,   125,   135,
      52,     1,     2,     3,     4,     5,   136,    53,    64,    54,
      55,   146,     7,   148,   161,    31,   152,   160,   165,    56,
      52,     1,     2,     3,     4,     5,   162,    53,   164,    54,
      55,   168,     7,   171,   172,    31,    57,   134,   174,    56,
      52,     1,     2,     3,     4,     5,   175,    53,   177,    54,
      55,   190,     7,   192,   193,    31,    57,   196,   198,    56,
      52,     1,     2,     3,     4,     5,   195,    53,   203,    54,
      55,   205,     7,   207,    98,    31,    57,   197,   209,    56,
      52,     1,     2,     3,     4,     5,   208,    53,   212,    54,
      55,   210,     7,   218,   221,    31,    57,   219,   223,    56,
     110,   153,   154,   224,   155,   156,   157,   158,   225,    33,
     227,    84,    85,    86,    87,    88,    57,     0,   228,     0,
     115,     1,     2,     3,     4,     5,     1,     2,     3,     4,
       5,     6,     7,   169,     0,     8,     6,     7,     0,     9,
      31,     0,     0,     0,     9,     1,     2,     3,     4,     5,
       0,     0,     0,     0,     0,    75,     7,     0,     0,    31,
       0,   153,   154,     9,   155,   156,   157,   158,     0,     0,
       0,    84,    85,    86,    87,    88,    84,    85,    86,    87,
      88,    84,    85,    86,    87,    88,   137,     0,     0,     0,
       0,   142,    84,    85,    86,    87,    88,    84,    85,    86,
      87,    88,   149,     0,     0,     0,     0,   170,     1,     2,
       3,     4,     5,    18,    84,    85,    86,    87,    88
};

static const yytype_int16 yycheck[] =
{
      27,    23,    59,    57,    95,     0,    10,    35,     6,     7,
      20,    21,    19,    20,    21,    22,    22,    22,    12,    14,
      20,    21,    22,     0,    46,    16,    19,    20,    21,    22,
      57,    38,    59,    39,    41,    39,   127,    35,    38,    42,
      97,    41,    36,    18,    47,    40,    68,    75,    41,    25,
      22,    73,    22,    19,    20,    21,    22,    25,    80,    20,
      21,    22,    84,    85,    86,    87,    88,    43,    44,    91,
      97,   162,    38,    67,    22,    41,    44,    75,    46,    17,
      41,    76,    25,     4,     5,     6,     7,     8,    14,    20,
      25,    42,    18,    14,    15,    33,    47,    18,    96,   121,
      41,    22,    42,    44,   195,   127,    41,    47,   106,    44,
      22,    46,    22,    33,    34,    35,    36,    37,   172,    40,
     174,   164,    42,   145,    42,   168,    22,    43,   219,    47,
     187,   188,    35,    36,    37,   192,    43,   159,    33,    34,
      35,    36,    37,    43,    45,   172,   203,   174,    43,    41,
      25,   208,   209,   175,    30,    31,    32,   214,    41,    41,
     187,   188,    43,    22,    20,   192,   164,    39,   225,   167,
     168,     4,     5,     6,     7,     8,   203,    22,    41,    20,
      45,   208,   209,    25,    22,   207,    43,   214,    43,    43,
       3,     4,     5,     6,     7,     8,    43,    10,   225,    12,
      13,    45,    15,    43,    22,    18,    42,    42,    22,    22,
       3,     4,     5,     6,     7,     8,    43,    10,    41,    12,
      13,    41,    15,    42,    39,    18,    39,    40,    39,    22,
       3,     4,     5,     6,     7,     8,    25,    10,    43,    12,
      13,    43,    15,    39,    22,    18,    39,    40,    22,    22,
       3,     4,     5,     6,     7,     8,    41,    10,    39,    12,
      13,    11,    15,    25,    17,    18,    39,    40,    39,    22,
       3,     4,     5,     6,     7,     8,    42,    10,    42,    12,
      13,    40,    15,    40,    40,    18,    39,    41,    40,    22,
      76,    23,    24,    42,    26,    27,    28,    29,    39,    14,
      40,    33,    34,    35,    36,    37,    39,    -1,   227,    -1,
      42,     4,     5,     6,     7,     8,     4,     5,     6,     7,
       8,    14,    15,   145,    -1,    18,    14,    15,    -1,    22,
      18,    -1,    -1,    -1,    22,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    14,    15,    -1,    -1,    18,
      -1,    23,    24,    22,    26,    27,    28,    29,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    33,    34,    35,    36,
      37,    33,    34,    35,    36,    37,    43,    -1,    -1,    -1,
      -1,    43,    33,    34,    35,    36,    37,    33,    34,    35,
      36,    37,    43,    -1,    -1,    -1,    -1,    43,     4,     5,
       6,     7,     8,     9,    33,    34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,    14,    15,    18,    22,
      49,    50,    52,    53,    56,    57,    59,    60,     9,    59,
      65,    59,    22,    25,    44,    46,     0,    16,    51,    18,
      53,    18,    57,    60,    22,    14,    52,    22,    22,    22,
      39,    19,    20,    21,    22,    38,    41,    77,    82,    85,
      20,    22,     3,    10,    12,    13,    22,    39,    57,    69,
      70,    71,    72,    73,    77,    22,    22,    52,    25,    43,
      44,    65,    61,    25,    43,    14,    54,    55,    57,    43,
      41,    44,    43,    85,    33,    34,    35,    36,    37,    43,
      45,    25,    20,    21,    41,    41,    41,    69,    17,    70,
      43,    19,    38,    85,    20,    22,    41,    85,    65,    40,
      55,    78,    79,    85,    20,    42,    85,    85,    85,    85,
      85,    25,    19,    85,    43,    43,    38,    41,    80,    81,
      85,    80,    59,    75,    40,    43,    43,    43,    45,    63,
      59,    66,    43,    22,    42,    47,    45,    85,    43,    43,
      80,    85,    42,    23,    24,    26,    27,    28,    29,    83,
      42,    22,    43,    58,    41,    22,    42,    47,    41,    79,
      43,    42,    39,    85,    39,    25,    80,    43,    66,    67,
      62,    59,    66,    30,    31,    32,    84,    69,    69,    85,
      43,    42,    39,    22,    42,    41,    40,    40,    22,    76,
      64,    70,    68,    39,    80,    11,    74,    25,    42,    39,
      40,    70,    42,    10,    39,    85,    70,    70,    40,    41,
      70,    40,    80,    40,    42,    39,    70,    40,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    50,    50,    50,    51,
      51,    52,    52,    53,    54,    54,    55,    55,    56,    56,
      57,    57,    57,    58,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    59,    59,    59,    59,    59,    61,
      62,    60,    63,    64,    60,    65,    65,    66,    67,    66,
      68,    66,    69,    69,    70,    70,    70,    70,    70,    71,
      71,    72,    73,    73,    73,    74,    74,    74,    75,    76,
      77,    78,    78,    78,    79,    80,    80,    80,    81,    81,
      82,    82,    82,    82,    83,    83,    83,    83,    83,    83,
      84,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     2,     2,     1,     1,     1,     3,
       0,     1,     2,     5,     1,     2,     1,     9,     1,     2,
       3,     5,     6,     0,     7,     5,     4,     4,     6,     6,
       5,     4,     7,     4,     1,     1,     1,     1,     1,     0,
       0,    11,     0,     0,    12,     1,     1,     0,     0,     3,
       0,     5,     1,     2,     1,     1,     1,     1,     2,     3,
       3,     3,     8,     7,     9,     4,     9,     0,     4,     3,
       4,     0,     1,     3,     1,     1,     3,     1,     0,     7,
       1,     1,     1,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 20: /* variable: datatype ID ';'  */
#line 246 "YACC.y"
                         { add('V', (yyvsp[-1].sir_char)); }
#line 1647 "y.tab.c"
    break;

  case 21: /* variable: datatype ID ASSIGNMENT expr ';'  */
#line 247 "YACC.y"
                                       { add('V', (yyvsp[-3].sir_char)); change_value_int((yyvsp[-3].sir_char),(yyvsp[-1].numar_intreg));}
#line 1653 "y.tab.c"
    break;

  case 22: /* variable: CONSTANT datatype ID ASSIGNMENT expr ';'  */
#line 248 "YACC.y"
                                                { add('V',(yyvsp[-3].sir_char)); change_value_int((yyvsp[-3].sir_char),(yyvsp[-1].numar_intreg)); symbol_table[count-1].isconst=1; symbol_table[count].type=strdup("Constant"); }
#line 1659 "y.tab.c"
    break;

  case 23: /* $@1: %empty  */
#line 249 "YACC.y"
                                        { add('A', (yyvsp[-3].sir_char)); symbol_table[count-1].sizevector= (yyvsp[-1].numar_intreg);}
#line 1665 "y.tab.c"
    break;

  case 25: /* variable: datatype ID ASSIGNMENT STRING_CONST ';'  */
#line 250 "YACC.y"
                                               { add('V', (yyvsp[-3].sir_char)); change_value_char((yyvsp[-3].sir_char),(yyvsp[-1].sir_char)); }
#line 1671 "y.tab.c"
    break;

  case 26: /* variable: ID ASSIGNMENT expr ';'  */
#line 251 "YACC.y"
                               {change_value_int((yyvsp[-3].sir_char),(yyvsp[-1].numar_intreg));}
#line 1677 "y.tab.c"
    break;

  case 27: /* variable: ID ASSIGNMENT STRING_CONST ';'  */
#line 252 "YACC.y"
                                       {change_value_char((yyvsp[-3].sir_char),(yyvsp[-1].sir_char));}
#line 1683 "y.tab.c"
    break;

  case 30: /* variable: datatype ID ASSIGNMENT BOOL_VAL ';'  */
#line 255 "YACC.y"
                                           { add('V', (yyvsp[-3].sir_char)); change_value_bool((yyvsp[-3].sir_char),(yyvsp[-1].boolval)); }
#line 1689 "y.tab.c"
    break;

  case 31: /* variable: ID ASSIGNMENT BOOL_VAL ';'  */
#line 256 "YACC.y"
                                   {change_value_bool((yyvsp[-3].sir_char),(yyvsp[-1].boolval));}
#line 1695 "y.tab.c"
    break;

  case 32: /* variable: ID '[' NUMBER_INT ']' ASSIGNMENT expr ';'  */
#line 257 "YACC.y"
                                                 {change_value_array((yyvsp[-6].sir_char), (yyvsp[-1].numar_intreg), (yyvsp[-4].numar_intreg)); }
#line 1701 "y.tab.c"
    break;

  case 34: /* datatype: INT  */
#line 260 "YACC.y"
              { insert_type() ;}
#line 1707 "y.tab.c"
    break;

  case 35: /* datatype: FLOAT  */
#line 261 "YACC.y"
               { insert_type() ;}
#line 1713 "y.tab.c"
    break;

  case 36: /* datatype: CHAR  */
#line 262 "YACC.y"
              { insert_type() ;}
#line 1719 "y.tab.c"
    break;

  case 37: /* datatype: BOOL  */
#line 263 "YACC.y"
              { insert_type() ;}
#line 1725 "y.tab.c"
    break;

  case 38: /* datatype: STRING  */
#line 264 "YACC.y"
                { insert_type() ;}
#line 1731 "y.tab.c"
    break;

  case 39: /* $@2: %empty  */
#line 268 "YACC.y"
                                     { cur_type= strdup(type);}
#line 1737 "y.tab.c"
    break;

  case 40: /* $@3: %empty  */
#line 268 "YACC.y"
                                                                                          {add_function(cur_type, (yyvsp[-4].sir_char));}
#line 1743 "y.tab.c"
    break;

  case 42: /* $@4: %empty  */
#line 269 "YACC.y"
                                              { cur_type= strdup(type);}
#line 1749 "y.tab.c"
    break;

  case 43: /* $@5: %empty  */
#line 269 "YACC.y"
                                                                                                   {add_function(cur_type, (yyvsp[-4].sir_char));}
#line 1755 "y.tab.c"
    break;

  case 46: /* func_datatype: VOID  */
#line 272 "YACC.y"
                    { insert_type() ;}
#line 1761 "y.tab.c"
    break;

  case 48: /* $@6: %empty  */
#line 275 "YACC.y"
                                  {buffer_param(type, (yyvsp[0].sir_char));}
#line 1767 "y.tab.c"
    break;

  case 49: /* parameter_list_decl: datatype ID $@6  */
#line 275 "YACC.y"
                                                            { add('V', (yyvsp[-1].sir_char)); }
#line 1773 "y.tab.c"
    break;

  case 50: /* $@7: %empty  */
#line 276 "YACC.y"
                                                          { buffer_param(type, (yyvsp[0].sir_char));}
#line 1779 "y.tab.c"
    break;

  case 51: /* parameter_list_decl: parameter_list_decl ',' datatype ID $@7  */
#line 276 "YACC.y"
                                                                                     { add('V', (yyvsp[-1].sir_char)); }
#line 1785 "y.tab.c"
    break;

  case 80: /* nr: ID  */
#line 327 "YACC.y"
       { (yyval.numar_intreg) = symbol_table[search((yyvsp[0].sir_char))].intval;}
#line 1791 "y.tab.c"
    break;

  case 83: /* nr: ID '[' NUMBER_INT ']'  */
#line 330 "YACC.y"
                         {(yyval.numar_intreg) = symbol_table[search((yyvsp[-3].sir_char))].vector[(yyvsp[-1].numar_intreg)];}
#line 1797 "y.tab.c"
    break;

  case 95: /* expr: expr ADD expr  */
#line 347 "YACC.y"
                    { (yyval.numar_intreg) = (yyvsp[-2].numar_intreg) + (yyvsp[0].numar_intreg); }
#line 1803 "y.tab.c"
    break;

  case 96: /* expr: expr SUB expr  */
#line 348 "YACC.y"
                    { (yyval.numar_intreg) = (yyvsp[-2].numar_intreg) - (yyvsp[0].numar_intreg); }
#line 1809 "y.tab.c"
    break;

  case 97: /* expr: expr MUL expr  */
#line 349 "YACC.y"
                    { (yyval.numar_intreg) = (yyvsp[-2].numar_intreg) * (yyvsp[0].numar_intreg); }
#line 1815 "y.tab.c"
    break;

  case 98: /* expr: expr DIV expr  */
#line 350 "YACC.y"
                    { (yyval.numar_intreg) = (yyvsp[-2].numar_intreg) / (yyvsp[0].numar_intreg); }
#line 1821 "y.tab.c"
    break;

  case 99: /* expr: expr MOD expr  */
#line 351 "YACC.y"
                    { (yyval.numar_intreg) = (yyvsp[-2].numar_intreg) % (yyvsp[0].numar_intreg); }
#line 1827 "y.tab.c"
    break;

  case 100: /* expr: '(' expr ')'  */
#line 352 "YACC.y"
                   { (yyval.numar_intreg) = (yyvsp[-1].numar_intreg); }
#line 1833 "y.tab.c"
    break;


#line 1837 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 354 "YACC.y"

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
	// for(i=0;i<count;i++) { new !!!!! de sters
	// 	free(symbol_table[i].id_name);
	// 	free(symbol_table[i].type);
	// }
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
