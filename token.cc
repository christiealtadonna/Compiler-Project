
#include <cstdlib>
#include <stdio.h>
#include <iostream>   //can this be in c++ program of stdio?
#include "token.h"

using namespace std;

Token::Token(int type, string lexeme, int line, int pos){
    tokenType = type;
    this->lexeme = lexeme;
    this->line = line;
    this->pos = pos;
  }


  Token::Token(){
    tokenType = 0;  //this- parameters in lexer.h
    //dont need lexeme b/c string will construct itself by default
    this->line = 0;
    this->pos=0;
  }

  Token::~Token(){
  } // is there anything to delete

  
  int Token::getType(){
    return tokenType;
  }

  string Token::getLexeme(){
    return this->lexeme;
  }

  int Token::getLine(){
    return this->line;
  }

  int Token::getPos(){
    return this->pos;
  }

