
%option noinput
%option nounput

%{
//#include "lp.c"
//#include "y.tab.c"
#include "y.tab.h"
#include "lpkit.h"
#include "lpglob.h"

/* These are defined in the parser lp.y. */
extern char Last_var[];
extern char Constraint_name[];
extern int Lin_term_count;
extern REAL f;
extern int x;
extern int isign;
extern int make_neg;
extern int Within_int_decl;

%}

WS   [ \n\t]+
LT   [A-Za-z]
KR   [A-Za-z0-9_\[\]\{\}/.&#$%~'@^]
DI   [0-9]
NM   {DI}*\.?{DI}+([Ee][-+]?{DI}+)?
VR   {LT}{KR}*(<{KR}+>)?
S_OP [-+ \t\n]+
LOG  [<>]?=?

%start COMMENT

%%
<INITIAL>"/*" {
  BEGIN COMMENT;
} /* begin skip comment */

<COMMENT>"*/" {
  BEGIN INITIAL;
} /* end skip comment */

<COMMENT>. {
}

<COMMENT>\n {
}

<INITIAL>{WS} {
}

<INITIAL>"," {
  return(COMMA);
}

<INITIAL>[mM][iI][nN]":" {
  return(MINIMISE);
}

<INITIAL>[mM][aA][xX]":" {
  return(MAXIMISE);
}

<INITIAL>{NM} {
  f = atof((char *)yytext);
  return(CONS);
} /* f contains the last float */

<INITIAL>{S_OP} {
  Sign = 0;
  for(x = 0; x < yyleng; x++)
    if(yytext[x] == '-' || yytext[x] == '+')
      Sign = (Sign == (yytext[x] == '+'));
  return (SIGN);
  /* Sign is TRUE if the sign-string
     represents a '-'. Otherwise Sign
     is FALSE */
}

<INITIAL>[Ii][Nn][Tt] {
  Within_int_decl = TRUE;
  return(VAR);
}

<INITIAL>{VR} {
  strcpy(Last_var, (char *)yytext);
  return(VAR);
}

<INITIAL>":" {
  return (COLON);
}

<INITIAL>"*" {
  return(AR_M_OP);
}

<INITIAL>{LOG} {
  return(RE_OP);
}

<INITIAL>";" {
  Within_int_decl = FALSE;
  return(END_C);
}

<INITIAL>. {
  fprintf(stderr,"LEX ERROR : %s lineno %d \n" ,yytext,yylineno);
}

%%
