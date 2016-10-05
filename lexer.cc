
#include "token.h"
#include "lexer.h"
#include <iostream>
#include <string>

using namespace std;

//Dont need classLExer{ } in .cc file

  //put array of keywords here

  //initialize isteam in header -because reference types need to be
  //initialized at creation time-once in curly bracs object already exits
Lexer::Lexer(istream& istream):inputStream(istream){
    line = 0;
    pos = 0;
    ch = nextChar(); // extracts first character from string

    //call next char here^

  }

  //Destructor ------ DO YOU NEED TO DELETE ANYTHING
  Lexer::~Lexer(){
  }

  char Lexer::nextChar(){

    //check to see if end of line or end of file
    if(ch == '\n'){
      line = line+1;
      pos = 0;
      ch = ' ';  //blank 
    }
    else if(ch == '#'){
	ch =  '#';
    }
    else{
	ch = inputStream.get();
	pos = pos + 1; //increment position on the line WILL I BE ABLE
		       //TO USE THIS POS IN NEXT FUNCTION
    }
    return ch;
  }

  //99% of work in nextToken

  Token Lexer::nextToken(){

    int type[] = {Token:: IF, Token:: ELSE, Token:: WHILE, Token:: FUNCTION,
		  Token:: VAR, Token::PRINTF, Token:: RETURN};
    string keys[] = {"if","else","while","function","var","printf","return"};

    string specChar[] = {"+","-","*","/","=","==","!=","<","<=",">",">=","&&","||\
"};
    //,"(",")","{","}",",",";"};
    char punct[] = {'(',')','{','}',',',';'};
    int specType[] = {Token::PLUS, Token::MINUS, Token::TIMES, Token::DIVIDE, Token::ASSIGN, Token::EQ, Token::NE,Token::LT, Token::LE, Token:: GT, Token:: GE, \
		      Token::AND, Token::OR};
    int puncType[] = {Token::LPAREN, Token::RPAREN, Token::LBRACE, Token::RBRACE, Token::COMMA, Token::SEMICOLON};

    


    //dont need to initliaze char or else going to always skip a ch
    //between tokens- ch is initialized in constructor and them
    //incremented from there
    string lexemeBuild=""; //want to initialize everytime because
			//starting over
    Token token;  //can initialize not when i declare
    //dont call next char yet bc using char from constructor
    while(isspace(ch)){
      ch = nextChar();
    }
    if(isalpha(ch)){
      lexemeBuild = lexemeBuild+ch;
      ch = nextChar();
      while(isalnum(ch)){
	lexemeBuild = lexemeBuild + ch;
	ch = nextChar(); // get the space after the ident/keyword
			 // cause it breaks out of while
      }

     
      //test to see if its a keyword
      for(int i = 0; i < 7; i++){
	if(lexemeBuild == keys[i]){
	  return  token = Token(type[i], lexemeBuild, line, pos);  //CAN USE
							   //CONSTRUCTOR
							   //LIKE THIS
	}
      }

      //wont reach this part unless not a keyword
      return token = Token(Token::IDENT, lexemeBuild, line, pos);
    }
    //check if first letter of next token is a digit
    else if(isdigit(ch)){
      //      lexemeBuild = lexemeBuild++ch;
      // ch = nextChar();
      while(isdigit(ch)){
	lexemeBuild = lexemeBuild + ch;
	ch = nextChar();
      }
      
      return token = Token(Token::INTLIT, lexemeBuild, line, pos);
    }
    else if(ispunct(ch)){
      //ENDOFILE
      if(ch == '#'){
	lexemeBuild = lexemeBuild+ch;
	return token = Token(Token::ENDOFFILE, lexemeBuild, line, pos);
      } // STRINGLIT
      else if(ch == '"'){
	lexemeBuild = lexemeBuild + ch;
	ch = nextChar();
	while(ch != '"'){
	  lexemeBuild = lexemeBuild + ch;
	  ch = nextChar();
	} // exit if closing quote is found
	lexemeBuild = lexemeBuild + ch; //should be final " b/c
					 //exited for loop
	ch = nextChar(); // always go one further			       
	return token = Token(Token::STRINGLIT, lexemeBuild, line, pos);
	

      }
      //PUNCTUATION OR OPERATOR
      else{
	//	lexemeBuild = lexemeBuild +ch;

	//PUNCTUATION ONLY HAS ONE CHAR

	for(int i = 0; i <7; i++){
	  if(ch  == punct[i]){
	    lexemeBuild =ch;
	  ch = nextChar(); //always look to next char
	  return token = Token(puncType[i], lexemeBuild,line,pos);
	}
	}

	//CHECK OPERATOR-WHICH CAN HAVE MORE THAN ONE CH
	while(ispunct(ch)){
	  lexemeBuild = lexemeBuild + ch;
	  ch = nextChar();
	}
	for(int i = 0; i < 13; i++){
	  if(lexemeBuild == specChar[i]){
	    return token = Token(specType[i], lexemeBuild, line, pos);
	  }
	}

	// wont reach this if special char found is returned
	//  cout<< "**ERROR - not correct token****"<< endl;
	  return token = Token(Token::ERROR, lexemeBuild, line, pos);
      }
    }//IF none of the above ERROR
    else {
      lexemeBuild = lexemeBuild+ch;
      // cout << "**ERROR --- INCORRECT TOKEN USED**";
      return token = Token(Token::ERROR, lexemeBuild, line, pos);
    }
  }
	 









