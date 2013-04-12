%{
    /* DECLARATIONS
     * ============
     * declarations for variables that we want to use in the program
     * ie: 
     * int symtable[10] = 0
     *
     */
#include <stdio.h>

union val {
  int ival;
  char *sval;
  char cval;
};

typedef struct node {
  struct node *left;
  struct node *right;
  char *code;
  union val lval;
};
void yyerror(char *s);
node mknode(node *left, node *right, char *code);
void frnode(node *n);


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
  Expression expression;
  Identifier identifier;
  Declarator declarator;
  Statement statement;
  FunctionDefinition functionDefinition;
  CompoundStatement compoundStatement;
  GrammarList grammarList;
  TranslationUnit translationunit;
}

%defines

%token STRING_LITERAL
%token NEWLINE
%token BLOCK_START
%token IDENTIFIER

%type<sval> STRING_LITERAL IDENTIFIER
%type<expression> postfixexpression primaryexpression unaryexpression expression
%type<identifier> identifier
%type<declarator> declarator
%type<statement> expressionstatement statement
%type<functionDefinition> functiondefinition externaldeclaration
%type<compoundStatement> compoundstatement
%type<grammarList> argumentexpressionlist parameterlist statementlist
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
parameterlist : parameterdeclaration
  ;
parameterdeclaration : 
  ;
identifier : IDENTIFIER { $$ = getIdentifier(yylval.sval) }
  ;
compoundstatement : BLOCK_START statementlist { $$ = newCompoundStatement($1); }
  ;
statementlist : statement { $$ = newStatementList($1); }
  ;
statement : expressionstatement { $$ = $1 }
  ;
expressionstatement : expression NEWLINE { $$ = getExpressionStatement($1); }
  ;
expression : unaryexpression { $$ = $1; }
  ;
unaryexpression : postfixexpression { $$ = $1; }
  ;
postfixexpression : primaryexpression { $$ = $1; }
  ;
primaryexpression : identifier '(' argumentexpressionlist ')' { $$ = getFunctionExpression($1, $3); }
  | STRING_LITERAL { $$ = getStringExpression(yylval.sval); }
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

node *mknode(node *left, node *right, char *code) {
  node newnode;
  newnode.left = left;
  newnode.right = right;
  char *newcode = malloc(sizeof(char) * strlen(code));
  strcpy(newcode, code);
  newnode.code = newcode;
}

void frnode(node *n) {
  char *code = n->code;
  n->code = NULL;
  free(code);
  free(n);
}
