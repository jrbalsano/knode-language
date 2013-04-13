%{
/* Declarations
 * ============
 */
#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"
#include "yacc.tab.h"

unsigned int level = 0;
void process_indent(char* line);
void fakeEOF();


%}

    /* Rules/Aliases
     * =============
     */

  /* don't call yywrap when finished */
%option noyywrap

  /* new_block is incredibly hacky. Please be careful. */
whtspc      ^[ ]+[^\n ] 
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
"{"                             printf("BLOCK_START\n"); return BLOCK_START;
"}"                             printf("BLOCK_END\n"); return BLOCK_END;
{whtspc}                        {
                                  char *yycopy = strdup(yytext);
                                  unput(yycopy[yyleng - 1]);
                                  process_indent(yycopy);
                                  free(yycopy);
                                }
{string}                        {
                                  printf("STRING_LITERAL\n"); 
                                  yylval.sval = yytext;
                                  return STRING_LITERAL; 
                                }
"{EOF}"                         yyterminate();
<<EOF>>                         fakeEOF(); process_indent(""); 
%%

unsigned int white_count(char* line) {
  unsigned int count = 0 ;
  while (*line == ' ')
    count++, line++ ;
  return count ;
}

void fakeEOF() {
  unput('}');
  unput('F'); 
  unput('O'); 
  unput('E'); 
  unput('{');
}

void process_indent(char* line) {
  unsigned int indent = white_count(line) ;

  if (indent == level * 2) {
    return;
  }

  if (indent == (level + 1) * 2) {
    level++;
    unput('{');
    return;
  }

  while (indent >= (level - 1) * 2) {
    level--;
    unput('}');
  }
}
