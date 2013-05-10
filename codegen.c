#include "codegen.h"

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
