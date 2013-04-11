%{
/* Declarations
 * ============
 */
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

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
\n                              return NEWLINE;
"print"                         return PRINT;
"main"                          return MAIN;
"("                             return *yytext;
")"                             return *yytext; 
":"                             return *yytext;
{new_block}                     return BLOCK_START;
{string}                        return STRING_LITERAL; 
%%

int main(int argc, char* argv[]) {
  yylex();
}


