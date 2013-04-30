#ifndef __ABSYN_H__
#define __ABSYN_H__

#include <stdio.h>
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

struct expression_ {
  enum {function, unary, postfix, primary, string, cast} type;
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
    enum{none = 0, postincr, postdecr, bracket, identifier, arg} postfix;
    enum{unary_none, preincr, predecr, positive = '+', negative = '-', negate = '!', clone = '*'} unary;
    enum{cast_none, typed} cast;
  } deriv;
};

struct identifier_ {
  char *symbol;
};
struct declarator_ {
  Identifier name;
  GrammarList p; //A list of parameters
};
struct statement_ {
  enum {expression} type;
  union {
    Expression e;
  } sub;
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
  enum {argument, statement} type;
  GrammarNode head;
};
struct grammarNode_ {
  GrammarNode next;
  void *data;
};

void addFront(GrammarList g, void *data);
TranslationUnit getTranslationUnit(FunctionDefinition fd);
FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs);
Declarator declaratorId(Identifier id);
Declarator getDeclarator(Identifier id, GrammarList pList);
CompoundStatement newCompoundStatement(GrammarList sList);
GrammarList newStatementList(Statement s);
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
Expression getUnaryExpression(Expression e);
Expression getUnaryIncr(Expression e);
Expression getUnaryDecr(Expression e);
Expression getUnarySingleOp(char c, Expression e);
Expression getCastExpression(Expression e);
Expression getTypedCast(int token, Expression e);
void freeTranslationUnit(TranslationUnit t); 
void freeFunctionDefinition(FunctionDefinition f);
void freeDeclarator(Declarator d);
void freeCompoundStatement(CompoundStatement c);
void freeGrammarList(GrammarList g);
void freeStatement(Statement s);
void freeExpression(Expression e);
void freeIdentifier(Identifier i);
#endif
