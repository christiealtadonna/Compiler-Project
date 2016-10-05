
#Makefile for Prog4-Lexer

OPTS = -g -c -Wall -Werror


lextest: lextest.o lexer.o token.o
	g++ -o lextest lextest.o lexer.o token.o

lextest.o: lextest.cc lexer.h token.h
	g++ $(OPTS) lextest.cc

lexer.o: lexer.cc lexer.h token.h
	g++ $(OPTS) lexer.cc

token.o: token.cc token.h 
	g++ $(OPTS) token.cc

clean:
	rm lexttest *.o


