all: simplac simplavm
.PHONY: all

simplac: lexer.o parser.o tree.o symbtab.o sema.o gencode.o printcode.o svm.o
	cc -g -o simplac lexer.o parser.o tree.o symbtab.o sema.o gencode.o printcode.o svm.o

simplavm: lexer.o symbtab.o sema.o gencode.o printcode.o astack.o ostack.o smachine.o svm.o
	cc -g -o simplavm lexer.o symbtab.o sema.o gencode.o printcode.o astack.o ostack.o smachine.o svm.o

lexer.o: lexer.c parser.h def.h
	cc -g -c lexer.c 

parser.o: parser.c def.h
	cc -g -c parser.c

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