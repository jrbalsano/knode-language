CC = gcc
# Use -DMEMTRACE to trace nodes as they are created, walked, and freed
# Use -DCODETRACE to monitor the code as it is built to see what errors are
# introducted at each step.
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
DEPENDS = comp/lex.yy.o comp/yacc.tab.o comp/absyn.o comp/symtable.o comp/walker.o comp/typecheck.o comp/codegen.o comp/scope.o comp/typechecktype.h
COMPILER = klc
PREPROCESSOR = klp

##############################
#   High Level Executables   #
##############################

.PHONY: knode
knode: $(COMPILER) $(PREPROCESSOR) libs/libknode.a

$(PREPROCESSOR): prep/whitelex.yy.o
	$(CC) prep/whitelex.yy.o -o $(PREPROCESSOR)

$(COMPILER): $(DEPENDS)
	$(CC) $(DEPENDS) -o $(COMPILER)

##############################
#         Object Files       #
##############################

comp/scope.o: comp/symtable.h comp/typechecktype.h

comp/codegen.o: comp/absyn.h

comp/typecheck.o: comp/absyn.h

comp/walker.o: comp/absyn.h comp/typecheck.h comp/codegen.h

comp/symtable.o: libs/uthash.h comp/typechecktype.h

comp/absyn.o: comp/typechecktype.h comp/scope.h

comp/lex.yy.o: comp/lex.yy.c

prep/whitelex.yy.o: prep/whitelex.yy.c prep/whitelex.h

comp/yacc.tab.o: comp/yacc.tab.c comp/absyn.h comp/symtable.h comp/walker.h

##############################
#       Library Files        #
##############################

libs/libknode.a: libs/dict.o libs/edge.o libs/node.o libs/smartpointers.o libs/uthash.h
	ar rc libs/libknode.a libs/dict.o libs/edge.o libs/node.o libs/smartpointers.o libs/uthash.h
	ranlib libs/libknode.a

libs/node.o: libs/dict.h libs/smartpointers.h libs/edge.h

libs/edge.o: libs/uthash.h libs/smartpointers.h libs/node.h

libs/smartpointers.o: libs/node.h libs/edge.h libs/dict.h

libs/dict.o: libs/uthash.h

##############################
#       lex/yacc C Files     #
##############################

comp/lex.yy.c: comp/lex.l comp/yacc.tab.c
	cd comp; lex lex.l

comp/yacc.tab.c: comp/yacc.y 
	cd comp; bison -d yacc.y

prep/whitelex.yy.c: prep/whitelex.l 
	cd prep; lex -o whitelex.yy.c whitelex.l

##############################
#          Utilities         #
##############################

.PHONY: yacc-debug
yacc-debug: yacc.y absyn.h symtable.h walker.h
	bison -d yacc.y --debug --verbose

.PHONY: clean
clean:
	rm -f $(COMPILER) $(PREPROCESSOR) a.out
	rm -f prep/whitelex.yy.c comp/lex.yy.c comp/yacc.tab.* comp/yacc.output comp/*.o libs/*.o libs/*.a
	rm -rf testall.log tests/*.out tests/*.c tests/*.out tests/*.log klc.dSYM klp.dSYM a.out.dSYM

.PHONY: all
all: clean $(PREPROCESSOR) $(COMPILER)
