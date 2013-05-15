%{
/* Declarations
* ============
*/
#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"

%}

/* Rules/Aliases
* =============
*/

/* don't call yywrap when finished */
%option noyywrap yylineno


integer   [1-9][0-9]*|0
double    [0-9]+\.[0-9]+
operator  [-+*/=%!<>]
string    \"([^\n\"]|\\\")*[^\\]\"
bool_literal   "TRUE"|"FALSE"


%%
"++"                            return PLUSPLUS;
"--"                            return MINUSMINUS;
"+="                            return PLUSEQ;
"-="                            return MINUSEQ;
"/="                            return DIVEQ;
"%="                            return MODEQ;
"*="                            return MULTEQ;  
">="                            return GE;
"<="                            return LE;
"=="                            return EQ;
"!="                            return NE;
"<=>"				                    return ALLEDGE;
"<->"				                    return BOTHEDGE;
"<-"				                    return LEFTEDGE;
"->"				                    return RIGHTEDGE;
"while"                         return WHILE;
"if"                            return IF;
"else"                          return ELSE;
"for"                           return FOR;
"break"                         return BREAK;
{operator}                      return *yytext;
{integer}                       yylval.ival = atoi(yytext); return INTEGER;
{double}                        yylval.fval = atof(yytext); return DOUBLEVAL;
{bool_literal}                  {
                                    yylval.ival = yytext[0] == 'T' ? 1 : 0; 
                                    return BOOL_LITERAL;
                                }
"and"                         	 return AND; 
"or"                      	     return OR; 
^[ ]*\n                         ;
\n                              return NEWLINE;
"print"                         yylval.sval = yytext; return IDENTIFIER;
"main"                          yylval.sval = yytext; return IDENTIFIER;
"("                             return *yytext;
")"                             return *yytext; 
":"                             return *yytext;
"{"                             return BLOCK_START;
"}"                             return BLOCK_END;
";"                             return *yytext;
"["                             return *yytext;
"]"                             return *yytext;
","                             return *yytext;
"."                             return *yytext;
"int"                           return INT;
"boolean"                       return BOOLEAN;
"double"                        return DOUBLE;
"char"                          return CHAR;
"string"                        return STRING;
"node"                          yylval.sval = yytext; return NODE;
"dict"                          yylval.sval = yytext; return DICT;
"edge"                          return EDGE;
{string}                        {
                                  
                                  yylval.sval = yytext;
                                  return STRING_LITERAL; 
                                }
[a-z_][a-zA-Z0-9_]*             {
                                    yylval.sval = yytext;
                                    return IDENTIFIER;
                                }
.                               ;
%%

