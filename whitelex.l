%{
/* Declarations
 * ============
 */
#include <stdio.h>
#include <stdlib.h>
#include "whitelex.h"
%}

%option noyywrap

%%

^[ ]*\n       ;

^[ ]*[^\n ]   {
                process_indent(yytext);
                printf("%c", yytext[yyleng-1]);
              }
#.*\          
<<EOF>>       process_indent(""); yyterminate();
%%

unsigned int white_count(char* line) {
  unsigned int count = 0 ;
  while (*line == ' ')
    count++, line++ ;
  return count ;
}

void process_indent(char* line) {
  unsigned int indent = white_count(line) ;

  if (indent == level * 2) {
    return;
  }

  if (indent == (level + 1) * 2) {
    level++;
    printf("{");
    return;
  }

  while (indent >= (level - 1) * 2) {
    level--;
    printf("}");
  }
}

int main() {
  yylex();
  return 0;
}
