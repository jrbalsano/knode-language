%{
    /* DECLARATIONS
     * ============
     * declarations for variables that we want to use in the program
     * ie: 
     * int symtable[10] = 0
     *
     */
#include <stdio.h>
#include "absyn.h"

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
%union {
  char *sval;
  int iValue;
  Identifier identifier;
  Declarator declarator;
  Statement statement;
  FunctionDefinition functionDefinition;
  CompoundStatement compoundStatement;
  GrammarList grammarList;
  TranslationUnit translationUnit;
  Expression expression;
}

%defines

%token STRING_LITERAL
%token NEWLINE
%token BLOCK_START
%token BLOCK_END
%token IDENTIFIER
%token GE
%token LE
%token EQ
%token WHILE
%token IF
%token ELSE
%token INTEGER
%token NE
%left '+' '-'
%left '*' '/' '%'
%type<sval> STRING_LITERAL IDENTIFIER INTEGER
%type<expression> postfixexpression primaryexpression multiplicativeexpression additiveexpression unaryexpression expression
%type<identifier> identifier
%type<declarator> declarator
%type<statement> expressionstatement statement
%type<functionDefinition> functiondefinition externaldeclaration
%type<compoundStatement> compoundstatement
%type<grammarList> argumentexpressionlist parameterlist parameterdeclaration statementlist
%type<translationUnit> translationunit


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

translationunit : externaldeclaration { $$ = getTranslationUnit($1); }
  ;
externaldeclaration : functiondefinition { $$ = $1; }
  ;
functiondefinition : declarator compoundstatement { $$ = getFunctionDefinition($1, $2); }
  ;
declarator  : identifier { $$ = declaratorId($1); }
  | declarator '(' parameterlist ')' ':' NEWLINE { $$ = getDeclarator($1, $3); }
  ;
parameterlist : parameterdeclaration { $$ = $1 }
  ;
parameterdeclaration : { $$ = NULL }
  ;
identifier : IDENTIFIER { $$ = getIdentifier(yylval.sval) }
  ;
compoundstatement : BLOCK_START statementlist BLOCK_END { $$ = newCompoundStatement($2); }
  ;
statementlist : statement { $$ = newStatementList($1); }
  ;
statement : expressionstatement { $$ = $1 }
  ;
expressionstatement : expression NEWLINE { $$ = getExpressionStatement($1); }
  ;
expression : additiveexpression { $$ = $1} 
  ;
additiveexpression : multiplicativeexpression { $$ = $1}
  | additiveexpression '+' multiplicativeexpression { $$ = $1 + $3 }
  | additiveexpression '-' multiplicativeexpression { $$ = $1 - $3 }
  ;
multiplicativeexpression : unaryexpression { $$ = $1 }
  | multiplicativeexpression '*' unaryexpression { $$ = $1 * $3}
  | multiplicativeexpression '/' unaryexpression { $$ = $1 / $3}
  | multiplicativeexpression '%' unaryexpression { $$ = $1 % $3}
  ;
unaryexpression : postfixexpression { $$ = $1; }
  ;
postfixexpression : primaryexpression { $$ = $1; }
  ;
primaryexpression : identifier '(' argumentexpressionlist ')' { $$ = getFunctionExpression($1, $3); }
  | STRING_LITERAL { $$ = getStringExpression(yylval.sval); }
  | INTEGER
  ;
argumentexpressionlist : expression { $$ = newArgumentExpressionList($1); }
  ;
%%
void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

int main(void) {
  yyparse();
  return 0;
}
