/*
  Christie Altadonna
  CSE 109
  Program 4
  LEXER: Member variables, functions, constructor, and deconstructor headers
*/
#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <string>
#include "token.h"

using namespace std;

class Lexer{
public:
  Lexer(istream& istream); //constructor
  Token nextToken();

  //deconstructor
  ~Lexer();
  
  /* CANT DO THIS HERE BECAUSE TOKEN OBJECT NOT DECLARED  
  int type[] = {Token:: IF, Token:: ELSE, Token:: WHILE, Token:: FUNCTION,
  		  Token:: VAR, Token::PRINTF, Token:: RETURN};
  string keys[] = {"if","else","while","function","var","printf","return"};

  string specChar[] = {"+","-","*","/","=","==","!=","<","<=",">",">=","&&","||","(",")","{","}",",",";"};
  int specType[] = {Token::PLUS, Token::MINUS, Token::TIMES, Token::DIVIDE, Token::ASSIGN, Token::EQ, Token::NE,Token::LT, Token::LE, Token:: GT, Token:: GE, Token::AND, Token::OR, Token::LPAREN, Token::RPAREN, Token::LBRACE, Token::RBRACE, Token::COMMA, Token::SEMICOLON};  
  */

private:
  istream& inputStream;
  char nextChar();

  int line;
  int pos;
  char ch;
  //  string lexemeBuild; Dont need b/c starting over each new token


};

#endif
