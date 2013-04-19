
%{
/* Declarations
 * ============
 */
#include <stdio.h>
#include <stdlib.h>
#include "arithlex.h"
%}

%option noyywrap

integer   [1-9][0-9]*
operator  [-+*/<>=]
parens    [()]
zero      0

%%

integer         printf("INTEGER"); yylval.iValue = atoi(yytext); return INTEGER;
zero            printf("INTEGER"); yylval.iValue = atoi(yytext); return INTEGER;
operator        printf("OP"); return *yytext;

<<EOF>>       process_indent(""); yyterminate();
%%
