#include "codegen.h"

void translationUnitGenerateCode(TranslationUnit t) {

  t->code = t->fd->code;
  //does not deal with case where t also has a translation unit

}

void functionDefinitionGenerateCode(FunctionDefinition f) {

  switch(f->type_name)
  {
    case 0:
      f->code = f->d->code + f->cs->code;
      break;
    case type:
  }
        
}

void declaratorGenerateCode(Declarator d) {

  d->code = d->name->code + "():\n";

  //TODO: deal with d->p case
}

void compoundStatementGenerateCode(CompoundStatement cs) {

  cs.code = "\n  " + cs->sList->code; //this might not work so nicely if it's not just for hello world... :/ might need to do something icky with the grammar list ick :/

}

void expressionListGenerateCode(GrammarList g) {

//popfront n'at, come back and do later

//set g.code equal to something PLEASE
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

  if (e->deriv.postfix == arg)
  {
       e.code = e->sub1.e->code + "(" + e->sub2.l->code + ")";  
  }
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

  i->code = i->symbol;

}

char *getAllocatedString(char *s) {
  char *ret = (char *)malloc((strlen(s)+1)*sizeof(char));
  strcpy(ret, s);
  return ret;
}
