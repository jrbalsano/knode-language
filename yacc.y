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
#include "symtable.h"

void yyerror(char *s);
int errorHad = 0;
struct symtab *symtable = NULL;

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
  float fval;
  struct symtab *symp;
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
%token DOUBLEVAL
%token NE
%left AND
%left OR
%token BOOLEAN
%token PLUSEQ
%token MINUSEQ
%token MULTEQ
%token DIVEQ
%token MODEQ
%token PLUSPLUS
%token MINUSMINUS
%token INT
%token DOUBLE
%token CHAR
%token STRING
%token NODE
%token DICT
%token EDGE
%token ALLEDGE
%token LEFTEDGE
%token RIGHTEDGE
%token BOTHEDGE
%token BREAK
%right '=' PLUSEQ MINUSEQ MULTEQ DIVEQ MODEQ
%nonassoc EQ NE
%nonassoc '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%type<sval> STRING_LITERAL
%type<ival> INTEGER
%type<fval> DOUBLEVAL
%type<symp> IDENTIFIER
%type<expression> postfixexpression primaryexpression multiplicativeexpression additiveexpression unaryexpression assignmentexpression equalityexpression expression castexpression andexpression orexpression conditionalexpression relationalexpression 
%type<identifier> identifier
%type<declarator> declarator
%type<statement> expressionstatement statement selectionstatement iterationstatement breakstatement nodestatement dictstatement edgestatement alledgestatement
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
  | translationunit externaldeclaration
  ;
externaldeclaration : functiondefinition { $$ = $1; }
  ;
functiondefinition : declarator compoundstatement { $$ = getFunctionDefinition($1, $2); }
  | typename declarator compoundstatement
  | NODE declarator compoundstatement
  | EDGE declarator compoundstatement
  ;
declarator  : identifier '(' parameterlist ')' ':' NEWLINE { $$ = getDeclarator(declaratorId($1), $3); }
  | identifier '(' ')' ':' NEWLINE { $$ = declaratorId($1); }
  ;
parameterlist : parameterlist ',' parameterdeclaration
  | parameterdeclaration
  ;
parameterdeclaration : typename identifier{ $$ = NULL; }
  | NODE identifier
  | DICT identifier
  | EDGE identifier
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
  | breakstatement
  | dictstatement
  | dictlist
  | edgestatement
  ;
dictstatement : DICT IDENTIFIER NEWLINE
  | DICT IDENTIFIER '[' INTEGER ']' NEWLINE
  | DICT IDENTIFIER '[' INTEGER ']' NEWLINE compoundstatement
  | DICT IDENTIFIER compoundstatement 
  ;
breakstatement : BREAK NEWLINE
  ;

nodestatement : NODE IDENTIFIER NEWLINE
  | NODE IDENTIFIER EQ IDENTIFIER
  | NODE IDENTIFIER NEWLINE compoundstatement
  ;
selectionstatement : IF '(' expression ')' NEWLINE compoundstatement %prec IFX
  | IF '(' expression ')' NEWLINE compoundstatement ELSE NEWLINE compoundstatement 
  ;
iterationstatement : WHILE '(' expression ')' NEWLINE compoundstatement
  | FOR '(' expression ';' expression ';' expression ')' NEWLINE compoundstatement
  ;
expressionstatement : expression NEWLINE { $$ = getExpressionStatement($1); }
  ;
dictlist : IDENTIFIER ':' IDENTIFIER NEWLINE
  | IDENTIFIER ':' STRING_LITERAL NEWLINE
  | IDENTIFIER ':' INTEGER NEWLINE
  | IDENTIFIER ':' BOOLEAN NEWLINE
  ;
edgestatement: EDGE IDENTIFIER '=' '[' IDENTIFIER alledgestatement IDENTIFIER ']' NEWLINE
  | IDENTIFIER alledgestatement IDENTIFIER NEWLINE
  | IDENTIFIER alledgestatement IDENTIFIER '['INTEGER']' NEWLINE
  ;
alledgestatement: ALLEDGE
  | BOTHEDGE
  | LEFTEDGE
  | RIGHTEDGE
  ;
expression : assignmentexpression
  | expression ',' assignmentexpression
  ;
assignmentexpression : conditionalexpression
  | unaryexpression assignmentoperator assignmentexpression
  | typename IDENTIFIER '=' assignmentexpression
  ;
assignmentoperator : '='
  | PLUSEQ
  | MINUSEQ
  | MULTEQ
  | DIVEQ
  | MODEQ
  ;
equalityexpression : relationalexpression
  | equalityexpression EQ relationalexpression
  | equalityexpression NE relationalexpression 
  ;
relationalexpression : additiveexpression
  | relationalexpression '<' additiveexpression
  | relationalexpression '>' additiveexpression
  | relationalexpression LE additiveexpression
  | relationalexpression GE additiveexpression
  ;
additiveexpression : multiplicativeexpression 
  | additiveexpression '+' multiplicativeexpression 
  | additiveexpression '-' multiplicativeexpression 
  ;
multiplicativeexpression : castexpression 
  | multiplicativeexpression '*' castexpression 
  | multiplicativeexpression '/' castexpression 
  | multiplicativeexpression '%' castexpression 
  ;
castexpression : unaryexpression
  | '(' typename ')' castexpression
  | '(' NODE ')' castexpression
  | '(' DICT ')' castexpression
  | '(' EDGE ')' castexpression
  ;
typename : INT
  | DOUBLE
  | CHAR
  | STRING
  ;
unaryexpression : postfixexpression
  | PLUSPLUS unaryexpression
  | MINUSMINUS unaryexpression
  | unaryoperator unaryexpression
  ;
conditionalexpression : orexpression
  ;
orexpression : orexpression OR andexpression
  | andexpression
  ;
andexpression : andexpression AND equalityexpression  
  | equalityexpression
  ;
unaryoperator : '+'
  | '-'
  | '!'
  | '*'
  ;
postfixexpression : primaryexpression
  | postfixexpression '[' expression ']' 
  | postfixexpression '.' identifier 
  | postfixexpression PLUSPLUS 
  | postfixexpression MINUSMINUS
  | postfixexpression '(' ')'
  | postfixexpression '(' argumentexpressionlist ')'
  ;
primaryexpression : STRING_LITERAL { $$ = getStringExpression(yylval.sval); }
  | INTEGER { char x[1000]; sprintf(x, "%d", yylval.ival); $$ = getStringExpression(x); }
  | DOUBLEVAL { char x[1000]; sprintf(x, "%f", yylval.fval); $$ = getStringExpression(x); }
  | identifier { $$ = getPrimaryExpression($1); }
  | '(' expression ')' { $$ = $2} 
  ;
argumentexpressionlist : assignmentexpression { $$ = newArgumentExpressionList($1); }
  | argumentexpressionlist ',' assignmentexpression
  ;
%%
void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
  errorHad = 1;
}

int main(void) {
  yyparse();
  if(errorHad)
    return 1;
  else
    return 0;
}
