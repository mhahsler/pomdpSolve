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

#ifndef YY_YYMDP_Y_TAB_H_INCLUDED
# define YY_YYMDP_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yymdpdebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 259,                 /* "invalid token"  */
    INTTOK = 1,                    /* INTTOK  */
    FLOATTOK = 2,                  /* FLOATTOK  */
    COLONTOK = 3,                  /* COLONTOK  */
    MINUSTOK = 4,                  /* MINUSTOK  */
    PLUSTOK = 5,                   /* PLUSTOK  */
    STRINGTOK = 6,                 /* STRINGTOK  */
    ASTERICKTOK = 7,               /* ASTERICKTOK  */
    DISCOUNTTOK = 8,               /* DISCOUNTTOK  */
    VALUESTOK = 9,                 /* VALUESTOK  */
    STATETOK = 10,                 /* STATETOK  */
    ACTIONTOK = 11,                /* ACTIONTOK  */
    OBSTOK = 12,                   /* OBSTOK  */
    TTOK = 13,                     /* TTOK  */
    OTOK = 14,                     /* OTOK  */
    RTOK = 15,                     /* RTOK  */
    UNIFORMTOK = 16,               /* UNIFORMTOK  */
    IDENTITYTOK = 17,              /* IDENTITYTOK  */
    REWARDTOK = 18,                /* REWARDTOK  */
    COSTTOK = 19,                  /* COSTTOK  */
    RESETTOK = 20,                 /* RESETTOK  */
    STARTTOK = 21,                 /* STARTTOK  */
    INCLUDETOK = 22,               /* INCLUDETOK  */
    EXCLUDETOK = 23,               /* EXCLUDETOK  */
    EOFTOK = 258                   /* EOFTOK  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 259
#define INTTOK 1
#define FLOATTOK 2
#define COLONTOK 3
#define MINUSTOK 4
#define PLUSTOK 5
#define STRINGTOK 6
#define ASTERICKTOK 7
#define DISCOUNTTOK 8
#define VALUESTOK 9
#define STATETOK 10
#define ACTIONTOK 11
#define OBSTOK 12
#define TTOK 13
#define OTOK 14
#define RTOK 15
#define UNIFORMTOK 16
#define IDENTITYTOK 17
#define REWARDTOK 18
#define COSTTOK 19
#define RESETTOK 20
#define STARTTOK 21
#define INCLUDETOK 22
#define EXCLUDETOK 23
#define EOFTOK 258

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 131 "parser.y"

  Constant_Block *constBlk;
  int i_num;
  double f_num;

#line 125 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yymdplval;


int yymdpparse (void);


#endif /* !YY_YYMDP_Y_TAB_H_INCLUDED  */
