%{
/* Declarations
* ============
*/
#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"
#include "symtable.h"

%}

/* Rules/Aliases
* =============
*/

/* don't call yywrap when finished */
%option noyywrap


integer   [1-9][0-9]*|0
double    [0-9]+\.[0-9]+
operator  [-+*/=%!<>]
string    \"[^\n]*[^\\]\"
boolean   "TRUE"|"FALSE"


%%
"++"                            printf("PLUSPLUS\n"); return PLUSPLUS;
"--"                            printf("MINUSMINUS\n"); return MINUSMINUS;
"+="                            printf("+=\n"); return PLUSEQ;
"-="                            printf("==\n"); return MINUSEQ;
"/="                            printf("/=\n"); return DIVEQ;
"%="                            printf("%%=\n"); return MODEQ;
"*="                            printf("*=\n"); return MULTEQ;  
">="                            printf(">=\n"); return GE;
"<="                            printf("<=\n"); return LE;
"=="                            printf("==\n"); return EQ;
"!="                            printf("!=\n"); return NE;
"<=>"				            printf("ALLEDGE\n"); return ALLEDGE;
"<->"				            printf("BOTHEDGE\n"); return BOTHEDGE;
"<-"				            printf("LEFTEDGE\n"); return LEFTEDGE;
"->"				            printf("RIGHTEDGE\n"); return RIGHTEDGE;
"while"                         printf("WHILE\n"); return WHILE;
"if"                            printf("IF\n"); return IF;
"else"                          printf("ELSE\n"); return ELSE;
"for"                           printf("FOR\n"); return FOR;
"break"                         printf("BREAK\n"); return BREAK;
{operator}                      printf("%s\n", yytext); return *yytext;
{integer}                       printf("INTEGER\n");  yylval.ival = atoi(yytext); return INTEGER;
{double}                        printf("DOUBLEVAL\n");  yylval.fval = atof(yytext); return DOUBLEVAL;
{boolean}                       {
                                    printf("BOOLEAN\n");  
                                    yylval.ival = yytext[0] == 'T' ? 1 : 0; 
                                    printf("BOOL'S TRUE COLORS: %d\n", yylval.ival);
                                    return BOOLEAN;
                                }
"and"                         	printf("AND\n");  return AND; 
"or"                      	    printf("OR\n");  return OR; 
^[ ]*\n                         ;
\n                              printf("NEWLINE\n"); return NEWLINE;
"print"                         printf("PRINT\n"); yylval.sval = yytext; return IDENTIFIER;
"main"                          printf("MAIN\n"); yylval.sval = yytext; return IDENTIFIER;
"("                             printf("(\n"); return *yytext;
")"                             printf(")\n"); return *yytext; 
":"                             printf(":\n"); return *yytext;
"{"                             printf("BLOCK_START\n"); return BLOCK_START;
"}"                             printf("BLOCK_END\n"); return BLOCK_END;
";"                             printf(";\n"); return *yytext;
"["                             printf("[\n"); return *yytext;
"]"                             printf("]\n"); return *yytext;
","                             printf(",\n"); return *yytext;
"."                             printf(".\n"); return *yytext;
"int"                           printf("INT\n"); return INT;
"double"                        printf("DOUBLE\n"); return DOUBLE;
"char"                          printf("CHAR\n"); return CHAR;
"string"                        printf("STRING\n"); return STRING;
"node"                          printf("NODE\n"); yylval.sval = yytext; return NODE;
"dict"                          printf("DICT\n"); yylval.sval = yytext; return DICT;
"edge"                          printf("EDGE\n"); return EDGE;
{string}                        {
                                  printf("STRING_LITERAL\n"); 
                                  yylval.sval = yytext;
                                  return STRING_LITERAL; 
                                }
[a-z_][a-zA-Z0-9_]*             {
                                    /*
                                     * NOTE: THIS IS A SUPER HACKY WAY TO
                                     * RECOGNIZE IDENTIFIERS, AND IS ONLY A
                                     * STOPGAP SOLUTION FOR NOW. IT ONLY WORKS
                                     * BECAUSE IT'S IN THE LAST POSITION
                                     * TODO: fix this by moving identifier
                                     * recognition into symbol table with used
                                     * variables/keywords
                                     */
                                    printf("IDENTIFIER\n");
                                    //printf("%s\n", yytext);
                                    //check the symbol table with symlook and return a pointer to the symbol table
                                    struct symtab *sp = symlook(yytext);
                                    yylval.symp = sp;
                                    return IDENTIFIER;
                                }
%%

