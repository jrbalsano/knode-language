CC = gcc
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g
#CFLAGS = -g -Wall -DMEMTRACE $(INCLUDES)
#LDFLAGS = -g -DMEMTRACE
#CFLAGS = -g -Wall -DPRETRACE $(INCLUDES)
#LDFLAGS = -g -DPRETRACE
COMPILER = klc
PREPROCESSOR = klp

.PHONY: all
all: clean $(PREPROCESSOR) $(COMPILER)

$(PREPROCESSOR): whitelex.yy.o
	$(CC) whitelex.yy.o -o $(PREPROCESSOR)

whitelex.yy.o: whitelex.yy.c

whitelex.yy.c: whitelex.l
	lex -o whitelex.yy.c whitelex.l

$(COMPILER): lex.yy.o yacc.tab.o absyn.o symtable.o walker.o typecheck.o codegen.o scope.o typechecktype.h
	$(CC) lex.yy.o yacc.tab.o absyn.o symtable.o walker.o typecheck.o codegen.o scope.o -o $(COMPILER)


yacc.tab.o: yacc.tab.c

lex.yy.c: lex.l yacc.tab.c
	lex lex.l

yacc.tab.c: yacc.y
	bison -d yacc.y --debug --verbose

.PHONY: clean
clean:
	rm -f $(COMPILER) $(PREPROCESSOR) whitelex.yy.c lex.yy.c a.out yacc.tab.* yacc.output *.o testall.log tests/*.out
