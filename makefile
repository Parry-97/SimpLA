all: simplac simplavm
.PHONY: all

simplac: simplac.o lexer.o parser.o tree.o symbtab.o sema.o gencode.o printcode.o svm.o
	cc -g -o simplac simplac.o lexer.o parser.o tree.o symbtab.o sema.o gencode.o printcode.o svm.o

simplavm: astack.o gencode.o lexer.o ostack.o parser.o printcode.o sema.o smachine.o svm.o symbtab.o tree.o
	cc -g -o simplavm astack.o gencode.o lexer.o ostack.o parser.o printcode.o sema.o smachine.o svm.o symbtab.o tree.o


lexer.o: lexer.c parser.h def.h
	cc -g -c lexer.c 

parser.o: parser.c def.h
	cc -g -c parser.c

simplac.o: simplac.c def.h
	cc -g -c simplac.c

tree.o: tree.c def.h
	cc -g -c tree.c

symbtab.o: symbtab.c def.h
	cc -g -c symbtab.c

sema.o: sema.c def.h
	cc -g -c sema.c

gencode.o: gencode.c def.h
	cc -g -c gencode.c

printcode.o: printcode.c def.h
	cc -g -c printcode.c

ostack.o: ostack.c def.h
	cc -g -c ostack.c

astack.o: astack.c def.h
	cc -g -c astack.c

smachine.o: smachine.c def.h
	cc -g -c smachine.c

svm.o: svm.c def.h
	cc -g -c svm.c

lexer.c: lexer.lex parser.y parser.h parser.c def.h
	flex -o lexer.c lexer.lex

parser.h: parser.y def.h
	bison -vdg -o parser.c parser.y

clean:
	rm -f lexer.c parser.c parser.h *.output *.o *.sim *.dot