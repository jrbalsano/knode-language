CC = gcc
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g
COMPILER = klc

.PHONY: all
all: clean $(COMPILER)

$(COMPILER): lex.yy.o yacc.tab.o absyn.o
	$(CC) lex.yy.o yacc.tab.o absyn.o -o $(COMPILER)

yacc.tab.o: yacc.tab.c

lex.yy.c: lex.l yacc.tab.c
	lex lex.l

yacc.tab.c: yacc.y
	bison -d yacc.y

.PHONY: clean
clean:
	rm -f $(COMPILER) lex.yy.c a.out yacc.tab.* *.o
