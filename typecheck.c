#include "typecheck.h"

void translationUnitTypeCheck(TranslationUnit t) {

}

void functionDefinitionTypeCheck(FunctionDefinition f) {

}

void declaratorTypeCheck(Declarator d) {

}

void compoundStatementTypeCheck(CompoundStatement cs) {

}

void expressionListTypeCheck(GrammarList g) {

}

void statementListTypeCheck(GrammarList g) {

}

void parameterListTypeCheck(GrammarList g) {

}

void forStatementTypeCheck(Statement s) {

}

void whileStatementTypeCheck(Statement s) {

}

void ifStatementTypeCheck(Statement s) {

}

void ifelseStatementTypeCheck(Statement s) {

}

void dictlistTypeCheck(Statement s) {

}

void dictDefinitionsTypeCheck(Statement s) {

}

void dictTypeCheck(Statement s) {

}

void nodeCreationTypeCheck(Statement s) {

}

void nodeAssignmentTypeCheck(Statement s) {

}

void nodeDictionaryTypeCheck(Statement s) {

}

void edgeCreationTypeCheck(Statement s) {

}

void edgeStatementTypeCheck(Statement s) {

}

void statementTypeCheck(Statement s) {

}

void parameterTypeCheck(Parameter p) {

}

void passupExpressionType(Expression e) {

}

void postfixIdentifierTypeCheck(Expression e) {

}

void postfixDecrementTypeCheck(Expression e) {

}

void postfixIncrementTypeCheck(Expression e) {

}

void postfixArgumentTypeCheck(Expression e) {

}

void postfixBracketTypeCheck(Expression e) {

}

void unaryExpressionTypeCheck(Expression e) {

}

void castTypedExpressionTypeCheck(Expression e) {

}

void multExpressionTypeCheck(Expression e) {

}

void addExpressionTypeCheck(Expression e) {

}

void relatExpressionTypeCheck(Expression e) {

}

void eqExpressionTypeCheck(Expression e) {

}

void condExpressionTypeCheck(Expression e) {

}

void assignmentInitExpressionTypeCheck(Expression e) {

}

void edgeExpressionTypeCheck(Expression e) {

}

void assignmentExpressionTypeCheck(Expression e) {

}

void primaryExpressionTypeCheck(Expression e) {
  switch(e->deriv.primary) {
  case primary_identifier:
    if(e->sub1.i->tt)
      e->tt = e->sub1.i->tt;
    else {
      fprintf(stderr, "Undeclared variable used.\n");
      exit(1);
    }
    break;
  default:
    //do other things
    break;
  }
}

void functionExpressionTypeCheck(Expression e) {

}

void twoExpressionTypeCheck(Expression e) {

}

void identifierTypeCheck(Identifier i) {
  i->tt = findSymbol(i->s, i->symbol);
}

void expressionStatementTypeCheck(Statement s){

}

TypeCheckType copyTypeCheckType(TypeCheckType tt) {
  if(tt==NULL)
  {
    return NULL;
  }
  TypeCheckType ret= (TypeCheckType)malloc(sizeof(struct typeCheckType_));
  ret->base = tt->base;
  ret->fn_sub = copyTypeCheckType(tt->fn_sub);
  ret->ar_sub = copyTypeCheckType(tt->ar_sub);
  return ret;
}

TypeCheckType getTypeCheckType(int type) {
  TypeCheckType ret = (TypeCheckType)malloc(sizeof(struct typeCheckType_));
  ret->base = type;
  return ret;
}

int exactTypeMatch(TypeCheckType t1, TypeCheckType t2) {
  if(t1 == NULL && t2 == NULL)
    return 1;
  else if(t1 == NULL || t2 == NULL)
    return 0;
  else if(t1->base == indeterminable || t2->base == indeterminable)
    return -1;
  else {
    int basematch = (t1->base == t2->base);
    int fnmatch = exactTypeMatch(t1->fn_sub, t2->fn_sub);
    int armatch = exactTypeMatch(t1->ar_sub, t2->ar_sub);
    if(basematch && fnmatch && armatch) {
      if(basematch < 0 || fnmatch < 0 || armatch < 0)
        return -1;
      else
        return 1;
    }
    else
      return 0;
  }
}

int castTypeMatch(TypeCheckType t1, TypeCheckType t2) {
  return 0;
}
