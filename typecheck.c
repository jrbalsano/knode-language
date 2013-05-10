#include "typecheck.h"

void translationUnitTypeCheck(TranslationUnit t) {

}

void functionDefinitionTypeCheck(FunctionDefinition f) {
  TypeCheckType tt = NULL;
  TypeCheckType hold;
  tt = copyTypeCheckType(f->d->tt);
  hold = tt;
  tt = addSymbolToScope(f->s, f->d->name->symbol, tt);
  if(!tt) {
    fprintf(stderr, "Error: Declaration of already declared variable `%s`\n", f->d->name->symbol);
    free(hold);
    exit(1);
  }
}

void declaratorTypeCheck(Declarator d) {
  //TODO: Fully implement this. Currently hacky
  d->tt = getTypeCheckType(function_);
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
  TypeCheckType tt = NULL;
  TypeCheckType hold;
  tt = getTypeCheckType(node_);
  hold = tt;
  tt = addSymbolToScope(s->s, s->sub1.i->symbol, tt);
  if(!tt) {
    fprintf(stderr, "Error: Declaration of already declared variable `%s`\n", s->sub2.i->symbol);
    free(hold);
    exit(1);
  }
}

void nodeAssignmentTypeCheck(Statement s) {

}

void nodeDictionaryTypeCheck(Statement s) {
  TypeCheckType tt = NULL;
  TypeCheckType hold;
  tt = getTypeCheckType(node_);
  hold = tt;
  tt = addSymbolToScope(s->s, s->sub1.i->symbol, tt);
  if(!tt) {
    fprintf(stderr, "Error: Declaration of already declared variable `%s`\n", s->sub2.i->symbol);
    free(hold);
    exit(1);
  }
}

void edgeCreationTypeCheck(Statement s) {

}

void edgeStatementTypeCheck(Statement s) {

}

void statementTypeCheck(Statement s) {

}

void expressionStatementTypeCheck(Statement s){

}

void declStatementTypeCheck(Statement s) {
  TypeCheckType tt = NULL;
  TypeCheckType hold;
  switch(s->sub1.typnam) {
    case INT:
      tt = getTypeCheckType(int_);
      break;
    case DOUBLE:
      tt = getTypeCheckType(double_);
      break;
    case CHAR:
      tt = getTypeCheckType(char_);
      break;
    case BOOLEAN:
      tt = getTypeCheckType(boolean_);
      break;
    case STRING:
      tt = getTypeCheckType(string_);
      break;
    case NODE:
      tt = getTypeCheckType(node_);
      break;
    case DICT:
      tt = getTypeCheckType(dict_);
      break;
    case EDGE:
      tt = getTypeCheckType(edge_);
      break;
    default:
      printf("Unknown token %d\n", s->sub1.typnam);
      break;
  }
  hold = tt;
  tt = addSymbolToScope(s->s, s->sub2.i->symbol, tt);
  if(!tt) {
    fprintf(stderr, "Error: Declaration of already declared variable `%s`\n", s->sub2.i->symbol);
    free(hold);
    exit(1);
  }
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
      e->tt = findSymbol(e->sub1.i->s, e->sub1.i->symbol);
      if(!e->tt) {
        fprintf(stderr, "Undeclared variable used `%s`.\n", e->sub1.i->symbol);
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
  // I'm pretty sure we don't need this method
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
  ret->fn_sub = NULL;
  ret->ar_sub = NULL;
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
  if(t1 == NULL && t2 == NULL)
    return 1;
  else if(t1 == NULL || t2 == NULL)
    return 0;
  else if(t1->base == indeterminable || t2->base == indeterminable)
    return -1;
  else if(t1->base == t2->base)
    return 1;
  else {
    int intToDub = (t2->base == int_ && t1->base == double_);
    int intToString = (t2->base == int_ && t1->base == string_);
    int dubToString = (t2->base == double_ && t1->base == string_);
    if(intToDub || intToString || dubToString)
      return 2;
    else
      return 0;
  }
}