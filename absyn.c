TranslationUnit getTranslationUnit(FunctionDefinition fd) {
  TranslationUnit ret = malloc(sizeof(struct translationUnit_));
  ret->f = fd;
  return ret;
}

FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs) {
  FunctionDefinition ret = malloc(sizeof(struct functionDefinition_));
  ret->d = d;
  ret->cs = cs;
  return ret;
}

Declarator declaratorId(Identifier id) {
  Declarator d = malloc(sizeof(struct declarator_));
  d->name = id;
  return d;
}

Declarator getDeclarator(Declarator d, GrammarList pList) {
  d->p = pList;
  return d;
}


CompoundStatement newCompoundStatement(GrammarList sList) {
  CompoundStatement ret = malloc(sizeof(struct compoundStatement_));
  ret->sList = sList;
  return ret;
}

GrammarList newStatementList(Statement s) {
  GrammarList sList = malloc(sizeof(struct grammarList_));
  sList->head = 0;
  addFront(sList, s);
  return sList;
}

Statement getExpressionStatement(Expression e) {
  Statement s = malloc(sizeof(struct statement_));
  s->type = expression;
  s->sub.e = e;
  return s;
}

Expression getFunctionExpression(Identifier id, GrammarList argExpList) {
  Expression ret = malloc(sizeof(struct expression_));
  ret->type = function;
  ret->val.i = id;
  ret->l = argExpList;
  return ret;
}

Expression getStringExpression(char *s) {
  Expression ret = malloc(sizeof(struct expression_));
  ret->type = string;
  ret->val.s = s;
  return ret;
}

GrammarList newArgumentExpressionList(Expression e) {
  GrammarList aeList = malloc(sizeof(struct grammarList_));
  aeList->head = 0;
  addFront(aeList, e);
  return aeList;
}

Identifier getIdentifier(char *s) {
  Identifier i = malloc(sizeof(struct identifier_));
  i->symbol = s;
  return i;
}

void addFront(GrammarList g, void *data) {
  GrammarNode n = malloc(sizeof(struct grammarNode_));
  n->data = data;
  n->next = g->head;
  g->head = n;
}

