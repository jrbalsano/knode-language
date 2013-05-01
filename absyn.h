#ifndef __ABSYN_H__
#define __ABSYN_H__

#include <stdio.h>
#include "symtable.h"

/**
 * Abstract Syntax Tree for Knode
 * This code creates the structs used for our grammar.
 */
typedef struct expression_ *Expression;
typedef struct identifier_ *Identifier;
typedef struct declarator_ *Declarator;
typedef struct statement_ *Statement;
typedef struct functionDefinition_ *FunctionDefinition;
typedef struct compoundStatement_ *CompoundStatement; 
typedef struct grammarList_ *GrammarList;
typedef struct grammarNode_ *GrammarNode;
typedef struct translationUnit_ *TranslationUnit;
typedef struct parameter_ *Parameter;

#include "yacc.tab.h"

struct expression_ {
  enum {none = 0, function, unary, postfix, primary, string, cast, mult, add, relat, eq} type;
  union {
    Expression e;
    Identifier i;
    GrammarList l;
    char *s;
    int typnam;
  } sub1;
  union {
    Expression e;
    Identifier i;
    GrammarList l;
  } sub2;
  union {
    enum{postfix_none = none, postincr, postdecr, bracket, identifier, arg} postfix;
    enum{unary_none = none, preincr, predecr, positive = '+', negative = '-', negate = '!', clone = '*'} unary;
    enum{cast_none = none, typed} cast;
    enum{mult_none = none, times = '*', divide = '/', mod = '%'} mult;
    enum{add_none = none, plus = '+', minus = '-'} add;
    enum{relat_none = none, less = '<', greater = '>', le, ge} relat;
    enum{eq_none = none, equal, notequal} eq;
    enum{gen_none = none, comma = ','} none;
  } deriv;
};

struct identifier_ {
  char *symbol;
  struct symtab *sp;
};
struct declarator_ {
  Identifier name;
  GrammarList p; //A list of parameters
};
struct statement_ {
  enum {statement_none = none, expression} type;
  union {
    Expression e;
    Statement s;
  } sub;
};
struct parameter_ {
	int type;
	Identifier i;
};
struct functionDefinition_ {
  Declarator d;
  CompoundStatement cs;
};
struct compoundStatement_ {
  GrammarList dlist; //A list of declarations
  GrammarList sList; //A list of statements
};
struct translationUnit_ {
  FunctionDefinition f;
};
struct grammarList_ {
  enum {argument, statement,parameterList} type;
  GrammarNode head;
};
struct grammarNode_ {
  GrammarNode next;
  void *data;
};

GrammarList addFront(GrammarList g, void *data);
TranslationUnit getTranslationUnit(FunctionDefinition fd);
FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs);
Declarator declaratorId(Identifier id);
Declarator getDeclarator(Identifier id, GrammarList pList);
CompoundStatement newCompoundStatement(GrammarList sList);
GrammarList newStatementList(Statement s);
GrammarList newParameterList(Parameter p);
Parameter getTypedParameter(int typname, Identifier i);
GrammarList appendToPList(GrammarList pList,Parameter param);
Statement getExpressionStatement(Expression e);
Expression getFunctionExpression(Identifier id, GrammarList argExpList);
Expression getPrimaryStringExpression(char *s);
GrammarList newArgumentExpressionList(Expression e);
Identifier getIdentifier(char *s);
Expression getPrimaryIdentifierExpression(Identifier id);
Expression getPostfixExpression(Expression e1);
Expression getPostfixBracketExpression(Expression e1, Expression e2);
Expression getPostfixIdentifierExpression(Expression e, Identifier id);
Expression getPostfixIncr(Expression e);
Expression getPostfixDecr(Expression e);
Expression getPostfixArgumentExpression(Expression e1, GrammarList argList);
void freeParameter(Parameter p);
Expression getUnaryExpression(Expression e);
Expression getUnaryIncr(Expression e);
Expression getUnaryDecr(Expression e);
Expression getUnarySingleOp(char c, Expression e);
Expression getCastExpression(Expression e);
Expression getTypedCast(int token, Expression e);
Expression getMultExpression(Expression e);
Expression getMultiplyExpression(Expression e1, char c, Expression e2);
Expression getAdditiveExpression(Expression e1);
Expression getAddExpression(Expression e1, char c, Expression e2);
Expression getRelatExpression(Expression e);
Expression getSingleCharRelat(Expression e1, char c, Expression e2);
Expression getLeRelat(Expression e1, Expression e2);
Expression getGeRelat(Expression e1, Expression e2);
Expression getEqExpression(Expression e);
Expression getEqual(Expression e1, Expression e2);
Expression getNotEqual(Expression e1, Expression e2);
Expression getExpression(Expression e);
Expression getExpressionAssignmentExpression(Expression e1, Expression e2);
void freeTranslationUnit(TranslationUnit t); 
void freeFunctionDefinition(FunctionDefinition f);
void freeDeclarator(Declarator d);
void freeCompoundStatement(CompoundStatement c);
void freeGrammarList(GrammarList g);
void freeStatement(Statement s);
void freeExpression(Expression e);
void freeIdentifier(Identifier i);

#endif
