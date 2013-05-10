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
#include "walker.h"


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
%token BOOL_LITERAL
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
%type<ival> INTEGER BOOLEAN typename INT BOOL_LITERAL DOUBLE CHAR STRING NODE DICT EDGE PLUSEQ MINUSEQ MULTEQ DIVEQ MODEQ assignmentoperator edge alledge LEFTEDGE RIGHTEDGE ALLEDGE BOTHEDGE
%type<fval> DOUBLEVAL
%type<cval> unaryoperator '-' '+' '!' '*' '%' '/' '>' '<'
%type<symp> IDENTIFIER
%type<expression> postfixexpression primaryexpression multiplicativeexpression additiveexpression unaryexpression assignmentexpression equalityexpression expression castexpression andexpression orexpression conditionalexpression relationalexpression
%type<identifier> identifier
%type<declarator> declarator
%type<statement> expressionstatement statement selectionstatement iterationstatement breakstatement nodestatement dictstatement edgestatement dictlist declstatement
%type<functionDefinition> functiondefinition
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

translationunit : functiondefinition { $$ = getTranslationUnit($1); root = $$; }
  | translationunit functiondefinition
  ;
functiondefinition : declarator compoundstatement { $$ = getFunctionDefinition($1, $2); }
  | typename declarator compoundstatement { $$ = getRetTypeFunctionDefinition($1, $2, $3); }
  | NODE declarator compoundstatement { $$ = getRetTypeFunctionDefinition($1, $2, $3); }
  | EDGE declarator compoundstatement { $$ = getRetTypeFunctionDefinition($1, $2, $3); }
  | DICT declarator compoundstatement { $$ = getRetTypeFunctionDefinition($1, $2, $3); }
  ;
declarator  : identifier '(' parameterlist ')' ':' NEWLINE { $$ = getDeclarator($1, $3); }
  | identifier '(' ')' ':' NEWLINE { $$ = declaratorId($1); }
  ;
parameterlist : parameterlist ',' parameterdeclaration {$$ = addBack($1,$3);}
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
  | statementlist statement { $$ = extendStatementList($1, $2); }
  ;
statement : expressionstatement { $$ = getStatement($1); }
  | iterationstatement { $$ = getStatement($1) }
  | selectionstatement { $$ = getStatement($1); }
  | nodestatement { $$ = getStatement($1); }
  | breakstatement { $$ = getStatement($1); }
  | dictstatement { $$ = getStatement($1); }
  | dictlist { $$ = getStatement($1); }
  | edgestatement { $$ = getStatement($1); }
  | declstatement { $$ = getStatement($1); } 
  ;
declstatement : typename identifier NEWLINE { $$ = getDeclarationStatement($1, $2); }
  ;
dictstatement : DICT identifier NEWLINE { $$ = getDictDecStatement($2); }
  | DICT identifier NEWLINE compoundstatement { $$ = getDictDefStatement($2, $4); }
  ;
breakstatement : BREAK NEWLINE { $$ = newBreakStatement(); }
  ;
nodestatement : NODE identifier NEWLINE {$$ = newNodeCreateStatement($2);}
  | NODE identifier '=' expression NEWLINE {$$ = newNodeAssignmentStatement($2, $4);}
  | NODE identifier NEWLINE compoundstatement {$$ = newNodeDictAssignmentStatement($2, $4);}
  ;
selectionstatement : IF '(' expression ')' NEWLINE compoundstatement %prec IFX {$$ = newIfStatement($3,$6);}
  | IF '(' expression ')' NEWLINE compoundstatement ELSE NEWLINE compoundstatement {$$ = newIfElseStatement($3,$6,$9);}
  ;
iterationstatement : WHILE '(' expression ')' NEWLINE compoundstatement {$$ = newWhileStatement($3,$6);}
  | FOR '(' expression ';' expression ';' expression ')' NEWLINE compoundstatement { $$ = newForStatement($3,$5,$7,$10);}
  ;
expressionstatement : expression NEWLINE { $$ = getExpressionStatement($1); }
  ;
dictlist : identifier ':' expression NEWLINE { $$ = getDictListStatement($1, $3); }
  ;
edgestatement: EDGE identifier '=' '[' unaryexpression edge unaryexpression ']' NEWLINE { $$ = getEdgeStatementFromNodes($2, $5, $6, $7); }
  | EDGE identifier NEWLINE { $$ = getEdgeDeclaration($2); }
  ;
alledge: ALLEDGE
  | edge
  ;
edge: BOTHEDGE
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
  | unaryexpression alledge unaryexpression { $$ = getAssignEdgeExpression($1, $2, $3); }
  ;
assignmentoperator : PLUSEQ { $$ = PLUSEQ; }
  | MINUSEQ { $$ = MINUSEQ; }
  | MULTEQ { $$ = MULTEQ; }
  | DIVEQ { $$ = DIVEQ; }
  | MODEQ { $$ = MODEQ; }
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
typename : INT { $$ = INT; }
  | DOUBLE { $$ = DOUBLE; }
  | CHAR { $$ = CHAR; }
  | BOOLEAN { $$ = BOOLEAN; }
  | STRING { $$ = STRING; }
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
  | postfixexpression '(' ')' { $$ = getPostfixEmptyArgument($1); }
  | postfixexpression '(' argumentexpressionlist ')' { $$ = getPostfixArgumentExpression($1, $3); }
  ;
primaryexpression : STRING_LITERAL { $$ = getPrimaryStringExpression(yylval.sval); }
  | INTEGER { char x[1000]; sprintf(x, "%d", yylval.ival); $$ = getPrimaryStringExpression(x); }
  | BOOL_LITERAL { char x[1000]; sprintf(x, "%d", yylval.ival); $$ = getPrimaryStringExpression(x); }
  | DOUBLEVAL { char x[1000]; sprintf(x, "%f", yylval.fval); $$ = getPrimaryStringExpression(x); }
  | identifier { $$ = getPrimaryIdentifierExpression($1); }
  | '(' expression ')' { $$ = getPrimaryParenExpression($2);} 
  ;
argumentexpressionlist : assignmentexpression { $$ = newArgumentExpressionList($1); }
  | argumentexpressionlist ',' assignmentexpression { $$ = addBack($1, $3); }
  ;
%%
void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
  errorHad = 1;
}

int main(void) {
  yyparse();
  startWalk(root);
  freeTranslationUnit(root);
  if(errorHad)
    return 1;
  else
    return 0;
}
