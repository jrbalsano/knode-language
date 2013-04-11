%{
    /* DECLARATIONS
     * ============
     * declarations for variables that we want to use in the program
     * ie: 
     * int symtable[10] = 0
     *
     */
#include <stdio.h>

void yyerror(char *s);
%}

    /* Tokens & Associations
     * =====================
     * This section specifies tokens, and associativity of operators
     * ie:
     * %token NUMBER
     * %left PLUS
     * 
     */

%defines

%union {
  int ival;
  char *sval;
  char cval;
}

%token MAIN
%token STRING_LITERAL
%token NEWLINE
%token BLOCK_START
%token PRINT
%token IDENTIFIER


    /* Grammar 
     * =======
     * The grammar goes below the %%. This section is here b/c of the way yacc
     * handles comments...General format follows. Remember that actions to the
     * grammar are assigned through the use of a curly brace following the
     * statement {}
     * ie:
     * statement_list
     *      : statement {statement_count++}
     *      | statement statement_list
     *
     */
%%

translationunit       : externaldeclaration
                      | translationunit externaldeclaration
                      ;
externaldeclaration   : functiondefinition
                      ;
functiondefinition    : declarator compoundstatement
                      ;
declarator            : identifier
                      | declarator '(' parameterlist ')' ':' NEWLINE
                      ;
parameterlist         : parameterdeclaration
                      ;
parameterdeclaration  : 
                      ;
identifier            : IDENTIFIER
                      | PRINT
                      | MAIN
                      ;
compoundstatement     : BLOCK_START statementlist
                      ;
statementlist         : statement
                      ;
statement             : expressionstatement
                      ;
expressionstatement   : expression NEWLINE
                      ;
expression            : unaryexpression
                      ;
unaryexpression       : postfixexpression
                      ;
postfixexpression     : primaryexpression
                      ;
primaryexpression     : identifier '(' argumentexpressionlist ')'
                      | STRING_LITERAL      { printf("%s\n", yylval.sval); }
                      ;
argumentexpressionlist : expression
                       ;
%%

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

int main(void) {
  yyparse();
  return 0;
}
