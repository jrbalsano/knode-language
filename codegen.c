#include "codegen.h"
int knodetemp;
void translationUnitGenerateCode(TranslationUnit t) {

}

void functionDefinitionGenerateCode(FunctionDefinition f) {

}

void declaratorGenerateCode(Declarator d) {

}

void compoundStatementGenerateCode(CompoundStatement cs) {

}

void expressionListGenerateCode(GrammarList g) {

}

void statementListGenerateCode(GrammarList g) {

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

}

void expressionStatementGenerateCode(Statement s){

}

void declStatementGenerateCode(Statement s){

}

void parameterGenerateCode(Parameter p) {

}

void passupExpressionCode(Expression e) {

}

void postfixIdentifierGenerateCode(Expression e) {

}

void postfixDecrementGenerateCode(Expression e) {

}

void postfixIncrementGenerateCode(Expression e) {

}

void postfixArgumentGenerateCode(Expression e) {

}

void postfixBracketGenerateCode(Expression e) {

}

void unaryExpressionGenerateCode(Expression e) {

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
  char *s1 = getValidString(e->sub1.e->value);
  char *s2 = getValidString(e->sub2.e->value); 
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
  
  const char *valformat = "__knodetemp%s;\n";
  int vallength = strlen(format) + 1 + strlen(k);
  e->value = (char *)malloc(vallength * sizeof(char));
  sprintf(e->value, valformat, k);

  //postcode, none

  printf("%s", e->precode);
  printf("%s", e->value);

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

}

void functionExpressionGenerateCode(Expression e) {

}

void twoExpressionGenerateCode(Expression e) {

}

void identifierGenerateCode(Identifier i) {

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
