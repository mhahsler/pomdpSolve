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


/* Substitute the variable and function names.  */
#define yyparse         yymdpparse
#define yylex           yymdplex
#define yyerror         yymdperror
#define yydebug         yymdpdebug
#define yynerrs         yymdpnerrs
#define yylval          yymdplval
#define yychar          yymdpchar

/* First part of user prologue.  */
#line 1 "parser.y"

/*
  *****
  Copyright 1994-1997, Brown University
  Copyright 1998, 1999, Anthony R. Cassandra

                           All Rights Reserved
                           
  Permission to use, copy, modify, and distribute this software and its
  documentation for any purpose other than its incorporation into a
  commercial product is hereby granted without fee, provided that the
  above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.
  
  ANTHONY CASSANDRA DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
  INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR ANY
  PARTICULAR PURPOSE.  IN NO EVENT SHALL ANTHONY CASSANDRA BE LIABLE FOR
  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
  *****

*/
#include <stdio.h>

#include "mdp-common.h"
#include "parse_err.h"
#include "mdp.h"
#include "parse_hash.h"
#include "parse_constant.h"
#include "sparse-matrix.h"
#include "imm-reward.h"

#define YACCtrace(X)       /*   printf(X);fflush(stdout)    */ 

/* When reading in matrices we need to know what type we are reading
   and also we need to keep track of where in the matrix we are
   including how to update the row and col after each entry is read. */
typedef enum { mc_none, mc_trans_single, mc_trans_row, mc_trans_all,
               mc_obs_single, mc_obs_row, mc_obs_all,
               mc_reward_single, mc_reward_row, 
               mc_reward_all, mc_reward_mdp_only,
               mc_start_belief, mc_mdp_start, 
               mc_start_include, mc_start_exclude } Matrix_Context;

extern int yylex(void);

/* Forward declaration for action routines which appear at end of file */
void yyerror(char *string);
void checkMatrix(void);
void enterString( Constant_Block *block );
void enterUniformMatrix(void);
void enterIdentityMatrix(void);
void enterResetMatrix(void);
void enterMatrix( double value );
void setMatrixContext( Matrix_Context context, 
                      int a, int i, int j, int obs );
void enterStartState( int i );
void setStartStateUniform(void);
void endStartStates(void);
void verifyPreamble(void);
void checkProbs(void);

/*  Helps to give more meaningful error messages */
long currentLineNumber = 1;

/* This sets the context needed when names are given the the states, 
   actions and/or observations */
Mnemonic_Type curMnemonic = nt_unknown;

Matrix_Context curMatrixContext = mc_none;

/* These variable are used to keep track what type of matrix is being entered and
   which element is currently being processed.  They are initialized by the
   setMatrixContext() routine and updated by the enterMatrix() routine. */
int curRow;
int curCol;
int minA, maxA;
int minI, maxI;
int minJ, maxJ;
int minObs, maxObs;

/*  These variables will keep the intermediate representation for the
    matrices.  We cannot know how to set up the sparse matrices until
    all entries are read in, so we must have this intermediate 
    representation, which will will convert when it has all been read in.
    We allocate this memory once we know how big they must be and we
    will free all of this when we convert it to its final sparse format.
    */
I_Matrix *IP;   /* For transition matrices. */
I_Matrix *IR;   /* For observation matrices. */
I_Matrix **IW;  /* For reward matrices */

/* These variables are used by the parser only, to keep some state
   information. 
*/
/* These are set when the appropriate preamble line is encountered.  This will
   allow us to check to make sure each is specified.  If observations are not
   defined then we will assume it is a regular MDP, and otherwise assume it 
   is a POMDP
   */
int discountDefined = 0;
int valuesDefined = 0;
int statesDefined = 0;
int actionsDefined = 0;
int observationsDefined = 0;

/* We only want to check when observation probs. are specified, but
   there was no observations in preamble. */
int observationSpecDefined = 0;

/* When we encounter a matrix with too many entries.  We would like
   to only generate one error message, instead of one for each entry.
   This variable is cleared at the start of reading  a matrix and
   set when there are too many entries. */
int gTooManyEntries = 0;


#line 199 "y.tab.c"

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

#line 310 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yymdplval;


int yymdpparse (void);


#endif /* !YY_YYMDP_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTTOK = 3,                     /* INTTOK  */
  YYSYMBOL_FLOATTOK = 4,                   /* FLOATTOK  */
  YYSYMBOL_COLONTOK = 5,                   /* COLONTOK  */
  YYSYMBOL_MINUSTOK = 6,                   /* MINUSTOK  */
  YYSYMBOL_PLUSTOK = 7,                    /* PLUSTOK  */
  YYSYMBOL_STRINGTOK = 8,                  /* STRINGTOK  */
  YYSYMBOL_ASTERICKTOK = 9,                /* ASTERICKTOK  */
  YYSYMBOL_DISCOUNTTOK = 10,               /* DISCOUNTTOK  */
  YYSYMBOL_VALUESTOK = 11,                 /* VALUESTOK  */
  YYSYMBOL_STATETOK = 12,                  /* STATETOK  */
  YYSYMBOL_ACTIONTOK = 13,                 /* ACTIONTOK  */
  YYSYMBOL_OBSTOK = 14,                    /* OBSTOK  */
  YYSYMBOL_TTOK = 15,                      /* TTOK  */
  YYSYMBOL_OTOK = 16,                      /* OTOK  */
  YYSYMBOL_RTOK = 17,                      /* RTOK  */
  YYSYMBOL_UNIFORMTOK = 18,                /* UNIFORMTOK  */
  YYSYMBOL_IDENTITYTOK = 19,               /* IDENTITYTOK  */
  YYSYMBOL_REWARDTOK = 20,                 /* REWARDTOK  */
  YYSYMBOL_COSTTOK = 21,                   /* COSTTOK  */
  YYSYMBOL_RESETTOK = 22,                  /* RESETTOK  */
  YYSYMBOL_STARTTOK = 23,                  /* STARTTOK  */
  YYSYMBOL_INCLUDETOK = 24,                /* INCLUDETOK  */
  YYSYMBOL_EXCLUDETOK = 25,                /* EXCLUDETOK  */
  YYSYMBOL_EOFTOK = 26,                    /* EOFTOK  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_pomdp_file = 28,                /* pomdp_file  */
  YYSYMBOL_29_1 = 29,                      /* $@1  */
  YYSYMBOL_30_2 = 30,                      /* $@2  */
  YYSYMBOL_preamble = 31,                  /* preamble  */
  YYSYMBOL_param_type = 32,                /* param_type  */
  YYSYMBOL_discount_param = 33,            /* discount_param  */
  YYSYMBOL_value_param = 34,               /* value_param  */
  YYSYMBOL_value_tail = 35,                /* value_tail  */
  YYSYMBOL_state_param = 36,               /* state_param  */
  YYSYMBOL_37_3 = 37,                      /* $@3  */
  YYSYMBOL_state_tail = 38,                /* state_tail  */
  YYSYMBOL_action_param = 39,              /* action_param  */
  YYSYMBOL_40_4 = 40,                      /* $@4  */
  YYSYMBOL_action_tail = 41,               /* action_tail  */
  YYSYMBOL_obs_param = 42,                 /* obs_param  */
  YYSYMBOL_43_5 = 43,                      /* $@5  */
  YYSYMBOL_obs_param_tail = 44,            /* obs_param_tail  */
  YYSYMBOL_start_state = 45,               /* start_state  */
  YYSYMBOL_46_6 = 46,                      /* $@6  */
  YYSYMBOL_47_7 = 47,                      /* $@7  */
  YYSYMBOL_48_8 = 48,                      /* $@8  */
  YYSYMBOL_start_state_list = 49,          /* start_state_list  */
  YYSYMBOL_param_list = 50,                /* param_list  */
  YYSYMBOL_param_spec = 51,                /* param_spec  */
  YYSYMBOL_trans_prob_spec = 52,           /* trans_prob_spec  */
  YYSYMBOL_trans_spec_tail = 53,           /* trans_spec_tail  */
  YYSYMBOL_54_9 = 54,                      /* $@9  */
  YYSYMBOL_55_10 = 55,                     /* $@10  */
  YYSYMBOL_56_11 = 56,                     /* $@11  */
  YYSYMBOL_obs_prob_spec = 57,             /* obs_prob_spec  */
  YYSYMBOL_obs_spec_tail = 58,             /* obs_spec_tail  */
  YYSYMBOL_59_12 = 59,                     /* $@12  */
  YYSYMBOL_60_13 = 60,                     /* $@13  */
  YYSYMBOL_61_14 = 61,                     /* $@14  */
  YYSYMBOL_reward_spec = 62,               /* reward_spec  */
  YYSYMBOL_reward_spec_tail = 63,          /* reward_spec_tail  */
  YYSYMBOL_64_15 = 64,                     /* $@15  */
  YYSYMBOL_65_16 = 65,                     /* $@16  */
  YYSYMBOL_66_17 = 66,                     /* $@17  */
  YYSYMBOL_67_18 = 67,                     /* $@18  */
  YYSYMBOL_ui_matrix = 68,                 /* ui_matrix  */
  YYSYMBOL_u_matrix = 69,                  /* u_matrix  */
  YYSYMBOL_prob_matrix = 70,               /* prob_matrix  */
  YYSYMBOL_num_matrix = 71,                /* num_matrix  */
  YYSYMBOL_state = 72,                     /* state  */
  YYSYMBOL_action = 73,                    /* action  */
  YYSYMBOL_obs = 74,                       /* obs  */
  YYSYMBOL_ident_list = 75,                /* ident_list  */
  YYSYMBOL_prob = 76,                      /* prob  */
  YYSYMBOL_number = 77,                    /* number  */
  YYSYMBOL_optional_sign = 78              /* optional_sign  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   115

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   259


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
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,    26,     2
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   144,   144,   168,   143,   203,   207,   209,   210,   211,
     212,   213,   215,   229,   235,   246,   252,   251,   270,   289,
     293,   292,   305,   324,   328,   327,   340,   359,   363,   362,
     379,   416,   415,   422,   421,   429,   433,   437,   442,   443,
     445,   446,   472,   474,   480,   479,   486,   485,   490,   490,
     495,   501,   500,   507,   506,   511,   511,   516,   524,   523,
     533,   532,   539,   538,   546,   545,   552,   556,   560,   566,
     570,   574,   579,   583,   588,   592,   597,   609,   624,   629,
     642,   657,   662,   674,   689,   694,   698,   703,   712,   725,
     733,   742,   746,   751
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
  "\"end of file\"", "error", "\"invalid token\"", "INTTOK", "FLOATTOK",
  "COLONTOK", "MINUSTOK", "PLUSTOK", "STRINGTOK", "ASTERICKTOK",
  "DISCOUNTTOK", "VALUESTOK", "STATETOK", "ACTIONTOK", "OBSTOK", "TTOK",
  "OTOK", "RTOK", "UNIFORMTOK", "IDENTITYTOK", "REWARDTOK", "COSTTOK",
  "RESETTOK", "STARTTOK", "INCLUDETOK", "EXCLUDETOK", "EOFTOK", "$accept",
  "pomdp_file", "$@1", "$@2", "preamble", "param_type", "discount_param",
  "value_param", "value_tail", "state_param", "$@3", "state_tail",
  "action_param", "$@4", "action_tail", "obs_param", "$@5",
  "obs_param_tail", "start_state", "$@6", "$@7", "$@8", "start_state_list",
  "param_list", "param_spec", "trans_prob_spec", "trans_spec_tail", "$@9",
  "$@10", "$@11", "obs_prob_spec", "obs_spec_tail", "$@12", "$@13", "$@14",
  "reward_spec", "reward_spec_tail", "$@15", "$@16", "$@17", "$@18",
  "ui_matrix", "u_matrix", "prob_matrix", "num_matrix", "state", "action",
  "obs", "ident_list", "prob", "number", "optional_sign", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-94)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
    -106,    37,    35,  -106,    28,    38,    55,    58,    67,    17,
    -106,  -106,  -106,  -106,  -106,  -106,    52,    41,  -106,  -106,
    -106,     0,  -106,  -106,  -106,  -106,    63,  -106,  -106,  -106,
      27,    33,    36,    44,    70,    71,  -106,  -106,  -106,  -106,
    -106,  -106,    69,  -106,  -106,    69,  -106,  -106,    69,  -106,
       5,  -106,  -106,    40,  -106,  -106,  -106,  -106,  -106,  -106,
      65,  -106,     3,     3,    73,    74,    75,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,     3,  -106,     3,     7,     7,
       7,  -106,  -106,  -106,  -106,  -106,    76,  -106,    77,  -106,
      78,     3,    10,     3,     5,     3,    52,    79,  -106,  -106,
    -106,    65,    80,  -106,    81,    47,  -106,     3,     5,    23,
       5,     3,    52,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,    82,    47,    65,    65,    23,    52,  -106,  -106,  -106,
      47,    52,  -106
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     2,     1,     0,     0,     0,     0,     0,    35,
       5,     7,     8,     9,    10,    11,    93,     0,    16,    20,
      24,     0,     3,    92,    91,    12,     0,    14,    15,    13,
       0,     0,     0,    28,     0,     0,    39,    89,    90,    18,
      86,    17,    19,    22,    21,    23,    26,    25,    27,    30,
       0,    31,    33,     4,    85,    87,    88,    69,    70,    29,
      71,    73,     0,     0,     0,     0,     0,    38,    40,    41,
      42,    72,    76,    77,    78,    32,    37,    34,     0,     0,
       0,    36,    79,    80,    81,    43,    48,    50,    55,    57,
      64,     0,     0,     0,     0,     0,    93,    46,    66,    67,
      49,    68,    53,    56,    62,    65,    75,     0,     0,     0,
       0,     0,    93,    74,    44,    47,    82,    83,    84,    51,
      54,    60,    63,     0,     0,     0,    93,    45,    52,    58,
      61,    93,    59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,    25,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,   -91,    -2,  -105,   -73,    -9,   -34,    42,   -59,
     -16,  -106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     9,    36,     2,    10,    11,    12,    29,    13,
      30,    41,    14,    31,    44,    15,    32,    47,    22,    50,
      62,    63,    75,    53,    67,    68,    85,   123,   108,    92,
      69,    87,   124,   110,    94,    70,    89,   131,   126,   112,
      96,   100,    59,    60,   105,    76,    86,   119,    42,    61,
     106,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,    71,    81,   103,    81,    33,    72,   122,    55,    56,
      82,    73,    74,    55,    56,    83,    84,   115,    97,   120,
     102,   130,   104,    57,    34,    35,   116,    58,    98,    99,
      39,   117,   118,    16,   114,    40,    43,     3,   121,    46,
      21,    40,    71,    17,    40,     4,     5,     6,     7,     8,
     -93,   -93,    49,    23,    24,    64,    65,    66,    23,    24,
      18,    27,    28,    19,   127,   128,    37,    38,    55,    56,
      88,    90,    20,    45,    48,    51,    52,    54,    78,    79,
      80,    91,    93,    95,   107,   109,   111,   125,    77,   113,
     101,   129,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,     0,     0,     0,
       0,     0,     0,     0,   113,   132
};

static const yytype_int16 yycheck[] =
{
      16,    60,    75,    94,    77,     5,     3,   112,     3,     4,
       3,     8,     9,     3,     4,     8,     9,   108,    91,   110,
      93,   126,    95,    18,    24,    25,     3,    22,    18,    19,
       3,     8,     9,     5,   107,     8,     3,     0,   111,     3,
      23,     8,   101,     5,     8,    10,    11,    12,    13,    14,
       3,     4,     8,     6,     7,    15,    16,    17,     6,     7,
       5,    20,    21,     5,   123,   124,     3,     4,     3,     4,
      79,    80,     5,    31,    32,     5,     5,     8,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,    63,   105,
      92,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   130,   131
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    31,     0,    10,    11,    12,    13,    14,    29,
      32,    33,    34,    36,    39,    42,     5,     5,     5,     5,
       5,    23,    45,     6,     7,    77,    78,    20,    21,    35,
      37,    40,    43,     5,    24,    25,    30,     3,     4,     3,
       8,    38,    75,     3,    41,    75,     3,    44,    75,     8,
      46,     5,     5,    50,     8,     3,     4,    18,    22,    69,
      70,    76,    47,    48,    15,    16,    17,    51,    52,    57,
      62,    76,     3,     8,     9,    49,    72,    49,     5,     5,
       5,    72,     3,     8,     9,    53,    73,    58,    73,    63,
      73,     5,    56,     5,    61,     5,    67,    72,    18,    19,
      68,    70,    72,    69,    72,    71,    77,     5,    55,     5,
      60,     5,    66,    77,    72,    69,     3,     8,     9,    74,
      69,    72,    71,    54,    59,     5,    65,    76,    76,    74,
      71,    64,    77
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    29,    30,    28,    31,    31,    32,    32,    32,
      32,    32,    33,    34,    35,    35,    37,    36,    38,    38,
      40,    39,    41,    41,    43,    42,    44,    44,    46,    45,
      45,    47,    45,    48,    45,    45,    49,    49,    50,    50,
      51,    51,    51,    52,    54,    53,    55,    53,    56,    53,
      57,    59,    58,    60,    58,    61,    58,    62,    64,    63,
      65,    63,    66,    63,    67,    63,    68,    68,    68,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    72,    73,
      73,    73,    74,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,     5,     2,     0,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     0,     4,     1,     1,
       0,     4,     1,     1,     0,     4,     1,     1,     0,     4,
       3,     0,     5,     0,     5,     0,     2,     1,     2,     0,
       1,     1,     1,     3,     0,     7,     0,     5,     0,     3,
       3,     0,     7,     0,     5,     0,     3,     3,     0,     9,
       0,     7,     0,     5,     0,     3,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     2,
       2,     1,     1,     0
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
  case 2: /* $@1: %empty  */
#line 144 "parser.y"
                  { 
		    /* The preamble is a section of the file which */
		    /* must come first and whcih contains some global */
		    /* properties of the MDP that the file */
		    /* specifies. (e.g., number of states).  The */
		    /* observations are optional and its presence or */
		    /* absence is what first tells the parser whether */
		    /* it is parsing an MDP or a POMDP. */

		    verifyPreamble();  /* make sure all things are */
				       /* defined */

		    /* While we parse we use an intermediate */
		    /* representation which will be converted to the */
		    /* sparse representation when we are finished */
		    /* parsing.  After the preamble we are ready to */
		    /* start filling in values and we know how big the */
		    /* problem is, so we allocate the space for the */
		    /* intermediate forms */

		    allocateIntermediateMDP();  
		  }
#line 1484 "y.tab.c"
    break;

  case 3: /* $@2: %empty  */
#line 168 "parser.y"
                  { 
		    /* Some type of algorithms want a place to start */
		    /* off the problem, especially when doing */
		    /* simulation type experiments.  This is an */
		    /* optional argument that allows specification of */
		    /* this.   In a POMDP this is a belief state, but */
		    /* in an MDP this is a single state.  If none is */
		    /* specified for a POMDP, then the uniform */
		    /* distribution over all states is used.  If none */
		    /* is specified for an MDP, then random states */
		    /* will be assumed. */

		    endStartStates(); 
		  }
#line 1503 "y.tab.c"
    break;

  case 4: /* pomdp_file: preamble $@1 start_state $@2 param_list  */
#line 187 "parser.y"
                  {
		    /* This is the very last thing we do while */
		    /* parsing.  Even though the file may conform to */
		    /* the syntax, the semantics of the problem */
		    /* specification requires probability */
		    /* distributions.  This routine will make sure */
		    /* that the appropriate things sum to 1.0 to make */
		    /* a valid probability distribution. This will */
		    /* also generate the error message when */
		    /* observation probabilities are specified in an */
		    /* MDP problem, since this is illegal. */

                     checkProbs();
		     YACCtrace("pomdp_file -> preamble params\n");
                  }
#line 1523 "y.tab.c"
    break;

  case 5: /* preamble: preamble param_type  */
#line 204 "parser.y"
                {
		   YACCtrace("preamble -> preamble param_type\n");
		}
#line 1531 "y.tab.c"
    break;

  case 12: /* discount_param: DISCOUNTTOK COLONTOK number  */
#line 216 "parser.y"
                {
		  /* The discount factor only makes sense when in the */
		  /* range 0 to 1, so it is an error to specify */
		  /* anything outside this range. */

                   gDiscount = (yyvsp[0].f_num);
                   if(( gDiscount < 0.0 ) || ( gDiscount > 1.0 ))
                      ERR_enter("Parser<ytab>:", currentLineNumber,
                                BAD_DISCOUNT_VAL, "");
                   discountDefined = 1;
		   YACCtrace("discount_param -> DISCOUNTTOK COLONTOK number\n");
	        }
#line 1548 "y.tab.c"
    break;

  case 13: /* value_param: VALUESTOK COLONTOK value_tail  */
#line 230 "parser.y"
                {
                   valuesDefined = 1;
		   YACCtrace("value_param -> VALUESTOK COLONTOK value_tail\n");
	        }
#line 1557 "y.tab.c"
    break;

  case 14: /* value_tail: REWARDTOK  */
#line 243 "parser.y"
                {
                   gValueType = REWARD_value_type;
		}
#line 1565 "y.tab.c"
    break;

  case 15: /* value_tail: COSTTOK  */
#line 247 "parser.y"
                {
                   gValueType = COST_value_type;
		}
#line 1573 "y.tab.c"
    break;

  case 16: /* $@3: %empty  */
#line 252 "parser.y"
                { 
		  /* Since are able to enumerate the states and refer */
		  /* to them by identifiers, we will need to set the */
		  /* current state to indicate that we are parsing */
		  /* states.  This is important, since we will parse */
		  /* observatons and actions in exactly the same */
		  /* manner with the same code.  */
 
		  curMnemonic = nt_state; 

		}
#line 1589 "y.tab.c"
    break;

  case 17: /* state_param: STATETOK COLONTOK $@3 state_tail  */
#line 264 "parser.y"
                {
                   statesDefined = 1;
                   curMnemonic = nt_unknown;
		   YACCtrace("state_param -> STATETOK COLONTOK state_tail\n");
		}
#line 1599 "y.tab.c"
    break;

  case 18: /* state_tail: INTTOK  */
#line 271 "parser.y"
                {

		  /*  For the number of states, we can just have a */
		  /*  number indicating how many there are, or ... */

                   gNumStates = (yyvsp[0].constBlk)->theValue.theInt;
                   if( gNumStates < 1 ) {
                      ERR_enter("Parser<ytab>:", currentLineNumber, 
                                BAD_NUM_STATES, "");
                      gNumStates = 1;
                   }

 		   /* Since we use some temporary storage to hold the
		      integer as we parse, we free the memory when we
		      are done with the value */

                   XFREE( (yyvsp[0].constBlk) );
		}
#line 1622 "y.tab.c"
    break;

  case 20: /* $@4: %empty  */
#line 293 "parser.y"
                {
		  /* See state_param for explanation of this */

		  curMnemonic = nt_action;  
		}
#line 1632 "y.tab.c"
    break;

  case 21: /* action_param: ACTIONTOK COLONTOK $@4 action_tail  */
#line 299 "parser.y"
                {
                   actionsDefined = 1;
                   curMnemonic = nt_unknown;
		   YACCtrace("action_param -> ACTIONTOK COLONTOK action_tail\n");
		}
#line 1642 "y.tab.c"
    break;

  case 22: /* action_tail: INTTOK  */
#line 306 "parser.y"
                {

		  /*  For the number of actions, we can just have a */
		  /*  number indicating how many there are, or ... */

                   gNumActions = (yyvsp[0].constBlk)->theValue.theInt;
                   if( gNumActions < 1 ) {
                      ERR_enter("Parser<ytab>:", currentLineNumber, 
                                BAD_NUM_ACTIONS, "" );
                      gNumActions = 1;
                   }
		   
		   /* Since we use some temporary storage to hold the
		      integer as we parse, we free the memory when we
		      are done with the value */

                   XFREE( (yyvsp[0].constBlk) );
		}
#line 1665 "y.tab.c"
    break;

  case 24: /* $@5: %empty  */
#line 328 "parser.y"
                { 
		  /* See state_param for explanation of this */

		  curMnemonic = nt_observation; 
		}
#line 1675 "y.tab.c"
    break;

  case 25: /* obs_param: OBSTOK COLONTOK $@5 obs_param_tail  */
#line 334 "parser.y"
                {
                   observationsDefined = 1;
                   curMnemonic = nt_unknown;
		   YACCtrace("obs_param -> OBSTOK COLONTOK obs_param_tail\n");
		}
#line 1685 "y.tab.c"
    break;

  case 26: /* obs_param_tail: INTTOK  */
#line 341 "parser.y"
                {

		  /*  For the number of observation, we can just have a */
		  /*  number indicating how many there are, or ... */

                   gNumObservations = (yyvsp[0].constBlk)->theValue.theInt;
                   if( gNumObservations < 1 ) {
                      ERR_enter("Parser<ytab>:", currentLineNumber, 
                                BAD_NUM_OBS, "" );
                      gNumObservations = 1;
                   }

		   /* Since we use some temporary storage to hold the
		      integer as we parse, we free the memory when we
		      are done with the value */

                   XFREE( (yyvsp[0].constBlk) );
		}
#line 1708 "y.tab.c"
    break;

  case 28: /* $@6: %empty  */
#line 363 "parser.y"
                { 
		  /* There are a number of different formats for the */
		  /* start state.  This one is valid for either a */
		  /* POMDP or an MDP.  With a POMDP it will expect a */
		  /* list of probabilities, one for each state, */
		  /* representing the initial belief state.  For an */
		  /* MDP there can be only a single integer */
		  /* representing the starting state. */

		  if( gProblemType == POMDP_problem_type )
		    setMatrixContext(mc_start_belief, 0, 0, 0, 0); 
		  else
		    setMatrixContext(mc_mdp_start, 0, 0, 0, 0); 
		}
#line 1727 "y.tab.c"
    break;

  case 30: /* start_state: STARTTOK COLONTOK STRINGTOK  */
#line 396 "parser.y"
                {
                   int num;

		   num = H_lookup( (yyvsp[0].constBlk)->theValue.theString, nt_state );
		   if(( num < 0 ) || (num >= gNumStates )) {
		     ERR_enter("Parser<ytab>:", currentLineNumber, 
					BAD_STATE_STR, (yyvsp[0].constBlk)->theValue.theString );
		   }
		   else {
		     if( gProblemType == MDP_problem_type )
		       gInitialState = num;
		     else
		       gInitialBelief[num] = 1.0;
		   }

		   XFREE( (yyvsp[0].constBlk)->theValue.theString );
		   XFREE( (yyvsp[0].constBlk) );
                }
#line 1750 "y.tab.c"
    break;

  case 31: /* $@7: %empty  */
#line 416 "parser.y"
                { 
		  setMatrixContext(mc_start_include, 0, 0, 0, 0); 
		}
#line 1758 "y.tab.c"
    break;

  case 33: /* $@8: %empty  */
#line 422 "parser.y"
                { 
		  setMatrixContext(mc_start_exclude, 0, 0, 0, 0); 
		}
#line 1766 "y.tab.c"
    break;

  case 35: /* start_state: %empty  */
#line 429 "parser.y"
                { 
		  setStartStateUniform(); 
		}
#line 1774 "y.tab.c"
    break;

  case 36: /* start_state_list: start_state_list state  */
#line 434 "parser.y"
                {
		  enterStartState( (yyvsp[0].i_num) );
                }
#line 1782 "y.tab.c"
    break;

  case 37: /* start_state_list: state  */
#line 438 "parser.y"
                {
		  enterStartState( (yyvsp[0].i_num) );
                }
#line 1790 "y.tab.c"
    break;

  case 41: /* param_spec: obs_prob_spec  */
#line 447 "parser.y"
                  {
		    /* If there are observation specifications defined,
		       but no observations listed in the preamble, then
		       this is an error, since regular MDPs don't have
		       the concept of observations.  However, it could 
		       be a POMDP that was just missing the preamble 
		       part.  The way we handle this is to go ahead 
		       and parse the observation specifications, but
		       always check before we actually enter values in
		       a matrix (see the enterMatrix() routine.)  This
		       way we can determine if there are any problems 
		       with the observation specifications.  We cannot
		       add entries to the matrices since there will be
		       no memory allocated for it.  We want to
		       generate an error for this case, but don't want
		       a separate error for each observation
		       specification, so we define a variable that is
		       just a flag for whether or not any observation
		       specificiations have been defined.  After we
		       are all done parsing we will check this flag
		       and generate an error if needed.
		       */

		      observationSpecDefined = 1;
		  }
#line 1820 "y.tab.c"
    break;

  case 43: /* trans_prob_spec: TTOK COLONTOK trans_spec_tail  */
#line 475 "parser.y"
                {
		   YACCtrace("trans_prob_spec -> TTOK COLONTOK trans_spec_tail\n");
		}
#line 1828 "y.tab.c"
    break;

  case 44: /* $@9: %empty  */
#line 480 "parser.y"
                        { setMatrixContext(mc_trans_single, (yyvsp[-4].i_num), (yyvsp[-2].i_num), (yyvsp[0].i_num), 0); }
#line 1834 "y.tab.c"
    break;

  case 45: /* trans_spec_tail: action COLONTOK state COLONTOK state $@9 prob  */
#line 481 "parser.y"
                {
                   enterMatrix( (yyvsp[0].f_num) );
		   YACCtrace("trans_spec_tail -> action COLONTOK state COLONTOK state prob \n");
		}
#line 1843 "y.tab.c"
    break;

  case 46: /* $@10: %empty  */
#line 486 "parser.y"
                         { setMatrixContext(mc_trans_row, (yyvsp[-2].i_num), (yyvsp[0].i_num), 0, 0); }
#line 1849 "y.tab.c"
    break;

  case 47: /* trans_spec_tail: action COLONTOK state $@10 u_matrix  */
#line 487 "parser.y"
                {
		   YACCtrace("trans_spec_tail -> action COLONTOK state ui_matrix \n");
		}
#line 1857 "y.tab.c"
    break;

  case 48: /* $@11: %empty  */
#line 490 "parser.y"
                          { setMatrixContext(mc_trans_all, (yyvsp[0].i_num), 0, 0, 0); }
#line 1863 "y.tab.c"
    break;

  case 49: /* trans_spec_tail: action $@11 ui_matrix  */
#line 491 "parser.y"
                {
		   YACCtrace("trans_spec_tail -> action ui_matrix\n");
		}
#line 1871 "y.tab.c"
    break;

  case 50: /* obs_prob_spec: OTOK COLONTOK obs_spec_tail  */
#line 496 "parser.y"
                {
		   YACCtrace("obs_prob_spec -> OTOK COLONTOK  obs_spec_tail\n");
		}
#line 1879 "y.tab.c"
    break;

  case 51: /* $@12: %empty  */
#line 501 "parser.y"
                         { setMatrixContext(mc_obs_single, (yyvsp[-4].i_num), 0, (yyvsp[-2].i_num), (yyvsp[0].i_num)); }
#line 1885 "y.tab.c"
    break;

  case 52: /* obs_spec_tail: action COLONTOK state COLONTOK obs $@12 prob  */
#line 502 "parser.y"
                {
                   enterMatrix( (yyvsp[0].f_num) );
		   YACCtrace("obs_spec_tail -> action COLONTOK state COLONTOK obs prob \n");
		}
#line 1894 "y.tab.c"
    break;

  case 53: /* $@13: %empty  */
#line 507 "parser.y"
                         { setMatrixContext(mc_obs_row, (yyvsp[-2].i_num), 0, (yyvsp[0].i_num), 0); }
#line 1900 "y.tab.c"
    break;

  case 54: /* obs_spec_tail: action COLONTOK state $@13 u_matrix  */
#line 508 "parser.y"
                {
		   YACCtrace("obs_spec_tail -> action COLONTOK state COLONTOK u_matrix\n");
		}
#line 1908 "y.tab.c"
    break;

  case 55: /* $@14: %empty  */
#line 511 "parser.y"
                         { setMatrixContext(mc_obs_all, (yyvsp[0].i_num), 0, 0, 0); }
#line 1914 "y.tab.c"
    break;

  case 56: /* obs_spec_tail: action $@14 u_matrix  */
#line 512 "parser.y"
                {
		   YACCtrace("obs_spec_tail -> action u_matrix\n");
		}
#line 1922 "y.tab.c"
    break;

  case 57: /* reward_spec: RTOK COLONTOK reward_spec_tail  */
#line 517 "parser.y"
                {
		   YACCtrace("reward_spec -> RTOK COLONTOK  reward_spec_tail\n");
		}
#line 1930 "y.tab.c"
    break;

  case 58: /* $@15: %empty  */
#line 524 "parser.y"
                          { setMatrixContext(mc_reward_single, (yyvsp[-6].i_num), (yyvsp[-4].i_num), (yyvsp[-2].i_num), (yyvsp[0].i_num)); }
#line 1936 "y.tab.c"
    break;

  case 59: /* reward_spec_tail: action COLONTOK state COLONTOK state COLONTOK obs $@15 number  */
#line 525 "parser.y"
                {
                   enterMatrix( (yyvsp[0].f_num) );

		   /* Only need this for the call to doneImmReward */
		   checkMatrix();  
		   YACCtrace("reward_spec_tail -> action COLONTOK state COLONTOK state COLONTOK obs number\n");
		}
#line 1948 "y.tab.c"
    break;

  case 60: /* $@16: %empty  */
#line 533 "parser.y"
                         { setMatrixContext(mc_reward_row, (yyvsp[-4].i_num), (yyvsp[-2].i_num), (yyvsp[0].i_num), 0); }
#line 1954 "y.tab.c"
    break;

  case 61: /* reward_spec_tail: action COLONTOK state COLONTOK state $@16 num_matrix  */
#line 534 "parser.y"
                  {
                   checkMatrix();
		   YACCtrace("reward_spec_tail -> action COLONTOK state COLONTOK state num_matrix\n");
		 }
#line 1963 "y.tab.c"
    break;

  case 62: /* $@17: %empty  */
#line 539 "parser.y"
                          { setMatrixContext(mc_reward_all, (yyvsp[-2].i_num), (yyvsp[0].i_num), 0, 0); }
#line 1969 "y.tab.c"
    break;

  case 63: /* reward_spec_tail: action COLONTOK state $@17 num_matrix  */
#line 540 "parser.y"
                {
                   checkMatrix();
		   YACCtrace("reward_spec_tail -> action COLONTOK state num_matrix\n");
		}
#line 1978 "y.tab.c"
    break;

  case 64: /* $@18: %empty  */
#line 546 "parser.y"
                          { setMatrixContext(mc_reward_mdp_only, (yyvsp[0].i_num), 0, 0, 0); }
#line 1984 "y.tab.c"
    break;

  case 65: /* reward_spec_tail: action $@18 num_matrix  */
#line 547 "parser.y"
                {
                   checkMatrix();
		   YACCtrace("reward_spec_tail -> action num_matrix\n");
                }
#line 1993 "y.tab.c"
    break;

  case 66: /* ui_matrix: UNIFORMTOK  */
#line 553 "parser.y"
                {
                   enterUniformMatrix();
                }
#line 2001 "y.tab.c"
    break;

  case 67: /* ui_matrix: IDENTITYTOK  */
#line 557 "parser.y"
                {
                   enterIdentityMatrix();
                }
#line 2009 "y.tab.c"
    break;

  case 68: /* ui_matrix: prob_matrix  */
#line 561 "parser.y"
                {
                   checkMatrix();
                }
#line 2017 "y.tab.c"
    break;

  case 69: /* u_matrix: UNIFORMTOK  */
#line 567 "parser.y"
                {
                   enterUniformMatrix();
                }
#line 2025 "y.tab.c"
    break;

  case 70: /* u_matrix: RESETTOK  */
#line 571 "parser.y"
                {
		  enterResetMatrix();
		}
#line 2033 "y.tab.c"
    break;

  case 71: /* u_matrix: prob_matrix  */
#line 575 "parser.y"
                {
                   checkMatrix();
                }
#line 2041 "y.tab.c"
    break;

  case 72: /* prob_matrix: prob_matrix prob  */
#line 580 "parser.y"
                {
                   enterMatrix( (yyvsp[0].f_num) );
                }
#line 2049 "y.tab.c"
    break;

  case 73: /* prob_matrix: prob  */
#line 584 "parser.y"
                {
                   enterMatrix( (yyvsp[0].f_num) );
                }
#line 2057 "y.tab.c"
    break;

  case 74: /* num_matrix: num_matrix number  */
#line 589 "parser.y"
                {
                   enterMatrix( (yyvsp[0].f_num) );
                }
#line 2065 "y.tab.c"
    break;

  case 75: /* num_matrix: number  */
#line 593 "parser.y"
                {
                   enterMatrix( (yyvsp[0].f_num) );
                }
#line 2073 "y.tab.c"
    break;

  case 76: /* state: INTTOK  */
#line 598 "parser.y"
                {
                   if(( (yyvsp[0].constBlk)->theValue.theInt < 0 ) 
                      || ((yyvsp[0].constBlk)->theValue.theInt >= gNumStates )) {
                      ERR_enter("Parser<ytab>:", currentLineNumber, 
                                BAD_STATE_VAL, "");
                      (yyval.i_num) = 0;
                   }
                   else
                      (yyval.i_num) = (yyvsp[0].constBlk)->theValue.theInt;
                   XFREE( (yyvsp[0].constBlk) );
                }
#line 2089 "y.tab.c"
    break;

  case 77: /* state: STRINGTOK  */
#line 610 "parser.y"
                {
                   int num;
                   num = H_lookup( (yyvsp[0].constBlk)->theValue.theString, nt_state );
                   if (( num < 0 ) || (num >= gNumStates )) {
				 ERR_enter("Parser<ytab>:", currentLineNumber, 
						 BAD_STATE_STR, (yyvsp[0].constBlk)->theValue.theString );
				 (yyval.i_num) = 0;
                   }
                   else
				 (yyval.i_num) = num;

                   XFREE( (yyvsp[0].constBlk)->theValue.theString );
                   XFREE( (yyvsp[0].constBlk) );
                }
#line 2108 "y.tab.c"
    break;

  case 78: /* state: ASTERICKTOK  */
#line 625 "parser.y"
                {
                   (yyval.i_num) = WILDCARD_SPEC;
                }
#line 2116 "y.tab.c"
    break;

  case 79: /* action: INTTOK  */
#line 630 "parser.y"
                {
                   (yyval.i_num) = (yyvsp[0].constBlk)->theValue.theInt;
                   if(( (yyvsp[0].constBlk)->theValue.theInt < 0 ) 
                      || ((yyvsp[0].constBlk)->theValue.theInt >= gNumActions )) {
                      ERR_enter("Parser<ytab>:", currentLineNumber, 
                                BAD_ACTION_VAL, "" );
                      (yyval.i_num) = 0;
                   }
                   else
                      (yyval.i_num) = (yyvsp[0].constBlk)->theValue.theInt;
                   XFREE( (yyvsp[0].constBlk) );
                }
#line 2133 "y.tab.c"
    break;

  case 80: /* action: STRINGTOK  */
#line 643 "parser.y"
                {
                   int num;
                   num = H_lookup( (yyvsp[0].constBlk)->theValue.theString, nt_action );
                   if(( num < 0 ) || (num >= gNumActions )) {
                      ERR_enter("Parser<ytab>:", currentLineNumber, 
                                BAD_ACTION_STR, (yyvsp[0].constBlk)->theValue.theString );
                      (yyval.i_num) = 0;
                   }
                   else
                      (yyval.i_num) = num;

                   XFREE( (yyvsp[0].constBlk)->theValue.theString );
                   XFREE( (yyvsp[0].constBlk) );
                }
#line 2152 "y.tab.c"
    break;

  case 81: /* action: ASTERICKTOK  */
#line 658 "parser.y"
                {
                   (yyval.i_num) = WILDCARD_SPEC;
                }
#line 2160 "y.tab.c"
    break;

  case 82: /* obs: INTTOK  */
#line 663 "parser.y"
                {
                   if(( (yyvsp[0].constBlk)->theValue.theInt < 0 ) 
                      || ((yyvsp[0].constBlk)->theValue.theInt >= gNumObservations )) {
                      ERR_enter("Parser<ytab>:", currentLineNumber, 
                                BAD_OBS_VAL, "");
                      (yyval.i_num) = 0;
                   }
                   else
                      (yyval.i_num) = (yyvsp[0].constBlk)->theValue.theInt;
                   XFREE( (yyvsp[0].constBlk) );
                }
#line 2176 "y.tab.c"
    break;

  case 83: /* obs: STRINGTOK  */
#line 675 "parser.y"
                {
                   int num;
                   num = H_lookup( (yyvsp[0].constBlk)->theValue.theString, nt_observation );
                   if(( num < 0 ) || (num >= gNumObservations )) { 
                      ERR_enter("Parser<ytab>:", currentLineNumber, 
                                BAD_OBS_STR, (yyvsp[0].constBlk)->theValue.theString);
                      (yyval.i_num) = 0;
                   }
                   else
                      (yyval.i_num) = num;

                   XFREE( (yyvsp[0].constBlk)->theValue.theString );
                   XFREE( (yyvsp[0].constBlk) );
               }
#line 2195 "y.tab.c"
    break;

  case 84: /* obs: ASTERICKTOK  */
#line 690 "parser.y"
                {
                   (yyval.i_num) = WILDCARD_SPEC;
                }
#line 2203 "y.tab.c"
    break;

  case 85: /* ident_list: ident_list STRINGTOK  */
#line 695 "parser.y"
                {
                   enterString( (yyvsp[0].constBlk) );
                }
#line 2211 "y.tab.c"
    break;

  case 86: /* ident_list: STRINGTOK  */
#line 699 "parser.y"
                {
                   enterString( (yyvsp[0].constBlk) );
                }
#line 2219 "y.tab.c"
    break;

  case 87: /* prob: INTTOK  */
#line 704 "parser.y"
                {
		  (yyval.f_num) = (yyvsp[0].constBlk)->theValue.theInt;
		  if( curMatrixContext != mc_mdp_start )
		    if(( (yyval.f_num) < 0 ) || ((yyval.f_num) > 1 ))
		      ERR_enter("Parser<ytab>:", currentLineNumber, 
				BAD_PROB_VAL, "");
		  XFREE( (yyvsp[0].constBlk) );
		}
#line 2232 "y.tab.c"
    break;

  case 88: /* prob: FLOATTOK  */
#line 713 "parser.y"
                {
		  (yyval.f_num) = (yyvsp[0].constBlk)->theValue.theFloat;
		  if( curMatrixContext == mc_mdp_start )
		    ERR_enter("Parser<ytab>:", currentLineNumber, 
				    BAD_START_STATE_TYPE, "" );
		  else
		    if(( (yyval.f_num) < 0.0 ) || ((yyval.f_num) > 1.0 ))
			 ERR_enter("Parser<ytab>:", currentLineNumber, 
					 BAD_PROB_VAL, "" );
		  XFREE( (yyvsp[0].constBlk) );
		}
#line 2248 "y.tab.c"
    break;

  case 89: /* number: optional_sign INTTOK  */
#line 726 "parser.y"
                {
                   if( (yyvsp[-1].i_num) )
                      (yyval.f_num) = (yyvsp[0].constBlk)->theValue.theInt * -1.0;
                   else
                      (yyval.f_num) = (yyvsp[0].constBlk)->theValue.theInt;
                   XFREE( (yyvsp[0].constBlk) );
                }
#line 2260 "y.tab.c"
    break;

  case 90: /* number: optional_sign FLOATTOK  */
#line 734 "parser.y"
                {
                   if( (yyvsp[-1].i_num) )
                      (yyval.f_num) = (yyvsp[0].constBlk)->theValue.theFloat * -1.0;
                   else
                      (yyval.f_num) = (yyvsp[0].constBlk)->theValue.theFloat;
                   XFREE( (yyvsp[0].constBlk) );
                }
#line 2272 "y.tab.c"
    break;

  case 91: /* optional_sign: PLUSTOK  */
#line 743 "parser.y"
                {
                   (yyval.i_num) = 0;
                }
#line 2280 "y.tab.c"
    break;

  case 92: /* optional_sign: MINUSTOK  */
#line 747 "parser.y"
                {
                   (yyval.i_num) = 1;
                }
#line 2288 "y.tab.c"
    break;

  case 93: /* optional_sign: %empty  */
#line 751 "parser.y"
                {
                   (yyval.i_num) = 0;
                }
#line 2296 "y.tab.c"
    break;


#line 2300 "y.tab.c"

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

#line 758 "parser.y"


/********************************************************************/
/*              External Routines                                   */
/********************************************************************/

#define EPSILON  0.00001  /* tolerance for sum of probs == 1 */

Constant_Block *aConst;

/******************************************************************************/
void 
yyerror(char *string)
{
   ERR_enter("Parser<yyparse>", currentLineNumber, PARSE_ERR,"");
}  /* yyerror */
/******************************************************************************/
void 
checkMatrix(void) {
/* When a matrix is finished being read for the exactly correct number of
   values, curRow should be 0 and curCol should be -1.  For the cases
   where we are only interested in a row of entries curCol should be -1.
   If we get too many entries, then we will catch this as we parse the 
   extra entries.  Therefore, here we only need to check for too few 
   entries.
   */

   switch( curMatrixContext ) {
   case mc_trans_row:
      if( curCol < gNumStates )
         ERR_enter("Parser<checkMatrix>:", currentLineNumber, 
                   TOO_FEW_ENTRIES, "");
      break;
   case mc_trans_all:
      if((curRow < (gNumStates-1) )
	 || ((curRow == (gNumStates-1))
	     && ( curCol < gNumStates ))) 
	ERR_enter("Parser<checkMatrix>:", currentLineNumber,  
                   TOO_FEW_ENTRIES, "" );
      break;
   case mc_obs_row:
      if( curCol < gNumObservations )
         ERR_enter("Parser<checkMatrix>:", currentLineNumber, 
                   TOO_FEW_ENTRIES, "");
      break;
   case mc_obs_all:
      if((curRow < (gNumStates-1) )
	 || ((curRow == (gNumStates-1))
	     && ( curCol < gNumObservations ))) 
         ERR_enter("Parser<checkMatrix>:", currentLineNumber,  
                   TOO_FEW_ENTRIES, "" );
      break;
   case mc_start_belief:
      if( curCol < gNumStates )
	ERR_enter("Parser<checkMatrix>:", currentLineNumber, 
		  TOO_FEW_ENTRIES, "");
      break;

    case mc_mdp_start:
      /* We will check for invalid multiple entries for MDP in 
	 enterMatrix() */
      break;

    case mc_reward_row:
      if( gProblemType == POMDP_problem_type )
	if( curCol < gNumObservations )
	  ERR_enter("Parser<checkMatrix>:", currentLineNumber, 
		    TOO_FEW_ENTRIES, "");
      break;

    case mc_reward_all:
      if( gProblemType == POMDP_problem_type ) {
	if((curRow < (gNumStates-1) )
	   || ((curRow == (gNumStates-1))
	       && ( curCol < gNumObservations ))) 
	  ERR_enter("Parser<checkMatrix>:", currentLineNumber,  
		    TOO_FEW_ENTRIES, "" );
      }
      else
	if( curCol < gNumStates )
	  ERR_enter("Parser<checkMatrix>:", currentLineNumber, 
		    TOO_FEW_ENTRIES, "");
      
      break;
    case mc_reward_single:
      /* Don't need to do anything */
      break;

    case mc_reward_mdp_only:
      if((curRow < (gNumStates-1) )
	 || ((curRow == (gNumStates-1))
	     && ( curCol < gNumStates ))) 
	ERR_enter("Parser<checkMatrix>:", currentLineNumber,  
		  TOO_FEW_ENTRIES, "" );
      break;

   default:
      ERR_enter("Parser<checkMatrix>:", currentLineNumber, 
                BAD_MATRIX_CONTEXT, "" );
      break;
   }  /* switch */

   if( gTooManyEntries )
     ERR_enter("Parser<checkMatrix>:", currentLineNumber, 
	       TOO_MANY_ENTRIES, "" );

   /* After reading a line for immediate rewards for a pomdp, we must tell
      the data structures for the special representation that we are done */
   switch( curMatrixContext ) {
   case mc_reward_row:
   case mc_reward_all:
   case mc_reward_mdp_only:
     doneImmReward();
     break;

     /* This case is only valid for POMDPs, so if we have an MDP, we
	never would have started a new immediate reward, so calling 
	the doneImmReward will be in error.  */
   case mc_reward_single:
     if( gProblemType == POMDP_problem_type )
       doneImmReward();
     break;
   default:
     break;
   }  /* switch */
   

   curMatrixContext = mc_none;  /* reset this as a safety precaution */
}  /* checkMatrix */
/******************************************************************************/
void 
enterString( Constant_Block *block ) {
   
   if( H_enter( block->theValue.theString, curMnemonic ) == 0 )
      ERR_enter("Parser<enterString>:", currentLineNumber, 
                DUPLICATE_STRING, block->theValue.theString );

   XFREE( block->theValue.theString );
   XFREE( block );
}  /* enterString */
/******************************************************************************/
void 
enterUniformMatrix(void) {
   int a, i, j, obs;
   double prob;

   switch( curMatrixContext ) {
   case mc_trans_row:
      prob = 1.0/gNumStates;
      for( a = minA; a <= maxA; a++ )
         for( i = minI; i <= maxI; i++ )
            for( j = 0; j < gNumStates; j++ )
	       addEntryToIMatrix( IP[a], i, j, prob );
      break;
   case mc_trans_all:
      prob = 1.0/gNumStates;
      for( a = minA; a <= maxA; a++ )
         for( i = 0; i < gNumStates; i++ )
            for( j = 0; j < gNumStates; j++ )
 	       addEntryToIMatrix( IP[a], i, j, prob );
      break;
   case mc_obs_row:
      prob = 1.0/gNumObservations;
      for( a = minA; a <= maxA; a++ )
         for( j = minJ; j <= maxJ; j++ )
            for( obs = 0; obs < gNumObservations; obs++ )
 	       addEntryToIMatrix( IR[a], j, obs, prob );
      break;
   case mc_obs_all:
      prob = 1.0/gNumObservations;
      for( a = minA; a <= maxA; a++ )
         for( j = 0; j < gNumStates; j++ )
            for( obs = 0; obs < gNumObservations; obs++ )
 	       addEntryToIMatrix( IR[a], j, obs, prob );
      break;
   case mc_start_belief:
      setStartStateUniform();
      break;
   case mc_mdp_start:
      /* This is meaning less for an MDP */
      ERR_enter("Parser<enterUniformMatrix>:", currentLineNumber, 
                BAD_START_STATE_TYPE, "" );
      break;
   default:
      ERR_enter("Parser<enterUniformMatrix>:", currentLineNumber, 
                BAD_MATRIX_CONTEXT, "" );
      break;
   }  /* switch */
}  /* enterUniformMatrix */
/******************************************************************************/
void 
enterIdentityMatrix(void) {
   int a, i,j;

   switch( curMatrixContext ) {
   case mc_trans_all:
      for( a = minA; a <= maxA; a++ )
         for( i = 0; i < gNumStates; i++ )
            for( j = 0; j < gNumStates; j++ )
               if( i == j )
		 addEntryToIMatrix( IP[a], i, j, 1.0 );
               else
		 addEntryToIMatrix( IP[a], i, j, 0.0 );
      break;
   default:
      ERR_enter("Parser<enterIdentityMatrix>:", currentLineNumber, 
                BAD_MATRIX_CONTEXT, "" );
      break;
   }  /* switch */
}  /* enterIdentityMatrix */
/******************************************************************************/
void 
enterResetMatrix(void) {
  int a, i, j;

  if( curMatrixContext != mc_trans_row ) {
    ERR_enter("Parser<enterMatrix>:", currentLineNumber, 
	      BAD_RESET_USAGE, "" );
    return;
  }

  if( gProblemType == POMDP_problem_type )
    for( a = minA; a <= maxA; a++ )
      for( i = minI; i <= maxI; i++ )
	for( j = 0; j < gNumStates; j++ )
	  addEntryToIMatrix( IP[a], i, j, gInitialBelief[j] );
  
  else  /* It is an MDP */
    for( a = minA; a <= maxA; a++ )
      for( i = minI; i <= maxI; i++ )
	addEntryToIMatrix( IP[a], i, gInitialState, 1.0 );
  

}  /* enterResetMatrix */
/******************************************************************************/
void 
enterMatrix( double value ) {
/*
  For the '_single' context types we never have to worry about setting or 
  checking the bounds on the current row or col.  For all other we do and
  how this is done depends on the context.  Notice that we are filling in the 
  elements in reverse order due to the left-recursive grammar.  Thus
  we need to update the col and row backwards 
  */
   int a, i, j, obs;

   switch( curMatrixContext ) {
   case mc_trans_single:
      for( a = minA; a <= maxA; a++ )
         for( i = minI; i <= maxI; i++ )
            for( j = minJ; j <= maxJ; j++ )
	      addEntryToIMatrix( IP[a], i, j, value );
      break;
   case mc_trans_row:
      if( curCol < gNumStates ) {
         for( a = minA; a <= maxA; a++ )
            for( i = minI; i <= maxI; i++ )
	      addEntryToIMatrix( IP[a], i, curCol, value );
         curCol++;
      }
      else
	gTooManyEntries = 1;

      break;
   case mc_trans_all:
      if( curCol >= gNumStates ) {
         curRow++;
         curCol = 0;;
      }

      if( curRow < gNumStates ) {
         for( a = minA; a <= maxA; a++ )
	   addEntryToIMatrix( IP[a], curRow, curCol, value );
         curCol++;
      }
      else
	gTooManyEntries = 1;

      break;

   case mc_obs_single:

      if( gProblemType == POMDP_problem_type )
	/* We ignore this if it is an MDP */

	for( a = minA; a <= maxA; a++ )
	  for( j = minJ; j <= maxJ; j++ )
            for( obs = minObs; obs <= maxObs; obs++ )
	      addEntryToIMatrix( IR[a], j, obs, value );
      break;

   case mc_obs_row:
      if( gProblemType == POMDP_problem_type ) {
	/* We ignore this if it is an MDP */

	if( curCol < gNumObservations ) {

	  for( a = minA; a <= maxA; a++ )
            for( j = minJ; j <= maxJ; j++ )
	      addEntryToIMatrix( IR[a], j, curCol, value );
	  
	  curCol++;
	} else { 
	  gTooManyEntries = 1; 
	}
      }

      break;

   case mc_obs_all:
      if( curCol >= gNumObservations ) {
         curRow++;
         curCol = 0;
      }

      if( gProblemType == POMDP_problem_type ){
        /* We ignore this if it is an MDP */
        
        if( curRow < gNumStates ) {
          for( a = minA; a <= maxA; a++ )
            addEntryToIMatrix( IR[a], curRow, curCol, value );
          
          curCol++;
        } else {
          gTooManyEntries = 1;
        }
      }
      break;

/* This is a special case for POMDPs, since we need a special 
   representation for immediate rewards for POMDP's.  Note that this 
   is not valid syntax for an MDP, but we flag this error when we set 
   the matrix context, so we ignore the MDP case here.
   */
   case mc_reward_single:
      if( gProblemType == POMDP_problem_type ) {

	if( curCol == 0 ) {
	  enterImmReward( 0, 0, 0, value );
	  curCol++;
	}
	else
	  gTooManyEntries = 1;

      }
     break;

    case mc_reward_row:
      if( gProblemType == POMDP_problem_type ) {

	/* This is a special case for POMDPs, since we need a special 
	   representation for immediate rewards for POMDP's */
   
	if( curCol < gNumObservations ) {
	  enterImmReward( 0, 0, curCol, value );
	  curCol++;
	}
	else
	  gTooManyEntries = 1;

      }  /* if POMDP problem */

      else /* we are dealing with an MDP, so there should only be 
	      a single entry */
	if( curCol == 0 ) {
	  enterImmReward( 0, 0, 0, value );
	  curCol++;
	}
	else
	  gTooManyEntries = 1;


     break;

   case mc_reward_all:

      /* This is a special case for POMDPs, since we need a special 
	 representation for immediate rewards for POMDP's */

      if( gProblemType == POMDP_problem_type ) {
	if( curCol >= gNumObservations ) {
	  curRow++;
	  curCol = 0;
	}
	if( curRow < gNumStates ) {
	  enterImmReward( 0, curRow, curCol, value );
	  curCol++;
	}
	else
	  gTooManyEntries = 1;

      }  /* If POMDP problem */

      /* Otherwise it is an MDP and we should be expecting an entire
	 row of rewards. */

      else  /* MDP */
	if( curCol < gNumStates ) {
	  enterImmReward( 0, curCol, 0, value );
	  curCol++;
	}
	else
	  gTooManyEntries = 1;

      break;

      /* This is a special case for an MDP only where we specify
	 the entire matrix of rewards. If we are erroneously 
	 definining a POMDP, this error will be flagged in the 
	 setMatrixContext() routine.
	 */

    case mc_reward_mdp_only:
      if( gProblemType == MDP_problem_type ) {
	if( curCol >= gNumStates ) {
	  curRow++;
	  curCol = 0;
	}
	if( curRow < gNumStates ) {
	  enterImmReward( curRow, curCol, 0, value );
	  curCol++;
	}
	else
	  gTooManyEntries = 1;

      }
      break;

    case mc_mdp_start:

      /* For an MDP we only want to see a single value and */
      /* we want it to correspond to a valid state number. */

      if( curCol > 0 )
	gTooManyEntries = 1;

      else {
	gInitialState = value;
	curCol++;
      }
      break;
	  
   case mc_start_belief:

      /* This will process the individual entries when a starting */
      /* belief state is fully specified.  When it is a POMDP, we need */
      /* an entry for each state, so we keep the curCol variable */
      /* updated.  */

      if( curCol < gNumStates ) {
	gInitialBelief[curCol] = value;
	curCol++;
      }
      else
	gTooManyEntries = 1;

      break;

   default:
      ERR_enter("Parser<enterMatrix>:", currentLineNumber, 
                BAD_MATRIX_CONTEXT, "");
      break;
   }  /* switch */

}  /* enterMatrix */
/******************************************************************************/
void 
setMatrixContext( Matrix_Context context, 
		  int a, int i, int j, int obs ) {
/* 
   Note that we must enter the matrix entries in reverse order because
   the matrices are defined with left-recursive rules.  Set the a, i,
   and j parameters to be less than zero when you want to define it
   for all possible values.  

   Rewards for MDPs and POMDPs differ since in the former, rewards are not
   based upon an observations.  This complicates things since not only is one 
   of the reward syntax options not valid, but the semantics of all the
   rewards change as well.  I have chosen to handle this in this routine.  
   I will check for the appropriate type and set the context to handle the
   proper amount of entries.
*/
  int state;

   curMatrixContext = context;
   gTooManyEntries = 0;  /* Clear this out before reading any */

   curRow = 0;  /* This is ignored for some contexts */
   curCol = 0;

   switch( curMatrixContext ) {

   case mc_start_belief:
     
     break;

   case mc_start_include:

     /* When we specify the starting belief state as a list of states */
     /* to include, we initialize all state to 0.0, since as we read */
     /* the states we will set that particular value to 1.0.  After it */
     /* is all done we can then just normalize the belief state */

     if( gProblemType == POMDP_problem_type ) {
       for( state = 0; state < gNumStates; state++ )
	 gInitialBelief[state] = 0.0;

     } else {  /* It is an MDP which is not valid */
       ERR_enter("Parser<setMatrixContext>:", currentLineNumber, 
		 BAD_START_STATE_TYPE, "");
     }
     break;

   case mc_start_exclude:

     /* When we are specifying the starting belief state as a a list */
     /* of states, we initialize all states to 1.0 and as we read each */
     /* in the list we clear it out to be zero.  fter it */
     /* is all done we can then just normalize the belief state */

     if( gProblemType == POMDP_problem_type )
       for( state = 0; state < gNumStates; state++ )
	 gInitialBelief[state] = 1.0;

     else  /* It is an MDP which is not valid */
       ERR_enter("Parser<setMatrixContext>:", currentLineNumber, 
		 BAD_START_STATE_TYPE, "");

     break;

  /* We need a special representation for the immediate rewards.
     These four cases initialize the data structure that will be
     needed for immediate rewards by calling newImmReward.  Note that
     the arguments will differe depending upon whether it is an
     MDP or POMDP.
     */
  case mc_reward_mdp_only:
    if( gProblemType == POMDP_problem_type )  {
       ERR_enter("Parser<setMatrixContext>:", currentLineNumber, 
		 BAD_REWARD_SYNTAX, "");
    }
    else {
      newImmReward( a, NOT_PRESENT, NOT_PRESENT, 0 );
    } 
    break;
 
  case mc_reward_all:	
    if( gProblemType == POMDP_problem_type ) 
      newImmReward( a, i, NOT_PRESENT, NOT_PRESENT );

    else {
      newImmReward( a, i, NOT_PRESENT, 0 );
    }
    break;
  case mc_reward_row:
    if( gProblemType == POMDP_problem_type ) 
      newImmReward( a, i, j, NOT_PRESENT );
    
    else {
      newImmReward( a, i, j, 0 );
    } 
    break;
  case mc_reward_single:

    if( gProblemType == MDP_problem_type ) {
       ERR_enter("Parser<setMatrixContext>:", currentLineNumber, 
		 BAD_REWARD_SYNTAX, "");
    }
    else {
       newImmReward( a, i, j, obs );
     }
    break;

   default:
     break;
   }

  /* These variable settings will define the range over which the current 
     matrix context will have effect.  This accounts for wildcards by
     setting the range to include everything.  When a single entry was
     specified, the range is that single number.  When we actually 
     start to read the matrix, each entry we see will apply for the
     entire range specified, though for specific entries the range 
     will be a single number.
     */
   if( a < 0 ) {
      minA = 0;
      maxA = gNumActions - 1;
   }
   else
      minA = maxA = a;

   if( i < 0 ) {
      minI = 0;
      maxI = gNumStates - 1;
   }
   else
      minI = maxI = i;

   if( j < 0 ) {
      minJ = 0;
      maxJ = gNumStates - 1;
   }
   else
      minJ = maxJ = j;

   if( obs < 0 ) {
      minObs = 0;
      maxObs = gNumObservations - 1;
   }
   else
      minObs = maxObs = obs;

}  /* setMatrixContext */
/******************************************************************************/
void 
enterStartState( int i ) {
/*
   This is not valid for an MDP, but the error has already been flagged
   in the setMatrixContext() routine.  Therefore, if just igore this if 
   it is an MDP.
*/

  if( gProblemType == MDP_problem_type )
    return;

  switch( curMatrixContext ) {
  case mc_start_include:
    gInitialBelief[i] = 1.0;
    break;
  case mc_start_exclude:
    gInitialBelief[i] = 0.0;
    break;
  default:
    ERR_enter("Parser<enterStartState>:", currentLineNumber, 
	      BAD_MATRIX_CONTEXT, "");
      break;
  } /* switch */
}  /* enterStartState */
/******************************************************************************/
void 
setStartStateUniform(void) {
  int i;
  double prob;

  if( gProblemType != POMDP_problem_type )
    return;

  prob = 1.0/gNumStates;
  for( i = 0; i < gNumStates; i++ )
    gInitialBelief[i] = prob;

}  /*  setStartStateUniform*/
/******************************************************************************/
void 
endStartStates(void) {
/*
   There are a few cases where the matrix context will not be
   set at this point.  When there is a list of probabilities
   or if it is an MDP the context will have been cleared.
   */
  int i;
  double prob;

  if( gProblemType == MDP_problem_type ) {
    curMatrixContext = mc_none;  /* just to be sure */
    return;
  }
    
  switch( curMatrixContext ) {
  case mc_start_include:
  case mc_start_exclude:
    /* At this point gInitialBelief should be a vector of 1.0's and 0.0's
       being set as each is either included or excluded.  Now we need to
       normalized them to make it a true probability distribution */
    prob = 0.0;
    for( i = 0; i < gNumStates; i++ )
      prob += gInitialBelief[i];
    if( prob <= 0.0 ) {
      ERR_enter("Parser<endStartStates>:", currentLineNumber, 
                BAD_START_PROB_SUM, "" );
      return;
    }
    for( i = 0; i < gNumStates; i++ )
      gInitialBelief[i] /= prob;
    break;

  default:  /* Make sure we have a valid prob. distribution */
    prob = 0.0;
    for( i = 0; i < gNumStates; i++ ) 
      prob += gInitialBelief[i];
    if((prob < ( 1.0 - EPSILON)) || (prob > (1.0 + EPSILON))) {
      ERR_enter("Parser<endStartStates>:", NO_LINE, 
		BAD_START_PROB_SUM, "" );
    }
    break;
  }  /* switch */

  curMatrixContext = mc_none;

}  /* endStartStates */
/******************************************************************************/
void 
verifyPreamble(void) {
/* 
   When a param is not defined, set these to non-zero so parsing can
   proceed even in the absence of specifying these values.  When an
   out of range value is encountered the parser will flag the error,
   but return 0 so that more errors can be detected 
   */

   if( discountDefined == 0 )
      ERR_enter("Parser<verifyPreamble>:", currentLineNumber, 
                MISSING_DISCOUNT, "" );
   if( valuesDefined == 0 )
      ERR_enter("Parser<verifyPreamble>:", currentLineNumber,
                MISSING_VALUES, "" );
   if( statesDefined == 0 ) {
      ERR_enter("Parser<verifyPreamble>:", currentLineNumber, 
                MISSING_STATES, "" );
      gNumStates = 1;
   }
   if( actionsDefined == 0 ) {
      ERR_enter("Parser<verifyPreamble>:", currentLineNumber, 
                MISSING_ACTIONS, "" );
      gNumActions = 1;
   }

   /* If we do not see this, them we must be parsing an MDP */
   if( observationsDefined == 0 ) {
     gNumObservations = 0;
     gProblemType = MDP_problem_type;
   }

   else
     gProblemType = POMDP_problem_type;

}  /* verifyPreamble */
/******************************************************************************/
void 
checkProbs(void) {
   int a,i,j;
   //int a,i,j,obs;
   double sum;
   char str[512];

   
   for( a = 0; a < gNumActions; a++ )
      for( i = 0; i < gNumStates; i++ ) {
	 sum = sumIMatrixRowValues( IP[a], i );
         if((sum < ( 1.0 - EPSILON)) || (sum > (1.0 + EPSILON))) {
            sprintf( str, "action=%d, state=%d (%.5lf)", a, i, sum );
            ERR_enter("Parser<checkProbs>:", NO_LINE, 
                      BAD_TRANS_PROB_SUM, str );
         }
      } /* for i */

   if( gProblemType == POMDP_problem_type )
     for( a = 0; a < gNumActions; a++ )
       for( j = 0; j < gNumStates; j++ ) {
	 sum = sumIMatrixRowValues( IR[a], j );
         if((sum < ( 1.0 - EPSILON)) || (sum > (1.0 + EPSILON))) {
	   sprintf( str, "action=%d, state=%d (%.5lf)", a, j, sum );
	   ERR_enter("Parser<checkProbs>:", NO_LINE, 
		     BAD_OBS_PROB_SUM, str );
         } /* if sum not == 1 */
       }  /* for j */

   /* Now see if we had observation specs defined in an MDP */

   if( observationSpecDefined && (gProblemType == MDP_problem_type))
     ERR_enter("Parser<checkProbs>:", NO_LINE, 
	       OBS_IN_MDP_PROBLEM, "" );

}  /* checkProbs */
/************************************************************************/
void 
initParser(void) {
/*
   This routine will reset all the state variables used by the parser
   in case it will parse multiple files.
*/
   observationSpecDefined = 0;
   discountDefined = 0;
   valuesDefined = 0;
   statesDefined = 0;
   actionsDefined = 0;
   observationsDefined = 0;
   observationSpecDefined = 0;
   currentLineNumber = 1;
   curMnemonic = nt_unknown;
   curMatrixContext = mc_none;

}  /* initParser */
/************************************************************************/
int 
readMDPFile( FILE *file ) {
   int returnValue, dump_status;
   extern FILE *yymdpin;

   initParser();

   ERR_initialize();
   H_create();
   yymdpin = file;

   returnValue = yyparse();

   /* If there are syntax errors, then we have to do something if we 
      want to parse another file without restarting.  It seems that
      a syntax error bombs the code out, but leaves the file pointer
      at the place it bombed.  Thus, another call to yyparse() will
      pick up where it left off and not necessarily at the start of a 
      new file.

      Unfortunately, I do not know how to do this yet.
      */
   if (returnValue != 0) {
      printf("\nParameter file contains syntax errors!\n");
    }

   dump_status = ERR_dump();

   ERR_cleanUp();
   H_destroy();

   if (dump_status || returnValue ) 
      return( 0 );

   /* This is where intermediate matrix representation are
      converted into their final representation */
   convertMatrices();

   return( 1 );
}  /* readPomdpFile */

/************************************************************************/
int
yymdpwrap(void)
{
   return 1;
}
/************************************************************************/

