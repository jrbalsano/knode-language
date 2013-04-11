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
}

%defines

%token STRING_LITERAL
%token NEWLINE
%token BLOCK_START
%token IDENTIFIER

%type<n> expression unaryexpression postfixexpression primaryexpression argumentexpressionlist
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

translationunit : externaldeclaration { $$ = TranslationUnit($1); }
  ;
externaldeclaration : functiondefinition { $$ = $1; }
  ;
functiondefinition : declarator compoundstatement { $$ = FunctionDefinition($1, $2); }
  ;
declarator  : identifier { $$ = DeclaratorId($1); }
  | declarator '(' parameterlist ')' ':' NEWLINE { $$ = Declarator($1, $3); }
  ;
parameterlist : parameterdeclaration
  ;
parameterdeclaration : 
  ;
identifier : IDENTIFIER { $$ = yylval.sval }
  ;
compoundstatement : BLOCK_START statementlist { $$ = CompoundStatement($1); }
  ;
statementlist : statement { $$ = StatementListFromSingle($1); }
  ;
statement : expressionstatement { $$ = $1 }
  ;
expressionstatement : expression NEWLINE { $$ = ExpressionStatement($1); }
  ;
expression : unaryexpression { $$ = $1; }
  ;
unaryexpression : postfixexpression { $$ = $1; }
  ;
postfixexpression : primaryexpression { $$ = $1; }
  ;
primaryexpression : identifier '(' argumentexpressionlist ')' { $$ = FunctionExpression($1, $3); }
  | STRING_LITERAL { $$ = StringExpression(yylval.sval); }
  ;
argumentexpressionlist : expression { $$ = ArgumentExpressionList($1); }
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
