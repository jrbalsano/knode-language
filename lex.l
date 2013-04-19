%{
/* Declarations
* ============
*/
#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"
#include "yacc.tab.h"

%}

/* Rules/Aliases
* =============
*/

/* don't call yywrap when finished */
%option noyywrap


integer   [1-9][0-9]*|0
operator  [-+*/=%!]
string    \"[^\n]*[^\\]\"
boolean   "TRUE"|"FALSE"
bool_op   "and"|"or"

%%


">="                            printf(">=\n"); return GE;
"<="                            printf("<=\n"); return LE;
"=="                            printf("==\n"); return EQ;
"!="                            printf("!=\n"); return NE;
"and"				printf("AND"); return AND;
"or"				printf("OR"); return OR;
"while"                         printf("WHILE\n"); return WHILE;
"if"                            printf("IF\n"); return IF;
"else"                          printf("ELSE\n"); return ELSE;
{operator}                      printf("%s\n", yytext); return *yytext;
{integer}                       printf("INTEGER\n");  yylval.ival = atoi(yytext); return INTEGER;
{boolean}                       printf("BOOLEAN\n");  yylval.ival = yytext[0] == 'T' ? 1 : 0; return BOOLEAN;
{bool_op}                       printf("%s\n", yytext);  yylval.sval = yytext; return BOOL_OP; 
^[ ]*\n                         ;
\n                              printf("NEWLINE\n"); return NEWLINE;
"print"                         printf("PRINT\n"); yylval.sval = yytext; return IDENTIFIER;
"main"                          printf("MAIN\n"); yylval.sval = yytext; return IDENTIFIER;
"("                             printf("(\n"); return *yytext;
")"                             printf(")\n"); return *yytext; 
":"                             printf(":\n"); return *yytext;
"{"                             printf("BLOCK_START\n"); return BLOCK_START;
"}"                             printf("BLOCK_END\n"); return BLOCK_END;
{string}                        {
                                  printf("STRING_LITERAL\n"); 
                                  yylval.sval = yytext;

                                  return STRING_LITERAL; 
                                }
%%
