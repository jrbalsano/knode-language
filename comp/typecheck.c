#include "typecheck.h"

void translationUnitTypeCheck(TranslationUnit t) {

}

void functionDefinitionTypeCheck(FunctionDefinition f) {
  TypeCheckType tt = NULL;
  TypeCheckType hold;
  if(f->type_name == none) {
    tt = getTypeCheckType(void_);
    tt->fn_sub = copyTypeCheckType(f->d->tt);
  }
  else {
    tt = getTTFromType(f->type_name);
    tt->fn_sub = copyTypeCheckType(f->d->tt);
  }
  hold = tt;
  tt = addSymbolToScope(f->s->parent, f->d->name->symbol, tt);
  if(!tt) {
    fprintf(stderr, "Error: Multiple definitions exist for function `%s`\n", f->d->name->symbol);
    free(hold);
    exit(1);
  }
  f->tt = tt;
  f->cs->tt = copyTypeCheckType(tt);
  if(!strcmp("main", f->d->name->symbol))
    f->cs->main = 1;
}

void declaratorTypeCheck(Declarator d) {
  if(d->p)
    d->tt = copyTypeCheckType(d->p->tt);
  else
    d->tt = NULL;
}

void compoundStatementTypeCheck(CompoundStatement cs) {

}

void expressionListTypeCheck(GrammarList g) {

}

void statementListTypeCheck(GrammarList g) {

}

void parameterListTypeCheck(GrammarList g) {
  GrammarNode cur = g->head;
  TypeCheckType last = NULL;
  while(cur) {
    Parameter p = (Parameter)cur->data;
    if(g->tt) {
      last->fn_sub = copyTypeCheckType(p->tt);
      last = last->fn_sub;
    }
    else {
      g->tt = copyTypeCheckType(p->tt);
      last = g->tt;
    }
    cur = cur->next;
  }
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
    printf("NodeCreation");
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
    printf("NodeDictionary");
    free(hold);
    exit(1);
  }
}

void edgeCreationTypeCheck(Statement s) {
  TypeCheckType tt = NULL;
  TypeCheckType hold;
  tt = getTypeCheckType(edge_);
  hold = tt;
  tt = addSymbolToScope(s->s, s->sub1.i->symbol, tt);

  if (!tt){
    fprintf(stderr, "Error: Declaration of already declared variable `%s`\n", s->sub2.i->symbol);
    free(hold);
    exit(1);
  } 
}

void edgeStatementTypeCheck(Statement s) {
  TypeCheckType tt = NULL;
  TypeCheckType hold;
  tt = getTypeCheckType(edge_);
  hold = tt;
  tt = addSymbolToScope(s->s, s->sub1.i->symbol, tt);

  if (!tt){
    fprintf(stderr, "Error: Declaration of already declared variable `%s`\n", s->sub2.i->symbol);
    free(hold);
    exit(1);
  } 

}

void statementTypeCheck(Statement s) {

}

void expressionStatementTypeCheck(Statement s){

}

void declStatementTypeCheck(Statement s) {
  TypeCheckType tt = NULL;
  TypeCheckType hold;
  tt = getTTFromType(s->sub1.typnam);
  hold = tt;
  tt = addSymbolToScope(s->s, s->sub2.i->symbol, tt);
  if(!tt) {
    fprintf(stderr, "Error: Declaration of already declared variable `%s`\n", s->sub2.i->symbol);
    printf("declStatement");
    free(hold);
    exit(1);
  }
}

void parameterTypeCheck(Parameter p) {
  TypeCheckType tt;
  p->tt = getTTFromType(p->type);
  addSymbolToScope(p->s, p->i->symbol, tt);
}

void passupExpressionType(Expression e) {
  e->tt = copyTypeCheckType(e->sub1.e->tt);
}

void postfixIdentifierTypeCheck(Expression e) {
  if(e->sub1.e->tt->base == edge_)
    e->tt = getTypeCheckType(string_);
  if(e->sub1.e->tt->base == node_)
    e->tt = getTypeCheckType(string_);
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
  e->tt = copyTypeCheckType(e->sub1.e->tt);
}

void castTypedExpressionTypeCheck(Expression e) {

}

void multExpressionTypeCheck(Expression e) {
  int int1 = e->sub1.e->tt->base == int_;
  int double1 = e->sub1.e->tt->base == double_;
  int int2 = e->sub2.e->tt->base == int_;
  int double2 = e->sub2.e->tt->base == double_;
  if (int1 && int2){
    e->tt = getTypeCheckType(int_);
  }

  else if ((double1 && double2) || (int1 && double2) || (double1 && int2)){
    e->tt = getTypeCheckType(double_);
  }
  else{
    fprintf(stderr, "TYPE CHECK ERROR: additive expression"); 
    exit(1);
  }
}

void addExpressionTypeCheck(Expression e) {
  int int1 = e->sub1.e->tt->base == int_;
  int double1 = e->sub1.e->tt->base == double_;
  int int2 = e->sub2.e->tt->base == int_;
  int double2 = e->sub2.e->tt->base == double_;
  int string1 = e->sub1.e->tt->base == string_;
  int string2 = e->sub2.e->tt->base == string_;

  if (int1 && int2){
    e->tt = getTypeCheckType(int_);
  }

  else if ((double1 && double2) || (int1 && double2) || (double1 && int2)){
    e->tt = getTypeCheckType(double_);
  }
 
  else if ((string1 && string2) || (int1 && string2) || (double1 && string2) || (string1 && int2) || (string1 && double2)){
    e->tt = getTypeCheckType(string_);
  }

  else{
    fprintf(stderr, "TYPE CHECK ERROR: additive expression"); 
    exit(1);
  }
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
  e->tt = copyTypeCheckType(e->sub1.e->tt);
}

void primaryExpressionTypeCheck(Expression e) {
  switch(e->deriv.primary) {
    case primary_identifier:
      e->tt = copyTypeCheckType(findSymbol(e->sub1.i->s, e->sub1.i->symbol));
      if(!e->tt) {
        fprintf(stderr, "Undeclared variable used `%s`.\n", e->sub1.i->symbol);
        exit(1);
      }
      break;
    case primary_string:
      e->tt = getTypeCheckType(string_);
        break;
    case primary_int:
      e->tt = getTypeCheckType(int_);
      break;
    case primary_bool:
      e->tt = getTypeCheckType(boolean_);
      break;
    case primary_double:
      e->tt = getTypeCheckType(double_);
      break;
    case parentheses:
      e->tt = copyTypeCheckType(e->sub1.e->tt);
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
  TypeCheckType ret = (TypeCheckType)malloc(sizeof(struct typeCheckType_));
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

TypeCheckType getTTFromType(int typename) {
  TypeCheckType tt;
  switch(typename) {
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
      printf("Unknown type %d\n", typename);
      break;
  }
  return tt;
}
