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

  /* new_block is incredibly hacky. Please be careful. */
new_block   ^[ ]{2} 
string      \"[^\n]*[^\\]\"

%%

    /* Tokens & Actions */
^[ ]*\n                         ;
\n                              printf("NEWLINE\n"); return NEWLINE;
"print"                         printf("PRINT\n"); yylval.sval = yytext; return IDENTIFIER;
"main"                          printf("MAIN\n"); yylval.sval = yytext; return IDENTIFIER;
"("                             printf("(\n"); return *yytext;
")"                             printf(")\n"); return *yytext; 
":"                             printf(":\n"); return *yytext;
{new_block}                     printf("BLOCK_START\n"); return BLOCK_START;
{string}                        {
                                  printf("STRING_LITERAL\n"); 
                                  yylval.sval = yytext;
                                  return STRING_LITERAL; 
                                }

%%
