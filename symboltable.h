/*
  Christie Altadonna
  cha415
  Programming Assignment 6
  Contructing a class- symbol table- to deal with variable
  declarations/scope of variables
  Include stack demo from Femisters demo in this class and
  implemented it by hardcoding it with Hash Tables
*/

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "hashTable.h"
#include <string>
#include <iostream>
#include <stdlib.h>

class SymbolTable{
public:
  //constructor
  SymbolTable();

  //deconstructor
  ~SymbolTable();

  SymbolTable* sTable;
  
private:
  //field
  int uniqueCount;  //use in addSymbol()
  
public:
  void enterScope();
  void exitScope();
  int addSymbol(string symbol);
  string getUniqueSymbol(string origSymbol);
  int index;
  // this came from Professor Femister's 'stackdemo' file
  class Stack{
  private:
    //need *?
    HashTable *stack;
    int size;
    //    int tos;
    static const int EMPTY = -1;
  public:
    int tos;
    Stack(int n):size(n),tos(Stack::EMPTY) {
      stack = new HashTable[size];  // stack is array of HashTables
    }
    
    Stack():size(10),tos(Stack::EMPTY) {
      stack = new HashTable[size];
    }

    Stack(const Stack& s)  { // Copy constructor
      size = s.size;
      tos = s.tos;
      stack = new HashTable[size];
      for (int i = 0; i < size; ++i) {
	stack[i] = s.stack[i];
      }
    }


    ~Stack() {
      if (stack != NULL) {
	delete [] stack;
      }
    }
    // should this be a &
    void push(HashTable ht) {  //creates a copy hash table- overloaded
			       //assignment operator
      if (tos >= size - 1) {
	cerr << "Stack overflow\n";
	exit(1);
      } else {
	stack[++tos] = ht;
      }
    }

    HashTable&  pop() {
      if (tos < 0) {
	cerr << "Stack underflow\n";
	exit(1);
      } else {
	return stack[tos--];
      }
    }

    HashTable& peek() const {
      if (tos < 0) {
	cerr << "Peek on empty stack!\n";
	exit(1);
      } else {
	return stack[tos];  // returning a copy of a hash table
      }
    }

    friend ostream& operator <<(ostream& out, const Stack& s){
      out << "[ ";
      //operator<<(out, "[ ");
      for (int i=0; i <= s.tos; i++) {
	//	out << s.stack[i] << " ";
      }
      out << "]";
      return out;
    }
    //ERROR
    void checkIndex(int i) const {
      if (i < 0 || i > tos) {
	cerr << "Index out of bounds\n";
	cerr << i << endl;
	exit(1);
      }
    }
    //THIS IS THE ERROR
    
    HashTable& operator [](int i){
      // cout << "lvalue []\n";
      checkIndex(i);
      return stack[i];
    }
    //dont need & here
    const HashTable operator [](int i) const {
      cout << "rvalue []\n";
      checkIndex(i);
      return stack[i];
    }

  };


  //fields -must declare after create stack
  Stack stck;

  //should this be a reference
  HashTable ht;
  int stackSize;


};
#endif
