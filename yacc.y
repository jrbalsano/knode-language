%{
    /* DECLARATIONS
     * ============
     * declarations for variables that we want to use in the program
     * ie: 
     * int symtable[10] = 0
     *
     */
#include <stdio.h>
#include <string.h>
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
  int ival;
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
%token FOR
%token IF
%token ELSE
%token INTEGER
%token NE
%token NODE
%left '+' '-'
%left '*' '/' '%'
%type<sval> STRING_LITERAL IDENTIFIER
%type<ival> INTEGER
%type<expression> postfixexpression primaryexpression multiplicativeexpression additiveexpression unaryexpression expression
%type<identifier> identifier
%type<declarator> declarator
%type<statement> expressionstatement statement selectionstatement iterationstatement nodestatement
%type<functionDefinition> functiondefinition externaldeclaration
%type<compoundStatement> compoundstatement
%type<grammarList> argumentexpressionlist parameterlist parameterdeclaration statementlist
%type<translationUnit> translationunit
%nonassoc IFX
%nonassoc ELSE


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
parameterlist : parameterdeclaration { $$ = $1; }
  ;
parameterdeclaration : { $$ = NULL; }
  ;
identifier : IDENTIFIER { $$ = getIdentifier(yylval.sval); }
  ;
compoundstatement : BLOCK_START statementlist BLOCK_END { $$ = newCompoundStatement($2); }
  ;
statementlist : statement { $$ = newStatementList($1); }
  | statementlist statement
  ;
statement : expressionstatement { $$ = $1; }
  | iterationstatement
  | selectionstatement
  | nodestatement
  ;
nodestatement : NODE NEWLINE
  ;
selectionstatement : IF '(' expression ')' NEWLINE compoundstatement %prec IFX
  | IF '(' expression ')' NEWLINE compoundstatement ELSE NEWLINE compoundstatement 
  ;
iterationstatement : WHILE '(' expression ')' NEWLINE compoundstatement
  | FOR '(' expression ';' expression ';' expression ')' NEWLINE compoundstatement
  ;
expressionstatement : expression NEWLINE { $$ = getExpressionStatement($1); }
  ;
expression : additiveexpression 
  ;
additiveexpression : multiplicativeexpression 
  | additiveexpression '+' multiplicativeexpression 
  | additiveexpression '-' multiplicativeexpression 
  ;
multiplicativeexpression : unaryexpression 
  | multiplicativeexpression '*' unaryexpression 
  | multiplicativeexpression '/' unaryexpression 
  | multiplicativeexpression '%' unaryexpression 
  ;
unaryexpression : postfixexpression 
  ;
postfixexpression : primaryexpression 
  ;
primaryexpression : identifier '(' argumentexpressionlist ')' { $$ = getFunctionExpression($1, $3); }
  | STRING_LITERAL { $$ = getStringExpression(yylval.sval); }
  | INTEGER { char x[1000]; sprintf(x, "%d", yylval.ival); $$ = getStringExpression(x); } 
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
