/*
  Christie Altadonna
  cha415
  Program Assignment 5
  Microc.cc: test program tests the functions/rules and displays the
  tree that should be displayed given the tokens inputed.

 */


#include "token.h"
#include "lexer.h"
#include "symboltable.h"
#include "parser.h"
#include <iostream>
#include <fstream>

using namespace std;

bool dotree = false;
void processFile(istream& in) {
  Lexer lexer(in);
  Token token;
  Parser parser(lexer, cout);
  //if just want to parse expr change compilationunit() to
  //expression(); and it will generate a tree that justv parses that piece
  Parser::TreeNode* program = parser.compilationunit();//compilationunit(); // compilationunit
							// top rule in
							// grammer-
							// parses
							// entire
							// file;
							// returns a
							// pointer to
  							// a tree node
  if(dotree){
    cout << Parser::TreeNode::toString(program) << endl;
  }
  else{
    parser.genasm(program);
  }
 

  
}

int main(int argc, char **argv) {
  ifstream in;
  
  if (argc > 1) {
      in.open(argv[1]);
      processFile(in);
      in.close();
  } else {
    processFile(cin);
  }
  return 0;
  
}
