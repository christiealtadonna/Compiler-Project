/*
  Christie Altadonna
  cha415
  PA 6
  Implementing the symbol table that takes care of the variable
  declarations and scope of variables
 */

#include "symboltable.h"
#include "hashTable.h"
#include <string>
#include <sstream>

using namespace std;

//what should by constructor do
SymbolTable::SymbolTable(){
  //HashTable scope = new HashTable();
  //stck.push(scope);  
  // stck = Stack();
  //stck = Stack(10);
  index = 0;
  stackSize = 0;
}

//SymbolTable::SymbolTable(){
//size =0;
//}

SymbolTable::~SymbolTable(){
  //  delete stck;     // is this correct
}

void SymbolTable::enterScope(){
  //HashTable newScope;
  stck.push(HashTable(53));  //appears that push is copying hashtable 
  stackSize++;
  ht = stck.peek(); // set ht to point to top of stack
}

void SymbolTable::exitScope(){
 HashTable popped = stck.pop();
 stackSize--;
 if(stackSize > 0){
   ht = stck.peek();
 }
}

string itos(int i) { stringstream ss; ss << i; string res = ss.str(); return res;}

int SymbolTable::addSymbol(string symbol){
  string unique;  //what do I make unique
  int canAdd;
  if(ht.inTable(symbol)){    //if false-add symbol
    canAdd = 0;
  }

  else {
    unique = symbol +"$"+itos(index++);
    // unique += "$";
    //unique += index;
    //index++;

    
    //cout << unique << endl;
    ht.add(symbol,unique);
    canAdd = 1;
  }
  return canAdd;

}

string SymbolTable::getUniqueSymbol(string origSymbol){
  int ind = stck.tos;
  //  cerr << "Index" << ind << endl;
  string returnSym;
  //this is coming out false but its true
  //  HashTable& ht2 = stck[ind];

  
  //  cerr << ht << endl;
  //cerr << stck.operator[](stck.tos) << endl;
  //want it to be false so doesnt go through while loop b/c its in the table
  //  cerr << !ht.inTable(origSymbol) << endl;
  //  cerr << "Is index is in stack: " << stck[ind].inTable(origSymbol) << endl;
  while(ind >= 0 && !((stck[ind]).inTable(origSymbol))){
      ind--;
      //  cerr << ind << endl;
  }
  if(ind < 0){
    returnSym = "";
  }
  else{
    returnSym = (stck[ind]).get(origSymbol); //is this allowed?
    // cerr << "You have gotten into the else- so should return unique symbol" << endl;
    // cerr << returnSym << endl;
  }
  return returnSym;

}
