CC = gcc
CFLAGS = -g -w
LDFLAGS = -g -w
#CFLAGS = -g -Wall -DMEMTRACE $(INCLUDES)
#LDFLAGS = -g -DMEMTRACE
#CFLAGS = -g -Wall -DPRETRACE $(INCLUDES)
#LDFLAGS = -g -DPRETRACE
DEPENDS = lex.yy.o yacc.tab.o absyn.o symtable.o walker.o typecheck.o codegen.o scope.o typechecktype.h
COMPILER = klc
PREPROCESSOR = klp

.PHONY: all
all: clean $(PREPROCESSOR) $(COMPILER)

$(PREPROCESSOR): whitelex.yy.o
	$(CC) whitelex.yy.o -o $(PREPROCESSOR)

whitelex.yy.o: whitelex.yy.c

whitelex.yy.c: whitelex.l
	lex -o whitelex.yy.c whitelex.l

$(COMPILER): $(DEPENDS)
	$(CC) $(DEPENDS) -o $(COMPILER)

test: $(DEPENDS)
	$(CC) -g -Wall -DMEMTRACE -DPRETRACE $(DEPENDS) -o $(COMPILER)

yacc.tab.o: yacc.tab.c

lex.yy.c: lex.l yacc.tab.c
	lex lex.l

yacc.tab.c: yacc.y
	bison -d yacc.y --debug --verbose

.PHONY: clean
clean:
	rm -f $(COMPILER) $(PREPROCESSOR) whitelex.yy.c lex.yy.c a.out yacc.tab.* yacc.output *.o testall.log tests/*.out
