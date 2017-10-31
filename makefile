
#Makefile for Prog6-Implementing SymbolTable, Function, etc

OBJ = microc.o parser.o lexer.o token.o symboltable.o hashTable.o hash.o link.o
OPTS = -g -c -Wall -Werror

#order matters - executable file must be on the top and only one
#lextest: lextest.o lexer.o token.o
#	g++ -o lextest lextest.o lexer.o token.o

#lextest.o: lextest.cc lexer.h token.h
#	g++ $(OPTS) lextest.cc

microc:	$(OBJ)
	g++ -o microc $(OBJ)

microc.o: microc.cc parser.h token.h lexer.h symboltable.h hashTable.h hash.h link.h
	g++ $(OPTS) microc.cc

#testSymTab: testSymTab.o symboltable.o hashTable.o hash.o link.o
#	g++ -o testSymTab testSymTab.o symboltable.o hashTable.o hash.o link.o

#testSymTab.o: testSymTab.cc symboltable.h hashTable.h hash.h link.h
#	g++ $(OPTS) testSymTab.cc 

lexer.o: lexer.cc lexer.h token.h
	g++ $(OPTS) lexer.cc

token.o: token.cc token.h 
	g++ $(OPTS) token.cc

parser.o: parser.cc parser.h lexer.h token.h symboltable.h
	g++ $(OPTS) parser.cc

symboltable.o: symboltable.cc symboltable.h hashTable.h
	g++ $(OPTS) symboltable.cc

hashTable.o: hashTable.cc hashTable.h link.h hash.h
	g++ $(OPTS) hashTable.cc

hash.o: hash.h hash.cc
	g++ $(OPTS) hash.cc

link.o: link.cc link.h
	g++ $(OPTS) link.cc

clean:
	rm microc *.o


