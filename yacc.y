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
TranslationUnit root = NULL;

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
  char cval;
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
  Parameter parameter;
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
%type<ival> INTEGER typename INT DOUBLE CHAR STRING  NODE DICT EDGE PLUSEQ MINUSEQ MULTEQ DIVEQ MODEQ assignmentoperator
%type<fval> DOUBLEVAL
%type<cval> unaryoperator '-' '+' '!' '*' '%' '/' '>' '<'
%type<symp> IDENTIFIER
%type<expression> postfixexpression primaryexpression multiplicativeexpression additiveexpression unaryexpression assignmentexpression equalityexpression expression castexpression andexpression orexpression conditionalexpression relationalexpression
%type<identifier> identifier
%type<declarator> declarator
%type<statement> expressionstatement statement selectionstatement iterationstatement breakstatement nodestatement dictstatement edgestatement alledgestatement
%type<functionDefinition> functiondefinition externaldeclaration
%type<compoundStatement> compoundstatement
%type<grammarList> argumentexpressionlist parameterlist statementlist
%type<translationUnit> translationunit
%type<parameter> parameterdeclaration
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

translationunit : externaldeclaration { $$ = getTranslationUnit($1); root = $$; }
  | translationunit externaldeclaration
  ;
externaldeclaration : functiondefinition { $$ = $1; }
  ;
functiondefinition : declarator compoundstatement { $$ = getFunctionDefinition($1, $2); }
  | typename declarator compoundstatement
  | NODE declarator compoundstatement
  | EDGE declarator compoundstatement
  ;
declarator  : identifier '(' parameterlist ')' ':' NEWLINE { $$ = getDeclarator($1, $3); }
  | identifier '(' ')' ':' NEWLINE { $$ = declaratorId($1); }
  ;
parameterlist : parameterlist ',' parameterdeclaration {$$ = addFront($1,$3);}
  | parameterdeclaration {$$ = newParameterList($1)}
  ;
parameterdeclaration : typename identifier { $$ = getTypedParameter($1, $2); }
  | NODE identifier { $$ = getTypedParameter($1, $2); }
  | DICT identifier { $$ = getTypedParameter($1, $2); }
  | EDGE identifier { $$ = getTypedParameter($1, $2); }
  ;
identifier : IDENTIFIER { $$ = getIdentifier(yylval.sval); }
  ;
compoundstatement : BLOCK_START statementlist BLOCK_END { $$ = newCompoundStatement($2); }
  ;
statementlist : statement { $$ = newStatementList($1); }
  | statementlist statement
  ;
statement : expressionstatement { $$ = $1; }
  | iterationstatement { $$ = NULL; }
  | selectionstatement { $$ = NULL; }
  | nodestatement { $$ = NULL; }
  | breakstatement { $$ = getStatement($1); }
  | dictstatement { $$ = NULL; }
  | dictlist { $$ = NULL; }
  | edgestatement { $$ = NULL; }
  ;
dictstatement : DICT IDENTIFIER NEWLINE {}
  | DICT IDENTIFIER '[' INTEGER ']' NEWLINE
  | DICT IDENTIFIER '[' INTEGER ']' NEWLINE compoundstatement
  | DICT IDENTIFIER compoundstatement 
  ;
breakstatement : BREAK NEWLINE { $$ = newBreakStatement(); }
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
  | IDENTIFIER ':' STRING_LITERAL NEWLINE { $1->value = $3; printf("%s\n", (char *)$1->value);}
  | IDENTIFIER ':' INTEGER NEWLINE { /*$1->value = $3; printf("%d\n", (int *)$1->value);*/}
  | IDENTIFIER ':' BOOLEAN NEWLINE { /*$1->value = $3; printf("%d\n", (int *)$1->value);*/}
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
expression : assignmentexpression { $$ = getExpression($1); }
  | expression ',' assignmentexpression { $$ = getExpressionAssignmentExpression($1, $3); }
  ;
assignmentexpression : conditionalexpression { $$ = getAssign($1); }
  | unaryexpression assignmentoperator assignmentexpression { $$ = getTokenizedAssignment($1, $2, $3); }
  | unaryexpression '=' assignmentexpression { $$ = getAssignment($1, $3); }
  | typename identifier '=' assignmentexpression { $$ = getInit($1, $2, $4); }
  ;
assignmentoperator : PLUSEQ { $$ = $1; }
  | MINUSEQ { $$ = $1; }
  | MULTEQ { $$ = $1; }
  | DIVEQ { $$ = $1; }
  | MODEQ { $$ = $1; }
  ;
conditionalexpression : orexpression { $$ = getCond($1); }
  ;
orexpression : orexpression OR andexpression { $$ = getOr($1, $3); }
  | andexpression { $$ = getOrExpression($1); }
  ;
andexpression : andexpression AND equalityexpression { $$ = getAnd($1, $3); }
  | equalityexpression { $$ = getAndExpression($1); }
  ;
equalityexpression : relationalexpression { $$ = getEqExpression($1); }
  | equalityexpression EQ relationalexpression { $$ = getEqual($1, $3); }
  | equalityexpression NE relationalexpression { $$ = getNotEqual($1, $3); }
  ;
relationalexpression : additiveexpression { $$ = getRelatExpression($1); }
  | relationalexpression '<' additiveexpression { $$ = getSingleCharRelat($1, $2, $3); }
  | relationalexpression '>' additiveexpression { $$ = getSingleCharRelat($1, $2, $3); }
  | relationalexpression LE additiveexpression { $$ = getLeRelat($1, $3); }
  | relationalexpression GE additiveexpression { $$ = getGeRelat($1, $3); }
  ;
additiveexpression : multiplicativeexpression { $$ = getAdditiveExpression($1); }
  | additiveexpression '+' multiplicativeexpression { $$ = getAddExpression($1, $2, $3); } 
  | additiveexpression '-' multiplicativeexpression { $$ = getAddExpression($1, $2, $3); }
  ;
multiplicativeexpression : castexpression { $$ = getMultExpression($1); }
  | multiplicativeexpression '*' castexpression { $$ = getMultiplyExpression($1, $2, $3); }
  | multiplicativeexpression '/' castexpression { $$ = getMultiplyExpression($1, $2, $3); }
  | multiplicativeexpression '%' castexpression { $$ = getMultiplyExpression($1, $2, $3); }
  ;
castexpression : unaryexpression { $$ = getCastExpression($1); }
  | '(' typename ')' castexpression { $$ = getTypedCast($2, $4); }
  | '(' NODE ')' castexpression { $$ = getTypedCast(NODE, $4); }
  | '(' DICT ')' castexpression { $$ = getTypedCast(DICT, $4); }
  | '(' EDGE ')' castexpression { $$ = getTypedCast(EDGE, $4); }
  ;
typename : INT
  | DOUBLE
  | CHAR
  | STRING
  ;
unaryexpression : postfixexpression { $$ = getUnaryExpression($1); }
  | PLUSPLUS unaryexpression { $$ = getUnaryIncr($2); }
  | MINUSMINUS unaryexpression { $$ = getUnaryDecr($2); }
  | unaryoperator unaryexpression {$$ = getUnarySingleOp($1, $2); }
  ;

unaryoperator : '+' { $$ = $1; }
  | '-' { $$ = $1; }
  | '!' { $$ = $1; }
  | '*' { $$ = $1; }
  ;
postfixexpression : primaryexpression { $$ = getPostfixExpression($1); }
  | postfixexpression '[' expression ']' { $$ = getPostfixBracketExpression($1, $3); } 
  | postfixexpression '.' identifier { $$ = getPostfixIdentifierExpression($1, $3); }
  | postfixexpression PLUSPLUS { $$ = getPostfixIncr($1); }
  | postfixexpression MINUSMINUS { $$ = getPostfixDecr($1); }
  | postfixexpression '(' ')' { $$ = $1; }
  | postfixexpression '(' argumentexpressionlist ')' { $$ = getPostfixArgumentExpression($1, $3); }
  ;
primaryexpression : STRING_LITERAL { $$ = getPrimaryStringExpression(yylval.sval); }
  | INTEGER { char x[1000]; sprintf(x, "%d", yylval.ival); $$ = getPrimaryStringExpression(x); }
  | BOOLEAN { char x[1000]; sprintf(x, "%d", yylval.ival); $$ = getPrimaryStringExpression(x); }
  | DOUBLEVAL { char x[1000]; sprintf(x, "%f", yylval.fval); $$ = getPrimaryStringExpression(x); }
  | identifier { $$ = getPrimaryIdentifierExpression($1); }
  | '(' expression ')' { $$ = $2} 
  ;
argumentexpressionlist : assignmentexpression { $$ = newArgumentExpressionList($1); }
  | argumentexpressionlist ',' assignmentexpression { $$ = addFront($1, $3); }
  ;
%%
void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
  errorHad = 1;
}

int main(void) {
  yyparse();
  freeTranslationUnit(root);
  if(errorHad)
    return 1;
  else
    return 0;
}
