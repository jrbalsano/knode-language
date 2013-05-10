#include "codegen.h"

void translationUnitGenerateCode(TranslationUnit t) {

  t->code = getAllocatedString(t->f->code);
  //does not deal with case where t also has a translation unit
  printf("translationUnit code: %s\n", t->code);
}
void functionDefinitionGenerateCode(FunctionDefinition f) {

/*NOTE: I have no idea why, but I get tons of errors when this switch statement is uncommented out... halp?!*/

//  switch(f->type_name)
//  {
//    case 0:
      Declarator dec = f->d;
      char *c = dec->code;
//      printf("dec->code %s\n", dec->code);
      char *c1 = f->cs->code;
//      printf("f->cs->code %s\n", f->cs->code);
      int length = strlen(c)+strlen(c1)+1;
      char result[length];
      strncpy(result, c, length);
      strncat(result, c1, length);
      f->code = getAllocatedString(result);
//      break;
//    default: 
//      break;//will need to be filled in for all types
//  }

}

void declaratorGenerateCode(Declarator d) {
  if(!d->p) {
    char *c = d->name->code;
    char *c2 = "()\n";
    int length = strlen(c) + strlen(c2) + 1;
    char result[length];
    strncpy(result, c, length);
    strncat(result, c2, length);
    d->code = getAllocatedString(result);
  }
  //TODO: deal with d->p case (The case where the function has a parameter list)
}

void compoundStatementGenerateCode(CompoundStatement cs) {

  char *c1 = cs->sList->code;
  char *c2 = "{\n";
  char *c3 = "}\n";
  int length = strlen(c1)+strlen(c2)+strlen(c3)+1;
  char result[length];
  strncpy(result, c2, length);
  strcat(result, c1);
  strcat(result, c3);
  cs->code = getAllocatedString(result);

}

void expressionListGenerateCode(GrammarList g) {
  int buffer = 1024;
  char *str = malloc(sizeof(char)*buffer);
  GrammarNode current = g->head;
  int i = 0;
  while (current)
  {
    char *c = ((Expression)current->data)->code;
    int newlength;
    if(i)
      newlength = strlen(str) + strlen(c) + 3;
    else
      newlength = strlen(c) + 1;
    while (newlength>buffer) {
      buffer *= 2;
      char *old = str;
      str = malloc(sizeof(char)*buffer);
      strcpy(str, old);
      free(old);
    }

    if (i == 0)
      strncpy(str, c, buffer);
    else {
      strncat(str, ", ", buffer);
      strncat(str, c, buffer);
    }
    
    current = current->next;
    i = i + 1;
  }

  g->code = getAllocatedString(str);
  free(str);
}

void statementListGenerateCode(GrammarList g) {
  int buffer = 1024;
  char *str = malloc(sizeof(char)*buffer);
  GrammarNode current = g->head;
  int i = 0;
  while (current)
  {
    char *c = ((Statement)current->data)->code;
    int newlength;
    if(i)
      newlength = strlen(str) + strlen(c) + 1;
    else
      newlength = strlen(c) + 1;
    while (newlength>buffer) {
      buffer *= 2;
      char *old = str;
      str = malloc(sizeof(char)*buffer);
      strcpy(str, old);
      free(old);
    }

    if (i == 0)
      strncpy(str, c, buffer);
    else
      strncat(str, c, buffer);
    
    current = current->next;
    i = i + 1;
  }

  g->code = getAllocatedString(str);
  free(str);


}

void parameterListGenerateCode(GrammarList g) {

}

void forStatementGenerateCode(Statement s) {


}

void whileStatementGenerateCode(Statement s) {

}

void ifStatementGenerateCode(Statement s) {

}

void ifelseStatementGenerateCode(Statement s) {

}

void dictlistGenerateCode(Statement s) {

}

void dictDefinitionsGenerateCode(Statement s) {

}

void dictGenerateCode(Statement s) {

}

void nodeCreationGenerateCode(Statement s) {

}

void nodeAssignmentGenerateCode(Statement s) {

}

void nodeDictionaryGenerateCode(Statement s) {

}

void edgeCreationGenerateCode(Statement s) {

}

void edgeStatementGenerateCode(Statement s) {

}

void statementGenerateCode(Statement s) {
  char str[strlen(s->sub1.s->code)+1];
  strcpy(str, s->sub1.s->code);
  s->code = getAllocatedString(str);
}

void expressionStatementGenerateCode(Statement s){
  char str[strlen(s->sub1.e->code)+2];
  strcpy(str, s->sub1.e->code);
  strcat(str, ";\n");
  s->code = getAllocatedString(str);
}

void declStatementGenerateCode(Statement s){

}

void parameterGenerateCode(Parameter p) {

}

void passupExpressionCode(Expression e) {
  e->code = getAllocatedString(e->sub1.e->code);
//  printf("passing up code");
}

void postfixIdentifierGenerateCode(Expression e) {

}

void postfixDecrementGenerateCode(Expression e) {

}

void postfixIncrementGenerateCode(Expression e) {

}

void postfixArgumentGenerateCode(Expression e) {

  if (e->deriv.postfix == arg)
  {
    char *str = e->sub1.e->code;
    char *str2 = e->sub2.l->code;
    int length = strlen(str) + strlen(str2) + 3;
    char result[length];
    strncpy(result, str, length);
    strncat(result, "(", length);
    strncat(result, str2, length);
    strncat(result, ")", length);
    e->code = getAllocatedString(result);
  }
}

void postfixBracketGenerateCode(Expression e) {

}

void unaryExpressionGenerateCode(Expression e) {
  e->code = getAllocatedString(e->sub1.e->code);
}

void castTypedExpressionGenerateCode(Expression e) {

}

void multExpressionGenerateCode(Expression e) {

}

void addExpressionGenerateCode(Expression e) {

}

void relatExpressionGenerateCode(Expression e) {

}

void eqExpressionGenerateCode(Expression e) {

}

void condExpressionGenerateCode(Expression e) {

}

void assignmentInitExpressionGenerateCode(Expression e) {

}

void edgeExpressionGenerateCode(Expression e) {

}

void assignmentExpressionGenerateCode(Expression e) {

}

void primaryExpressionGenerateCode(Expression e) {
  switch(e->deriv.primary)
  {
    case primary_identifier: 
      e->code = getAllocatedString(e->sub1.i->code);
     break;
    case primary_string:
      e->code = getAllocatedString(e->sub1.s);
      break;
    default: //not correct default behavior, just tryna debug
      e->code = getAllocatedString(e->sub1.s); 
      break;
  }
}

void functionExpressionGenerateCode(Expression e) {

}

void twoExpressionGenerateCode(Expression e) {

}

void identifierGenerateCode(Identifier i) {
/*  NOTE: the commented out code is what we want to do, but for some reason it results in the code being blank.*/
  char *c;
  if(!strcmp(i->symbol, "print"))
    c = "printf";
  else
    c = i->symbol;
  i->code = getAllocatedString(c); 
}

char *getAllocatedString(char *s) {
  char *ret = (char *)malloc((strlen(s)+1)*sizeof(char));
  strcpy(ret, s);
  return ret;
}
