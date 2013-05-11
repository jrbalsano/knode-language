#include "codegen.h"
int knodetemp;
void translationUnitGenerateCode(TranslationUnit t) {

  t->code = getAllocatedString(getValidString(t->f->code));
  //does not deal with case where t also has a translation unit
  printf("final code:\n%s\n", t->code);
}
void functionDefinitionGenerateCode(FunctionDefinition f) {

      Declarator dec = f->d;
      char *c = getValidString(dec->code);
      char *mainFunc = "main()\n";
      char *c1 = getValidString(f->cs->code);
      if(strcmp(c, mainFunc) == 0) {
        char *cCode = "void main()";
        int length = strlen(cCode) + strlen(c1) + 1;
        char result[length];
        strncpy(result, cCode, length);
        strncat(result, c1, length);
        f->code = getAllocatedString(result);
     }
     else {
       int length = strlen(c) + strlen(c1) + 1;
       char result[length];
       strncpy(result, c, length);
       strncat(result, c1, length);
       f->code = getAllocatedString(result);
     }
}

void declaratorGenerateCode(Declarator d) {
  if(!d->p) {
    char *c = getValidString(d->name->code);
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

  char *c1 = getValidString(cs->sList->code);
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
    c = getValidString(c);
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
    c = getValidString(c);
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
  char str[strlen(getValidString(s->sub1.s->code))+1];
  strcpy(str, getValidString(s->sub1.s->code));
  s->code = getAllocatedString(str);
}

void expressionStatementGenerateCode(Statement s){
  char str[strlen(getValidString(s->sub1.e->code))+2];
  strcpy(str, getValidString(s->sub1.e->code));
  strcat(str, ";\n");
  s->code = getAllocatedString(str);
}

void declStatementGenerateCode(Statement s){

}

void parameterGenerateCode(Parameter p) {

}

void passupExpressionCode(Expression e) {
  e->code = getAllocatedString(getValidString(e->sub1.e->code));

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
    char *str = getValidString(e->sub1.e->code);
    char *str2 = getValidString(e->sub2.l->code);
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
  e->code = getAllocatedString(getValidString(e->sub1.e->code));
}

void castTypedExpressionGenerateCode(Expression e) {

}

void multExpressionGenerateCode(Expression e) {

}

void addExpressionGenerateCode(Expression e) {
  // k is the string of the value of the current knodetemp.
  // k is incremented after use here for the next knodetemp.
  char k[15];
  sprintf(k, "%d", knodetemp++);

  // this char pointer is the length of the precode without the input.
  const char *format = "int length = strlen(%s) + strlen(%s);\nchar __knodetemp%s[length];\nstrcpy(__knodetemp%s, %s);\n strcat(__knodetemp%s, %s);\n";
  char *s1 = getValidString(e->sub1.e->code);
  char *s2 = getValidString(e->sub2.e->code);

  //  print for debugging
  printf("%s\n", s1);
  printf("%s\n", s2);

  // the length of the precode
  int length = strlen(s1) * 2 + strlen(s2) * 2 + strlen(k) * 3 + strlen(format) + 1;

  // sets the size of the precode
  e->precode = (char *)malloc(length * sizeof(char));

  // sets this expression's precode.
  sprintf(e->precode, format, s1, s2, k, k, s1, k, s2);
   
  //precode = 
  //int length = strlen(string1) + strlen(string2);
  //char __knodetemp#[length]
  //strcpy(__knodetemp#, string1);
  //strcat(__knodetemp#, string2);

  //val = __knodetemp#
  
  const char *valformat = "__knodetemp%s";
  int vallength = strlen(format) + 1 + strlen(k);
  e->code = (char *)malloc(vallength * sizeof(char));
  sprintf(e->code, valformat, k);

  //postcode, none
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
  char intval[15];
  char dval[15];
  switch(e->deriv.primary)
  {
    case primary_identifier: 
      e->code = getAllocatedString(getValidString(e->sub1.i->code));
     break;
    case primary_string:
      e->code = getAllocatedString(getValidString(e->sub1.s));
      break;
    case primary_int:
      sprintf(intval, "%d", e->sub1.ival);
      e->code = getAllocatedString(getValidString(intval));
      break;
    case primary_double:
      sprintf(dval, "%f", e->sub1.dval);
      e->code = getAllocatedString(getValidString(dval));
      break;
    case primary_bool:
      sprintf(intval, "%d", e->sub1.boolval);
      e->code = getAllocatedString(getValidString(intval));
      break;
    default: //not correct default behavior, just tryna debug
      e->code = getAllocatedString(getValidString(e->sub1.s));
      break;
  }
}

void functionExpressionGenerateCode(Expression e) {

}

void twoExpressionGenerateCode(Expression e) {

}

void identifierGenerateCode(Identifier i) {
  char *c = getValidString(i->symbol);
  if(!strcmp(c, "print"))
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

char *getValidString(char *s){
  if (s)
     return s;
  else
     return "";
}
