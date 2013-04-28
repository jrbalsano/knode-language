#include "absyn.h"
#include <stdlib.h>

TranslationUnit getTranslationUnit(FunctionDefinition fd) {
  TranslationUnit ret = (TranslationUnit)malloc(sizeof(struct translationUnit_));
  ret->f = fd;
  return ret;
}

FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs) {
  FunctionDefinition ret = (FunctionDefinition)malloc(sizeof(struct functionDefinition_));
  ret->d = d;
  ret->cs = cs;
  return ret;
}

Declarator declaratorId(Identifier id) {
  Declarator d = (Declarator)malloc(sizeof(struct declarator_));
  d->name = id;
  return d;
}

Declarator getDeclarator(Identifier id, GrammarList pList) {
  Declarator d = (Declarator)malloc(sizeof(struct declarator_));
  d->name = id;
  d->p = pList;
  return d;
}


CompoundStatement newCompoundStatement(GrammarList sList) {
  CompoundStatement ret = (CompoundStatement)malloc(sizeof(struct compoundStatement_));
  ret->sList = sList;
  return ret;
}

GrammarList newStatementList(Statement s) {
  GrammarList sList = (GrammarList)malloc(sizeof(struct grammarList_));
  sList->head = 0;
  addFront(sList, s);
  return sList;
}

Statement getExpressionStatement(Expression e) {
  Statement s = (Statement)malloc(sizeof(struct statement_));
  s->type = expression;
  s->sub.e = e;
  return s;
}

Expression getFunctionExpression(Identifier id, GrammarList argExpList) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = function;
  ret->val.i = id;
  ret->sub1.l = argExpList;
  return ret;
}

Expression getPrimaryIdentifierExpression(Identifier id){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = primary;
  ret->val.i = id;
  return ret;
}

Expression getPrimaryStringExpression(char *s) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = string;
  ret->val.s = s;
  return ret;
}

GrammarList newArgumentExpressionList(Expression e) {
  GrammarList aeList = (GrammarList)malloc(sizeof(struct grammarList_));
  aeList->head = 0;
  addFront(aeList, e);
  return aeList;
}

Identifier getIdentifier(char *s) {
  Identifier i = (Identifier)malloc(sizeof(struct identifier_));
  i->symbol = s;
  return i;
}

Expression getPostfixExpression(Expression e1){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = postfix;
  return ret;
}

Expression getPostfixBracketExpression(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = postfix;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getPostfixArgumentExpression(Expression e1, GrammarList argList){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = postfix;
  ret->sub1.e = e1;
  ret->sub2.l = argList;
  return ret;

}

Expression getPostfixIncr(Expression e){
  e->operator = increment;
  return e;
}


Expression getPostfixDecr(Expression e){
  e->operator = decrement;
  return e;
}

Expression getPostfixIdentifierExpression(Expression e, Identifier id){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = postfix;
  ret->sub1.e = e;
  ret->sub2.i = id;
  return ret;
}

Expression getUnaryExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = unary;
  return ret;
}

Expression getUnaryIncr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = unary;
  ret->operator = increment;
  return ret;
}

Expression getUnaryDecr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = unary;
  ret->operator = decrement;
  return ret;
}

void addFront(GrammarList g, void *data) {
  GrammarNode n = (GrammarNode)malloc(sizeof(struct grammarNode_));
  n->data = data;
  n->next = g->head;
  g->head = n;
}

