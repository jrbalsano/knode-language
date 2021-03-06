#include "absyn.h"
#include "yacc.tab.h"
#include <stdlib.h>

/*******************
 * Translation Units
 *******************/

/**
 * Create Translation Unit from an existing FunctionDefinition
 */
TranslationUnit getTranslationUnit(FunctionDefinition fd) {
  TranslationUnit ret = (TranslationUnit)malloc(sizeof(struct translationUnit_));
  ret->s = NULL;
  ret->code = NULL;
  ret->f = fd;
  ret->t = NULL;
  return ret;
}
TranslationUnit getMultFuncDefTranslationUnit(TranslationUnit t, FunctionDefinition fd) {
  TranslationUnit ret = (TranslationUnit)malloc(sizeof(struct translationUnit_));
  ret->s = NULL;
  ret->code = NULL;
  ret->f = fd;
  ret->t = t;
  return ret;
}

/**
 * Recursively free the translation unit and its children.
 */
void freeTranslationUnit(TranslationUnit t) {
#ifdef MEMTRACE
  printf("Freeing translation unit\n");
#endif

  if(t == NULL) {
    fprintf(stderr, "Null child TranslationUnit\n");
    return;
  }

  if (t->t) {
    freeTranslationUnit(t->t);
  }
  else {
    if(t->s->postcode)
      free(t->s->postcode);
    free(t->s);
  }

  if (t->f) {
    freeFunctionDefinition(t->f);
  }
  if(t->code)
    free(t->code);
  free(t);
#ifdef MEMTRACE
  printf("Translation unit freed\n");
#endif

}

/*********************
 * Function Definition 
 *********************/

/**
 * Create FunctionDefinition from its Declaration and the statements that comprise
 * the function.
 */
FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs) {
  FunctionDefinition ret = (FunctionDefinition)malloc(sizeof(struct functionDefinition_));
  ret->s = NULL;
  ret->tt = NULL;
  ret->code = NULL;
  ret->type_name = none;
  ret->d = d;
  ret->cs = cs;
  return ret;
}

/**
 * Create a new function definition with a specified type
 */
FunctionDefinition getRetTypeFunctionDefinition(int type, Declarator d, CompoundStatement cs) {
  FunctionDefinition ret = getFunctionDefinition(d, cs);
  ret->s = NULL;
  ret->tt = NULL;
  ret->code = NULL;
  ret->type_name = type;
  return ret;
}
/**
 * Recursively free the function definition and its children.
 */
void freeFunctionDefinition(FunctionDefinition f) {
#ifdef MEMTRACE
  printf("Freeing function definition\n");
#endif
  if(f == NULL) {
    fprintf(stderr, "Null child FunctionDefinition\n");
    return;
  }
  freeDeclarator(f->d);
  freeCompoundStatement(f->cs);
  freeTypeCheckType(f->tt);
  if(f->code)
    free(f->code);
  if(f->s->postcode)
    free(f->s->postcode);
  free(f->s);
  free(f);
#ifdef MEMTRACE
  printf("Function definition freed\n");
#endif
}

/*************
 * Declarators
 *************/

/**
 * Create a declarator from just an identifier. This is used in cases where
 * the function has no parameters, just an identifier
 */
Declarator declaratorId(Identifier id) {
  Declarator d = (Declarator)malloc(sizeof(struct declarator_));
  d->s = NULL;
  d->tt = NULL;
  d->code = NULL;
  d->name = id;
  d->p = NULL;
  return d;
}

/**
 * Create a declarator from an identifier and a parameter list
 */
Declarator getDeclarator(Identifier id, GrammarList pList) {
  Declarator d = (Declarator)malloc(sizeof(struct declarator_));
  d->s = NULL;
  d->tt = NULL;
  d->code = NULL;
  d->name = id;
  d->p = pList;
  return d;
}

/**
 * Recursively free the declarator and its children.
 */
void freeDeclarator(Declarator d) {
#ifdef MEMTRACE
  printf("Freeing declarator\n");
#endif
  if(d == NULL) {
    fprintf(stderr, "Null child Declarator\n");
    return;
  }  
  if(d->p)
    freeGrammarList(d->p);
  freeIdentifier(d->name);
  freeTypeCheckType(d->tt);
  if(d->code)
    free(d->code);
  free(d);
#ifdef MEMTRACE
  printf("Declarator freed\n");
#endif
}

/*********************
 * Compound Statements
 *********************/

/**
 * Create a new compound statement by initializing a new statement list.
 */
CompoundStatement newCompoundStatement(GrammarList sList) {
  CompoundStatement ret = (CompoundStatement)malloc(sizeof(struct compoundStatement_));
  ret->s = NULL;
  ret->main = 0;
  ret->type = none;
  ret->code = NULL;
  ret->tt = NULL;
  ret->sList = sList;
  return ret;
}

/**
 * Recursively free the compound statement and its children in postorder.
 */
void freeCompoundStatement(CompoundStatement c) {
#ifdef MEMTRACE
  printf("Freeing compound statement\n");
#endif
  if(c == NULL) {
    fprintf(stderr, "Null child CompoundStatement\n");
    return;
  }
  freeGrammarList(c->sList);
  freeTypeCheckType(c->tt);
  if(c->code)
    free(c->code);
  free(c);
#ifdef MEMTRACE
  printf("Compound statement freed\n");
#endif
}
/*****************
 * Grammar Lists
 *****************/

/**
 * Create a new statement list from an existing statement. To be used in situations where
 * a statement list does not already exist.
 */
GrammarList newStatementList(Statement s) {
  GrammarList sList = (GrammarList)malloc(sizeof(struct grammarList_));
  sList->precode = NULL;
  sList->postcode = NULL;
  sList->s = NULL;
  sList->code = NULL;
  sList->tt = NULL;
  sList->type = statement;
  sList->head = 0;
  sList->tail = 0;
  addBack(sList, s);
  return sList;
}

/**
 * Adds a new statement to the front of the statementlist
 */
GrammarList extendStatementList(GrammarList sList, Statement s) {
  addBack(sList, s);
  return sList;
}

/**
 * Creates a new parameter list from an existing parameter. To be used in sutations
 * where a parameter list does not already exist. See addBack for cases where the
 * list already exists.
 */
GrammarList newParameterList(Parameter p) {
  GrammarList pList = (GrammarList)malloc(sizeof(struct grammarList_));
  pList->precode = NULL;
  pList->postcode = NULL;
  pList->s = NULL;
  pList->code = NULL;
  pList->tt = NULL;
  pList->type = parameterList;
  pList->head = 0;
  pList->tail = 0;
  addBack(pList, p);
  return pList;
}

/**
 * Creates a new argument expression list from an existing expression. To be used in
 * situations where the argument expression list does not already exist.
 */
GrammarList newArgumentExpressionList(Expression e) {
  GrammarList aeList = (GrammarList)malloc(sizeof(struct grammarList_));
  aeList->precode = NULL;
  aeList->postcode = NULL;
  aeList->s = NULL;
  aeList->code = NULL;
  aeList->tt = NULL;
  aeList->type = argument;
  aeList->head = 0;
  aeList->tail = 0;
  addBack(aeList, e);
  return aeList;
}
/**
 * Creates a new argument expression list from an existing expression. To be used in
 * situations where the argument expression list does not already exist.
 */
GrammarList newExpressionList(Expression e) {
  GrammarList eList = (GrammarList)malloc(sizeof(struct grammarList_));
  eList->precode = NULL;
  eList->postcode = NULL;
  eList->s = NULL;
  eList->code = NULL;
  eList->tt = NULL;
  eList->type = expressionList;
  eList->head = 0;
  eList->tail = 0;
  addBack(eList, e);
  return eList;
}
/**
 * Add a node to the front of the Grammar List g, with data pointer data
 */
GrammarList addBack(GrammarList g, void *data) {
  GrammarNode n = (GrammarNode)malloc(sizeof(struct grammarNode_));
  n->s = NULL;
  n->data = data;
  n->next = NULL;
  GrammarNode back = g->tail;
  if(!back) 
    g->head = n;
  else 
    g->tail->next = n;
  g->tail = n;
  return g;
}

/**
 * pops the first node off the front of the list and returns the data stored therein.
 */
void *popFront(GrammarList g) {
  if(g->head) {
    GrammarNode n = g->head;
    g->head = n->next;
    void *d = n->data;
    free(n);
    return d;
  }
  else
    return NULL;
}

void freeGrammarList(GrammarList g) {
#ifdef MEMTRACE
  printf("Freeing grammar list\n");
#endif
  if(g == NULL) {
    fprintf(stderr, "Null child GrammarList\n");
    return;
  }  
  while(g->head) {
    void *d = popFront(g);
    switch(g->type) {
      case argument:
        freeExpression((Expression)d);
        break;
      case statement:
        freeStatement((Statement)d);
        break;
      case parameterList:
        freeParameter((Parameter)d);
        break;
      case expressionList:
        freeExpression((Expression)d);
        break;
    }
  }
  freeTypeCheckType(g->tt);
  if(g->code)
    free(g->code);
  if(g->precode)
    free(g->precode);
  if(g->postcode)
    free(g->postcode);
  free(g);
#ifdef MEMTRACE
  printf("Grammar list freed\n");
#endif
}

/************
 * Statements
 ************/

/**
 * Creates a statement from an existing statement
 */
Statement getStatement(Statement s) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = none;
  ret->sub1.s = s;
  return ret;
}

/**
 * Create a new selection if statement.
 */
Statement newIfStatement(Expression e, CompoundStatement cs) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->sub1.e = e;
  ret->type = selection;
  ret->deriv.selection = ifStatement;
  ret->sub2.cs = cs;
  return ret;
}

/**
 * Create a new selection if/else statement.
 */
Statement newIfElseStatement(Expression e, CompoundStatement cs1,CompoundStatement cs2) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->sub1.e = e;
  ret->type = selection;
  ret->deriv.selection = ifelseStatement;
  ret->sub2.cs = cs1;
  ret->sub3.cs = cs2;
  return ret;
}
/**
 * Create a Statement from an existing expression
 */
Statement getExpressionStatement(Expression e) {
  Statement s = (Statement)malloc(sizeof(struct statement_));
  s->code = NULL;
  s->tt = NULL;
  s->type = expression;
  s->sub1.e = e;
  return s;
}
/**
 * Create a new while iteration statement.
 */
Statement newWhileStatement(Expression e, CompoundStatement cs) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = iteration;
  ret->deriv.iteration = whileIter;
  ret->sub1.e = e;
  ret->sub2.cs = cs;
  return ret;
}
/**
 * Create a new for iteration statement.
 */
Statement newForStatement(Expression e1, Expression e2,Expression e3,CompoundStatement cs) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = iteration;
  ret->deriv.iteration = forIter;
  ret->sub1.forloop.e1 = e1;
  ret->sub1.forloop.e2 = e2;
  ret->sub1.forloop.e3 = e3;
  ret->sub2.cs = cs;
  return ret;
}
/**
 * Create a new break statement.
 */
Statement newBreakStatement() {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = breakStatement;
  return ret;
}

/**
 * Create a new, unadorned node declaration statement
 */
Statement newNodeCreateStatement(Identifier id) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = node;
  ret->deriv.node = nodeCreate;
  ret->sub1.i = id;
  return ret;
}

/**
 * Create a new node assignment statement
 */
Statement newNodeAssignmentStatement(Identifier id, Expression e) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = node;
  ret->deriv.node = nodeAssignment;
  ret->sub1.i = id;
  ret->sub2.e = e;
  return ret;
}

/**
 * Create a new dictlist definition
 */
Statement getDictListStatement(Identifier i, Expression e) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = dictlist;
  ret->sub1.i = i;
  ret->sub2.e = e;
  return ret;
}

/**
 * Creates a new Dict without definitions
 */
Statement getDictDecStatement(Identifier i) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = dict;
  ret->deriv.dict = none;
  ret->sub1.i = i;
  return ret;
}
/**
 * Create a new node dict assignment statement
 */
Statement newNodeDictAssignmentStatement(Identifier id, CompoundStatement cs) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = node;
  ret->deriv.node = nodeDictAssignment;
  ret->sub1.i = id;
  ret->sub2.cs = cs;
  return ret;
}

/*
 * Create a new edge statement out of an existing node pair.
 */
Statement getEdgeStatementFromNodes(Identifier i, Expression e1, int edgeconnector, Expression e2) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = edge;
  ret->deriv.edge = edgeconnector;
  ret->sub1.i = i;
  ret->sub2.e = e1;
  ret->sub3.e = e2;
  return ret;
}

/**
 * Creates a new dict with a compound statement containing definitions.
 */
Statement getDictDefStatement(Identifier i, CompoundStatement cs) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = dict;
  ret->deriv.dict = definitions;
  ret->sub1.i = i;
  ret->sub2.cs = cs;
  return ret;
}

/**
 * Create a new edge statement, that only declares that an edge can
 * be stored in a certain identifier.
 */
Statement getEdgeDeclaration(Identifier i) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = edge;
  ret->deriv.edge = none;
  ret->sub1.i = i;
  return ret;
}

Statement getDeclarationStatement(int token, Identifier i){
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->s = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = decl;
  ret->sub1.typnam = token;
  ret->sub2.i = i;
  return ret;
}

/**
 * Recursively free the Statement and its children in postorder.
 */
void freeStatement(Statement s) {
#ifdef MEMTRACE
  printf("Freeing statement\n");
#endif
  if(s == NULL) {
    fprintf(stderr, "Null child Statement\n");
    return;
  }  
  switch(s->type) {
    case expression:
      freeExpression(s->sub1.e);
      break;
    case iteration:
      switch(s->deriv.iteration) {
        case forIter:
          freeExpression(s->sub1.forloop.e1);
          freeExpression(s->sub1.forloop.e2);
          freeExpression(s->sub1.forloop.e3);
          freeCompoundStatement(s->sub2.cs);
          break;
        case whileIter:
          freeExpression(s->sub1.e);
          freeCompoundStatement(s->sub2.cs);
          break;
      }
      break;
    case decl:
      freeIdentifier(s->sub2.i);
      break; 
    case selection:
      switch(s->deriv.selection) {
        case ifStatement:
          freeCompoundStatement(s->sub2.cs);
          freeExpression(s->sub1.e);
          break;
        case ifelseStatement:
          freeExpression(s->sub1.e);
          freeCompoundStatement(s->sub2.cs);
          freeCompoundStatement(s->sub3.cs);
          break;
      }
      break;
    case dictlist:
      freeIdentifier(s->sub1.i);
      freeExpression(s->sub2.e);
      break;
    case dict:
      switch(s->deriv.dict) {
        case definitions:
          freeIdentifier(s->sub1.i);
          freeCompoundStatement(s->sub2.cs);
          break;
        case none:
          freeIdentifier(s->sub1.i);
          break;
      }
      break;
    case node:
      switch(s->deriv.node) {
        case nodeCreate:
          freeIdentifier(s->sub1.i);
          break;
        case nodeAssignment:
          freeIdentifier(s->sub1.i);
          freeExpression(s->sub2.e);
          break;
        case nodeDictAssignment:
          freeIdentifier(s->sub1.i);
          freeCompoundStatement(s->sub2.cs);
          break;
      }
      break;
    case edge:
      switch(s->deriv.edge) {
        case none:
          freeIdentifier(s->sub1.i);
          break;
        default:
          freeIdentifier(s->sub1.i);
          freeExpression(s->sub2.e);
          freeExpression(s->sub3.e);
          break;
      }
      break;
    case none:
      freeStatement(s->sub1.s);
      break;
    default:
      break;
  }
  freeTypeCheckType(s->tt);
  if(s->code)
    free(s->code);
  free(s);
#ifdef MEMTRACE
  printf("Statement freed\n");
#endif
}

/************
 * Parameters
 ************/

/**
 * Create a parameter from a typed argument
 */
Parameter getTypedParameter(int typnam, Identifier i){
  Parameter ret = (Parameter)malloc(sizeof(struct parameter_));
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type=typnam;
  ret->i = i;
  return ret;
}

/**
 * Free the Parameter.
 */
void freeParameter(Parameter p) {
  freeIdentifier(p->i);
  freeTypeCheckType(p->tt);
  if(p->code)
    free(p->code);
  free(p);
}

/*************
 * Expressions
 *************/

/**
 * Create a new expression from a function call defined by the functions id
 * and the list of arguments
 */
Expression getFunctionExpression(Identifier id, GrammarList argExpList) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = function;
  ret->sub1.i = id;
  ret->sub2.l = argExpList;
  return ret;
}

/**
 * Creates a new primary expression from an existing identifier
 */
Expression getPrimaryIdentifierExpression(Identifier id){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = primary;
  ret->deriv.primary = primary_identifier;
  ret->sub1.i = id;
  return ret;
}

/**
 * Creates a new primary expression from an existing string
 */
Expression getPrimaryStringExpression(char *s) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = primary;
  ret->sub1.s = (char *)malloc(strlen(s)+1);
  strcpy(ret->sub1.s, s);
  ret->deriv.primary = primary_string;
  return ret;
}

Expression getPrimaryIntegerExpression(int ivalue){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = primary;
  ret->sub1.ival = ivalue;  
  ret->deriv.primary = primary_int;
  return ret;

}
Expression getPrimaryDoubleExpression(double dvalue){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = primary;
  ret->sub1.dval = dvalue;  
  ret->deriv.primary = primary_double;
  return ret;

}

Expression getPrimaryBoolExpression(int bvalue){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = primary;
  ret->sub1.boolval = bvalue;  
  ret->deriv.primary = primary_bool;
  return ret;

}


/**Get parenthesized primary expression*/
Expression getPrimaryParenExpression(Expression e) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = primary;
  ret->deriv.primary = parentheses;
  ret->sub1.e = e;
  return ret;
}
/**
 * Creates a new Postfix Expression from an existing expression
 */
Expression getPostfixExpression(Expression e1){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->deriv.postfix = none;
  ret->sub1.e = e1;
  ret->type = postfix;
  return ret;
}

/**
 * Creates a new Postfix Expression with an empty argument
 */
Expression getPostfixEmptyArgument(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = postfix;
  ret->sub1.e = e;
  ret->sub2.l = NULL;
  ret->deriv.postfix = argEmpty;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing expression followed
 * by square brackets encompassing a second expression
 */
Expression getPostfixBracketExpression(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = postfix;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  ret->deriv.postfix = bracket;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing argument list and an
 * existing expression
 */
Expression getPostfixArgumentExpression(Expression e1, GrammarList argList){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = postfix;
  ret->sub1.e = e1;
  ret->sub2.l = argList;
  ret->deriv.postfix = arg;
  return ret;

}

/**
 * Creates a new Postfix Expression from an existing expression and specifies
 * it as an incremement expression
 */
Expression getPostfixIncr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = postfix;
  ret->deriv.postfix = postincr;
  ret->sub1.e = e;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing expression and specifies
 * it as an increment expression
 */
Expression getPostfixDecr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type=postfix;
  ret->deriv.postfix = postdecr;
  ret->sub1.e = e;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing expression and its
 * identifier. This is to be used when accessing the properties of some
 * expression using a expression.identifier construct.
 */
Expression getPostfixIdentifierExpression(Expression e, Identifier id){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = postfix;
  ret->sub1.e = e;
  ret->sub2.i = id;
  ret->deriv.postfix = identifier;
  return ret;
}

Expression getUnaryExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = unary;
  ret->deriv.unary = none;
  ret->sub1.e = e;
  return ret;
}

Expression getUnaryIncr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = unary;
  ret->sub1.e = e;
  ret->deriv.unary = preincr;
  return ret;
}

Expression getUnarySingleOp(char op, Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = unary;
  ret->sub1.e = e;
  ret->deriv.unary = op;
  return ret;
}

Expression getUnaryDecr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = unary;
  ret->deriv.unary = predecr;
  ret->sub1.e = e;
  return ret;
}

Expression getCastExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->type = cast;
  ret->code = NULL;
  ret->tt = NULL;
  ret->deriv.cast = none;
  ret->sub1.e = e;
  return ret;
}

Expression getTypedCast(int token, Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = cast;
  ret->deriv.cast = typed;
  ret->sub1.typnam = token;
  ret->sub2.e = e;
  return ret;
}

Expression getMultExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = mult;
  ret->deriv.mult = none;
  ret->sub1.e = e;
  return ret;
}

Expression getMultiplyExpression(Expression e1, char c, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = mult;
  ret->deriv.mult = c;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getAdditiveExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = add;
  ret->deriv.add = none;
  ret->sub1.e = e;
  return ret;
}

Expression getAddExpression(Expression e1, char c, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = add;
  ret->deriv.add = c;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getRelatExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = relat;
  ret->deriv.relat = none;
  ret->sub1.e = e;
  return ret;
}

Expression getSingleCharRelat(Expression e1, char c, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = relat;
  ret->deriv.relat = c;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getLeRelat(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = relat;
  ret->deriv.relat = le;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getGeRelat(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = relat;
  ret->deriv.relat = ge;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getEqExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = eq;
  ret->deriv.eq = none;
  ret->sub1.e = e;
  return ret;
}

Expression getEqual(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = eq;
  ret->deriv.relat = equal;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getNotEqual(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = eq;
  ret->deriv.relat = notequal;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getAndExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = cond;
  ret->deriv.cond = none;
  ret->sub1.e = e;
  return ret;
}

Expression getAnd(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = cond;
  ret->deriv.cond = cond_and;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}
Expression getOrExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = cond;
  ret->deriv.cond = none;
  ret->sub1.e = e;
  return ret;
}

Expression getOr(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = cond;
  ret->deriv.cond = cond_or;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}
Expression getCond(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = cond;
  ret->deriv.cond = none;
  ret->sub1.e = e;
  return ret;
}

Expression getAssign(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = assignment;
  ret->deriv.assign = none;
  ret->sub1.e = e;
  return ret;
}

Expression getTokenizedAssignment(Expression e1, int op, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = assignment;
  ret->deriv.assign = op;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getAssignment(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = assignment;
  ret->deriv.assign = eq_assign;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getInit(int token, Identifier i, Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->deriv.assign = init;
  ret->type = assignment;
  ret->sub1.typnam = token;
  ret->sub2.i = i;
  ret->sub3.e = e;
  return ret;
}

/**
 * Creates a new assignment expression from an edge connector expression
 * This would in reality be an array of edges being returned.
 */
Expression getAssignEdgeExpression(Expression e1, int edgeconnector, Expression e2) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = assignment;
  ret->deriv.assign = edgeconnector;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}
/**
 * Creates a new expression from an existing assignment expression
 */
Expression getExpression(Expression e) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = none;
  ret->deriv.none = none;
  ret->sub1.e = e;
  return ret;
}

/**
 * Creates a new expression from an existing expression and an existing
 * assignment expression.
 */
Expression getExpressionAssignmentExpression(Expression e1, Expression e2) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->precode = NULL;
  ret->postcode = NULL;
  ret->s = NULL;
  ret->code = NULL;
  ret->tt = NULL;
  ret->type = none;
  ret->deriv.none = comma;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

/**
 * Recursively free an expression and its children in postorder
 */
void freeExpression(Expression e) {
#ifdef MEMTRACE
  printf("Freeing expression\n");
#endif
  if(e == NULL) {
    fprintf(stderr, "Null child Expression\n");
    return;
  }
  switch (e->type) { 
    case postfix:
      switch (e->deriv.postfix) {
        case identifier:
          freeIdentifier(e->sub2.i);
          freeExpression(e->sub1.e);
          break;
        case postdecr:
          freeExpression(e->sub1.e);
          break;
        case postincr:
          freeExpression(e->sub1.e);
          break;
        case arg:
          freeExpression(e->sub1.e);
          freeGrammarList(e->sub2.l);
          break;
        case argEmpty:
          freeExpression(e->sub1.e);
          break;
        case bracket:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
        case 0:
          freeExpression(e->sub1.e);
          break;
      }
      break;
    case unary:
      freeExpression(e->sub1.e);
      break;
    case cast:
      switch(e->deriv.cast){
        case typed:
          freeExpression(e->sub2.e);
          break;
        case 0:
          freeExpression(e->sub1.e);
          break;
      }
      break;

    case mult:
      switch(e->deriv.mult){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case add:
      switch(e->deriv.add){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case relat:
      switch(e->deriv.relat){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case eq:
      switch(e->deriv.eq){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case cond:
      switch(e->deriv.eq){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case assignment:
      switch(e->deriv.assign){
        case init:
          freeIdentifier(e->sub2.i);
          freeExpression(e->sub3.e);
          break;
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      } 
      break;
    case primary:
      switch(e->deriv.primary){
        case primary_string:
          free(e->sub1.s);
          break;
        case primary_identifier:
          freeIdentifier(e->sub1.i);
          break;
        case parentheses:
          freeExpression(e->sub1.e);
          break;
        default: //suppresses warnings about primary_none
          break;
      }
      break;
    case function:
      freeIdentifier(e->sub1.i);
      freeGrammarList(e->sub2.l);
      break;
    case none:
      if(!e->deriv.none) 
        freeExpression(e->sub1.e);
      else if(e->deriv.none == comma) {
        freeExpression(e->sub1.e);
        freeExpression(e->sub2.e);
      }
      break;
    default:
      break;
  }
  freeTypeCheckType(e->tt);
  if(e->code)
    free(e->code);
  if(e->precode)
    free(e->precode);
  if(e->postcode)
    free(e->postcode);
  free(e);
#ifdef MEMTRACE
  printf("Expression freed\n");
#endif
}


/*************
 * Identifiers
 *************/

/**
 * Create an identifier from a string
 */
Identifier getIdentifier(char *s) {
  Identifier i = (Identifier)malloc(sizeof(struct identifier_));
  i->s = NULL;
  i->tt = NULL;
  i->code = NULL;
  strncpy(i->symbol, s, sizeof(i->symbol));
  return i;
}

/**
 * free an identifier and its children
 */
void freeIdentifier(Identifier i) {
#ifdef MEMTRACE
  printf("Freeing identifier\n");
#endif
  if(i == NULL) {
    fprintf(stderr, "Null child Identifier\n");
    return;
  }  
  freeTypeCheckType(i->tt);
  if(i->code)
    free(i->code);
  free(i);
#ifdef MEMTRACE
  printf("Identifier freed\n");
#endif
}

/****************
 * TypeCheckTypes
 ****************/
void freeTypeCheckType(TypeCheckType t) {
#ifdef MEMTRACE
  printf("Freeing TypeCheckType\n");
#endif
  if(t == NULL) {
    return;
  }  
  freeTypeCheckType(t->ar_sub);
  freeTypeCheckType(t->fn_sub);
  free(t);
#ifdef MEMTRACE
  printf("TypeCheckType freed\n");
#endif
}
