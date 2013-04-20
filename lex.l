%{
/* Declarations
* ============
*/
#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"
#include "yacc.tab.h"

char *keywords[19];
a[0] = "node"
a[1] = "double"
a[2] = "if"
a[3] = "dict"
a[4] = "explore"
a[5] = "examine"
a[6] = "edge"
a[7] = "else"
a[8] = "int"
a[9] = "and"
a[10] = "null"
a[11] = "follow"
a[12] = "char"
a[13] = "for"
a[14] = "while"
a[15] = "or"
a[16] = "string"
a[17] = "final"

%}

/* Rules/Aliases
* =============
*/

/* don't call yywrap when finished */
%option noyywrap


integer   [1-9][0-9]*|0
operator  [-+*/=%!]
string    \"[^\n]*[^\\]\"

%%


">="                            printf(">=\n"); return GE;
"<="                            printf("<=\n"); return LE;
"=="                            printf("==\n"); return EQ;
"!="                            printf("!=\n"); return NE;
"while"                         printf("WHILE\n"); return WHILE;
"if"                            printf("IF\n"); return IF;
"else"                          printf("ELSE\n"); return ELSE;
"for"                           printf("FOR\n"); return FOR;
{operator}                      printf("%s\n", yytext); return *yytext;
{integer}                       printf("INTEGER\n"); yylval.ival = atoi(yytext); return INTEGER;
^[ ]*\n                         ;
\n                              printf("NEWLINE\n"); return NEWLINE;
"print"                         printf("PRINT\n"); yylval.sval = yytext; return IDENTIFIER;
"node ".*                       printf("NODE\n"); yylval.sval = yytext; return NODE;
[a-z_][\w]*                     {
                                    if (checkKeywords()) return IDENTIFIER;
                                }
"main"                          printf("MAIN\n"); yylval.sval = yytext; return IDENTIFIER;
"("                             printf("(\n"); return *yytext;
")"                             printf(")\n"); return *yytext; 
":"                             printf(":\n"); return *yytext;
"{"                             printf("BLOCK_START\n"); return BLOCK_START;
"}"                             printf("BLOCK_END\n"); return BLOCK_END;
";"                             printf(";\n"); return *yytext;
{string}                        {
                                  printf("STRING_LITERAL\n"); 
                                  yylval.sval = yytext;

                                  return STRING_LITERAL; 
                                }
%%

int checkKeywords() {
    
    return 0;
}
