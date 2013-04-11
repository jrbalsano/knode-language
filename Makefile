CC = gcc
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g
LEXER = lexer

.PHONY: all
all: $(LEXER)

$(LEXER): lex.yy.c
	$(CC) lex.yy.c -o $(LEXER)

lex.yy.c: lex.l
	lex lex.l

.PHONY: clean
clean:
	rm -f $(LEXER) lex.yy.c a.out
