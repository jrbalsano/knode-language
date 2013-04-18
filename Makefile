CC = gcc
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g
COMPILER = klc
PREPROCESSOR = klp

.PHONY: all
all: clean $(PREPROCESSOR) $(COMPILER)

$(PREPROCESSOR): whitelex.yy.o
	$(CC) whitelex.yy.o -o $(PREPROCESSOR)

whitelex.yy.o: whitelex.yy.c

whitelex.yy.c: whitelex.l
	lex -o whitelex.yy.c whitelex.l

$(COMPILER): lex.yy.o yacc.tab.o absyn.o 
	$(CC) lex.yy.o yacc.tab.o absyn.o -o $(COMPILER)

yacc.tab.o: yacc.tab.c

lex.yy.c: lex.l yacc.tab.c
	lex lex.l

yacc.tab.c: yacc.y
	bison -d yacc.y

.PHONY: clean
clean:
	rm -f $(COMPILER) $(PREPROCESSOR) whitelex.yy.c lex.yy.c a.out yacc.tab.* *.o
