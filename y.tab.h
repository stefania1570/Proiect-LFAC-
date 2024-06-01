/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 152 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
