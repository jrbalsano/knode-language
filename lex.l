%{
/* Declarations
 * ============
 */
#include <stdio.h>
#include <stdlib.h>

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
^[ ]*\n                         {/* Ignore blank lines. */}
\n                              { printf("NEWLINE\n"); }
"print"                         { printf("PRINT\n"); }
"main"                          { printf("MAIN\n"); }
"("                             { printf("LPAR\n"); }
")"                             { printf("RPAR\n"); }
":"                             { printf("COL\n"); }
{new_block}                     { printf("NEW_BLOCK\n"); }
{string}                        { printf("STRING_LITERAL: %s\n", yytext); }
.                               { printf("Unmatched Pattern: %s\n", yytext); }
%%

int main(int argc, char* argv[]) {
  yylex();
}


