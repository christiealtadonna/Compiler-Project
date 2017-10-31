/*
Christie Altadonna
cha415
Program 7
Description: In this file we are implementing the Parser definitons;
we are giving the code for the functions that represent syntax
rules/logic. In program 7 specifically implement genasm and all the
functions that go with it. Implementing printfstatements as well
 */


#include "parser.h"
#include "token.h"
#include "lexer.h"
#include "symboltable.h"
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

stringstream ss;

Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1), jindex(0) {
  //make sure jindex should be zero here
  token = lexer.nextToken(); //first  token initialized in token

}

Parser::~Parser() {
}

const string Parser::ops[] = {"ADD", "SUB", "MULT", "DIV",

		      "ISEQ", "ISNE", "ISLT", "ISLE", "ISGT", "ISGE",

		      "AND", "OR",

		      "PUSHL", "PUSHV", "STORE",

		      "JUMP", "JUMPF", "JUMPT", "CALL", "RET","FUNC",
			      
		      "PARAM",

		      "PRINTF",

		      "LABEL", "SEQ" };

void Parser::error(string message) {
  cerr << message << " Found " << token.getLexeme() << " at line " << token.getLine() << " position " << token.getPos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.getType() != tokenType)
    error(message);
}



Parser::TreeNode* Parser::funcall(string functionName){
  check(Token::LPAREN, "must follow func name with '('");
  token = lexer.nextToken();
  int tokenType = token.getType();
  //no parameters - just return the call node
  TreeNode* callNode = new TreeNode(CALL, functionName);
  TreeNode* returnNode;
  TreeNode* exprNode;
  if(tokenType == Token::RPAREN){
    token = lexer.nextToken();
    return callNode;
  }
  else{
    returnNode = expression();
    tokenType = token.getType();
     while(tokenType != Token::RPAREN){
       check(Token::COMMA, "Error- must separate arguments with a ','");
       token = lexer.nextToken();
       exprNode = expression();
       tokenType = token.getType();
       returnNode = new TreeNode(SEQ, returnNode, exprNode);
     }
  }
     check(Token::RPAREN, "Error, must end function call with ')'");
     token = lexer.nextToken();
     returnNode = new TreeNode(SEQ, returnNode, callNode);
     return returnNode;

}

Parser::TreeNode* Parser::factor() {
  int tokenType = token.getType(); // next token is already loaded in
  TreeNode* stackNode;
  string idName;
  switch(tokenType){
  case Token::LPAREN:     //LPAREN and RPAREN do not go in the tree
    token=lexer.nextToken();
    stackNode = expression(); //expression() calls nextToken()
    check(Token::RPAREN, "Invalid token, must be a right parenthesis");
    token= lexer.nextToken();
    break;
  case Token::INTLIT:
    stackNode = new TreeNode(PUSHL, token.getLexeme());
    token = lexer.nextToken();
    break;
  case Token::IDENT:
    idName = token.getLexeme();
    token= lexer.nextToken();
    tokenType = token.getType();
    if(tokenType != Token::LPAREN){
      string unique;
      unique = symTable.getUniqueSymbol(idName);
      if(unique == ""){
	error("Error-variable has not been declared in this scope");
      }
      stackNode = new TreeNode(PUSHV, unique); 


    }
    else{
      //ADDED TO FUNCTION function
      /* string symb = symTable.getUniqueSymbol(idName);
      stackNode = funcall(symb);
      */
      stackNode = funcall(idName);
    }
    break; 
    //add the <funccall> case when you declare funccall
  default:
    error("Incorrect factor token");
    break;  
  }

  return stackNode; 
}

Parser::TreeNode* Parser::term() {
  TreeNode* termNode = factor(); //saves term node that factor provide
				 //(next token
  TreeNode* factorNode;
  int tokenType = token.getType();
  while(tokenType == Token::TIMES || tokenType == Token::DIVIDE){
    // tt = token.getType(); dont need because using switch
    token = lexer.nextToken();
    factorNode = factor();
    Operation op;
    switch (tokenType){   // assign token type to variable so after
			  // get next operation still have that variable
    case Token::TIMES:
      op = MULT;
      break;
    case Token::DIVIDE:
      op=DIV;
      break;
    }
    termNode = new TreeNode(op, termNode, factorNode);
						      //one to get
                                // how to get next token type; next
				// thing that happens is the test in
				// the while loop
  
  tokenType= token.getType();
  }
  return termNode;
}

Parser::TreeNode* Parser::expression() {
  TreeNode* termNode = term(); // looks at the next token
   int tokenType = token.getType();
   while(tokenType == Token::PLUS || tokenType == Token::MINUS){
     token = lexer.nextToken(); //go to next term token
     TreeNode* termNode2 = term();
     Operation op;   //initialize op as an operation
     switch(tokenType){
     case Token::PLUS:
       op = ADD;
       break;
     case Token::MINUS:
       op= SUB;
       break;
     }
     // next time loop iterates, create tree with the operation of the
     // previous iteration as the left child and the new termNode2 the right
     termNode = new TreeNode(op, termNode, termNode2);
     

     tokenType = token.getType();  //term looks to next token-loaded
				   //for another iteration of while loop
   }
   return termNode;
}

Parser::TreeNode* Parser::relationalExpression() {
  TreeNode* expNode = expression();
  int tokenType = token.getType();
  Operation op;
  switch(tokenType){
  case Token::EQ:
     op = ISEQ;
     break;
  case Token::LT:
    op = ISLT;
    break;
  case Token::LE:
    op=ISLE;
    break;
  case Token::GT:
    op=ISGT;
    break;
  case Token::GE:
    op=ISGE;
    break;
  case Token::NE:
    op=ISNE;
    break;
  default:
    // dont need to call nextToken bc expression() callled it
    return expNode;
  }

  token = lexer.nextToken();
  TreeNode* expNode2 = expression();

  return new TreeNode(op, expNode, expNode2); 
}

Parser::TreeNode* Parser::logicalExpression() {
   TreeNode* reNode = relationalExpression();
  int tokenType = token.getType();
  while(tokenType == Token::AND || tokenType == Token::OR){
    token = lexer.nextToken();
    TreeNode* reNode2 = relationalExpression();
    Operation op;
    switch(tokenType){
    case Token::AND:
      op = AND;
      break;
    case Token::OR:
      op=OR;
      break;
    }
    reNode = new TreeNode(op, reNode, reNode2);
    tokenType = token.getType(); // get token type for another
				 // iteration  of while look- have
				 // token type
  }
  return reNode;

}


Parser::TreeNode* Parser::returnStatement(){
  check(Token::RETURN, "Error- must begin return statement with 'return'");
  token = lexer.nextToken();
  TreeNode* leNode = logicalExpression();
  check(Token::SEMICOLON, "Error must end returnStatement with ';'");
  TreeNode* retNode = new TreeNode(RET);
  TreeNode* returnNode = new TreeNode(SEQ, leNode, retNode);
  token = lexer.nextToken();
  return returnNode;

}



Parser::TreeNode* Parser::ifStatement() {
  check(Token::IF, "Error- if statement must start with an if");
  token = lexer.nextToken(); //token will be a LPAREN
  check(Token::LPAREN, "Error- logical expression must start with left parenthesis");
  token = lexer.nextToken();  // start of logical expression
  TreeNode* leNode = logicalExpression();

  string l1 = makeLabel();
  TreeNode* jumpNode = new TreeNode(JUMPF, l1);
  TreeNode* returnNode = new TreeNode(SEQ, leNode, jumpNode);
  int tokenType = token.getType();

  check(Token::RPAREN, "Error- logical expression must end  with right  parenthesis");
  token = lexer.nextToken();

  symTable.enterScope();
  TreeNode* thenBlock = block();
  symTable.exitScope();
  
  returnNode = new TreeNode(SEQ, returnNode, thenBlock);
  // token currently would be RPAREN

  
  tokenType = token.getType(); //if 'ELSE' then theres an else
				   //statement
  TreeNode* labelNode = new TreeNode(LABEL,l1);
  
  //must check for else -take care of dangling else
  if(tokenType == Token::ELSE){
    token = lexer.nextToken(); //move to block
    string l2 = makeLabel();
    TreeNode* jumpNode2 = new TreeNode(JUMP, l2);
    returnNode = new TreeNode(SEQ, returnNode, jumpNode2);

    returnNode = new TreeNode(SEQ, returnNode, labelNode);
    symTable.enterScope();
    TreeNode* elseBlock = block();
    symTable.exitScope();
    
    returnNode = new TreeNode(SEQ, returnNode, elseBlock);
    TreeNode* labelNode2 = new TreeNode(LABEL, l2);
    returnNode = new TreeNode(SEQ, returnNode, labelNode2);
  }

  else{
    returnNode = new TreeNode(SEQ, returnNode, labelNode);
  }

  return returnNode;

}




Parser::TreeNode* Parser::whileStatement() {
  check(Token::WHILE, "Error- while statement must start with 'while'");
  token = lexer.nextToken();
  check(Token::LPAREN, "Must start while condition with left parenthesis");
  token = lexer.nextToken(); //start of logical expression
  TreeNode* leNode = logicalExpression();
  check(Token::RPAREN, "Must end while condition with right parenthesis");
  token = lexer.nextToken();
  symTable.enterScope();
  TreeNode* blockNode = block();
  symTable.exitScope();
  //block calls nextToken(); 
  string l1 = makeLabel();
  string l2 = makeLabel();
  TreeNode* returnNode;
  TreeNode* labelNode = new TreeNode(LABEL, l1);
  //create a subtree that labels L1 or evalutates logical expr
  returnNode = new TreeNode(SEQ, labelNode, leNode);
  TreeNode* jumpfNode = new TreeNode(JUMPF, l2);
  //JUMPF and block subtree
  returnNode = new TreeNode(SEQ, returnNode, jumpfNode);
  returnNode = new TreeNode(SEQ, returnNode, blockNode);
    
  TreeNode* jumpL1 = new TreeNode(JUMP, l1);

  
  TreeNode* labelL2 = new TreeNode(LABEL, l2);
  //JUMPL1 or LABEL L2 subtree


  TreeNode* jumpLabel = new TreeNode(SEQ, jumpL1, labelL2);
  returnNode = new TreeNode(SEQ, returnNode, jumpLabel);
  
  return returnNode;
}


Parser::TreeNode* Parser::assignStatement() {
  check(Token::IDENT,"error-assignment statement must start with identifier");
  string unique;
  unique = symTable.getUniqueSymbol(token.getLexeme());
  if(unique == ""){
    error("Error- identifier has not been declared");
  }
  TreeNode* idNode = new TreeNode(STORE, unique);//store unique symbol
						 //here to use in tree
						  
  token = lexer.nextToken();
  check(Token::ASSIGN,"error- must be an '='");
  token = lexer.nextToken();
  TreeNode* leNode = logicalExpression();  

  check(Token::SEMICOLON, "error-assignment statement must end with a ';'");
  token = lexer.nextToken();
  //sequence together the logical expression and the STOREd variable
  return new TreeNode(SEQ, leNode, idNode);
}



Parser::TreeNode* Parser::statement() {
  int tokenType = token.getType();
  TreeNode* returnNode;
  switch(tokenType){
  case Token::IDENT:
    returnNode = assignStatement();
    break;
  case Token::WHILE:
    returnNode = whileStatement();
    // token = lexer.nextToken();
    break;
  case Token::IF:
    returnNode = ifStatement();
    //token= lexer.nextToken();
    break;
  case Token::VAR:
    returnNode = vardefStatement();
    break;
  case Token::RETURN:
    returnNode = returnStatement();
    break;
  case Token::PRINTF:
    returnNode = printfStatement();
    break;
  default:
    error("Token not a statement");
    break;
  }
  //don't need to call next token because each of these call next token
  return returnNode;

}
//create subtree for block of statements
Parser::TreeNode* Parser::block() {
  //symTable.enterScope();
  int tokenType = token.getType();
  check(Token::LBRACE, "Error- block must start with left brace");
  token = lexer.nextToken();
  //start in statement token
  TreeNode* returnNode;
  tokenType = token.getType();
  if(tokenType != Token::RBRACE){
    TreeNode* newNode;
    returnNode= statement();
    //token = lexer.nextToken();
    tokenType = token.getType();
    while(tokenType != Token::RBRACE){
      //token = lexer.nextToken();  // call for token after '}'
      newNode = statement();
      tokenType = token.getType();
      returnNode = new TreeNode(SEQ, returnNode, newNode);
    }
  }
  else {
    //return plain SEQ node with no children if block is empty
    check(Token::RBRACE, "error-must end block right '}'");
    returnNode = new TreeNode(SEQ);
  }
  //token after statement() is called should be right brace so look
  //one more past
  check(Token::RBRACE, "error-must end block right '}'");

  // symTable.exitScope();
  
  token = lexer.nextToken();
  return returnNode;

}

//variable definition statement tree node code
Parser::TreeNode* Parser::vardefStatement(){
  check(Token::VAR, "Error- must use 'var' to declare a variable");
  token = lexer.nextToken();
  check(Token::IDENT, "Error-must use an identifier to label a variable");
   int canAdd;
   string lexeme = token.getLexeme();
  canAdd =symTable.addSymbol(lexeme); // returns zero or 1
  if(canAdd == 0){
    error("Variable name is already defined in this scope");
  }
  token = lexer.nextToken();
  int tokenType = token.getType();
  while(tokenType == Token::COMMA){
    token = lexer.nextToken();
    check(Token::IDENT, "Error-must use an identifier to label a variable");
    canAdd = symTable.addSymbol(token.getLexeme());

    //if indent already in scope cannot declare
    if(canAdd == 0){
      error("Variable name is already defined in this scope");
    }
    token=lexer.nextToken();
    tokenType = token.getType();
  }
  check(Token::SEMICOLON, "Error, must end a var def with a ';'");
  token = lexer.nextToken();
  //return a SEQ node do not have to return a tree
  TreeNode* returnNode = new TreeNode(SEQ);
  return returnNode;

}

//create subtree for function instructions
Parser::TreeNode* Parser::function(){
  check(Token::FUNCTION, "Error- must start function with word 'function'");
  token = lexer.nextToken();
  check(Token::IDENT, "Error- illegal name of function");
  //save function name
  string funcName = token.getLexeme();
  
  TreeNode* returnNode = new TreeNode(FUNC, funcName+":");

  
  token = lexer.nextToken();
  check(Token::LPAREN, "Error must use '(' after function name");
  token = lexer.nextToken();
  int tokenType = token.getType();
  TreeNode* paramNode;
  string param;
  //  string paramN;
  string uniqueParam;
  //place a new hashtable on top of stack  
  symTable.enterScope();  // EVEN IF NO PARAMS
  while(tokenType == Token::IDENT){
    // ss<< "PARAM" << counter++;
    //paramN = ss.str();
    param = token.getLexeme();

    //
    //
    
    int canAdd;
    canAdd = symTable.addSymbol(param);
    if(canAdd == 0){
      error("Duplicate parameters with same name");
    }

    //get and sue the unique param name within node
    uniqueParam = symTable.getUniqueSymbol(param);
    //change PARAM to STORE to pop top value off stack and store
    paramNode = new TreeNode(STORE, uniqueParam);
    //keep SEQ new nodes with subtrees so postorder will give correct order
    returnNode = new TreeNode(SEQ, returnNode,paramNode);
    token = lexer.nextToken();
    tokenType = token.getType();
    if(tokenType == Token::COMMA){
      token = lexer.nextToken();
      tokenType = token.getType();
    }
  }
    check(Token::RPAREN, "Error-must be a ')'");
    //must always look to next token
    token = lexer.nextToken();

    //each fucntion generates a label for a function name
    //must have a function called main so knows where to start
    //TreeNode* functionNode = new TreeNode(FUNC, fname+":");
    
    
    TreeNode* blockNode = block();
    //pop hashtable/scope off of stack
    symTable.exitScope();
    returnNode = new TreeNode(SEQ, returnNode, blockNode);
    return returnNode;
}
      

//call zero or more functions and generate nodes
Parser::TreeNode* Parser::compilationunit() {
  int tokenType = token.getType();
  TreeNode* returnNode = new TreeNode(SEQ);  //WHAT to return if no function 
  if(tokenType == Token::FUNCTION){
    returnNode =function();
    tokenType =token.getType();
  }  
  while(tokenType == Token::FUNCTION){
    TreeNode* funNode;
    funNode = function();
    returnNode = new TreeNode(SEQ,returnNode, funNode);
    tokenType = token.getType();
  }

  return returnNode;
}

//JFemister's code from assignment
Parser::TreeNode* Parser::printfStatement(){
  TreeNode* paramList = NULL;
  int nparams = 0;
  check(Token::PRINTF, "Expecting printf");
  token = lexer.nextToken();
  check(Token::LPAREN, "Expecting (");
  token = lexer.nextToken();
  check(Token::STRINGLIT, "Expecting string literal");
  string formatString = token.getLexeme();
  token = lexer.nextToken();
  if(token.getType() == Token::COMMA) {
    token = lexer.nextToken();
    paramList = expression();
    ++nparams;
    while(token.getType() == Token::COMMA) {
      token = lexer.nextToken();
      paramList = new TreeNode(SEQ, paramList, expression());
      ++nparams;
    }
  }
  check(Token::RPAREN, "Expecting )");
  token = lexer.nextToken();
  check(Token::SEMICOLON, "Expecting ;");
  token = lexer.nextToken();
  TreeNode* printStatement = new TreeNode(SEQ, paramList, new TreeNode(PRINTF, itos(nparams)+ formatString));
  return printStatement;
}



//generate a label to use in conds to jump to
string Parser::jlabel(){
  string tmp = "J";
  //use stringstream to concatenate a number and string into a string
  stringstream ss;
  ss << ++jindex;
  string res = ss.str();
  tmp = tmp + res;
  return tmp;
}


//print out the code
void Parser::emit(string code){
  cout <<"    " <<  code << endl;
}

//print out a label which is nto indented
void Parser::emitLabel(string code){
  cout << code << endl;
}

//function to substitute the conditional operation in
void Parser::cond1(string op){
  string j1 = jlabel();
  string j2 = jlabel();
  emit("pop rbx");
  emit("pop rax");
  emit("cmp rax,rbx");
  emit(op+" "+j1);
  emit("mov rax,0");
  emit("jmp "+j2);
  emitLabel(j1+":");
  emit("mov rax, 1");
  emitLabel(j2+":");
  emit("push rax");
}

//use big switch statement to generate instruction starting at
//rootnode
//recursive function

//declarations added before gentinst (6 in 7B)
string currentFunc;
int nfmts = 0;
string fmts[100];
void Parser::geninst(TreeNode *node){
  //check to see if base case- child is null
  //  cout << "in geninst" <<endl;
  if(node == NULL){
    return;
  }

  //postorder traversal
  geninst(node->leftChild);
  geninst(node->rightChild);
  
  int count = 0;
  string opr;
  string cond;
  string fmt;
  int nparams;
  //go throught the operations to know what to print in assembly code
  switch(node->op){
  case ADD:
    count++;
  case SUB:
    count++;
  case AND:
    count++;
  case OR:
    count++;
    emit("pop rbx");
    emit("pop rax");
    switch(count){
    case 4:
      opr = "add";
      break;
    case 3:
      opr = "sub";
      break;
    case 2:
      opr = "and";
      break;
    case 1:
      opr = "or";
      break;
    }
    emit(opr+" "+"rax, rbx");
    emit("push rax");
    break;
  case MULT:
    emit("pop rbx");
    emit("pop rax");
    emit("imul rbx");
    emit("push rax");
    break;
  case DIV:
    emit("mov rdx, 0");
    emit("pop rbx");
    emit("pop rax");
    emit("idiv rbx");
    emit("push rax");
    break;
  case LABEL:
    //label in assembler code?
    emitLabel(node->val+":");
    break;
  case ISEQ:
    cond = "je";
    cond1(cond);
    break;
  case ISNE:
    cond = "jne";
    cond1(cond);
    break;
  case ISLT:
    cond = "jl";
    cond1(cond);
    break;
  case ISLE:
    cond = "jle";
    cond1(cond);
    break;
  case ISGT:
    cond = "jg";
    cond1(cond);
    break;
  case ISGE:
    cond = "jge";
    cond1(cond);
    break;
  case JUMP:
    emit("jmp "+node->val);
    break;
  case JUMPF:
    emit("pop rax");
    emit("cmp rax,0");
    emit("je "+node->val);
    break;
  case JUMPT:
    emit("pop rax");
    emit("cmp rax,0");
    emit("jne "+node->val);
    break;
  case PUSHV:
    emit("push qword["+node->val+"]");
    break;
  case PUSHL:
    emit("mov rax, "+node->val);    //is this the interger constant??
    emit("push rax");
    break;
  case STORE:
    emit("pop qword["+node->val+"]");
    break;
  case PRINTF:
    fmt = node->val;   // val is the format string in printf
    nparams = fmt.at(0) - '0';    //takes out first digit and
				  //subtracts ASCII char of 0 which
				  //gives us an int w/ # of params
    fmt = "`" + fmt.substr(1) + "`";  //format string
    fmts[nfmts++] = fmt;  //everytime process printf save its format
			  //string in this array
    emit("mov rdi,fmt" + itos(nfmts));  
    if(nparams == 5){
      emit("pop r9");
      --nparams;
    }
    if(nparams == 4){
      emit("pop r8");
      --nparams;
    }
    if(nparams == 3){
      emit("pop rcx");
      --nparams;
    }
    if(nparams == 2){
      emit("pop rdx");
      --nparams;
    }
    if(nparams == 1){
      emit("pop rsi");
    }
    emit("mov rax,0");
    emit("push rbp");
    emit("call printf");
    emit("pop rbp");
    break;
  case CALL:
    emit("call "+node->val);  //FUNC NAME?
    emit("push rax");
    break;
  case FUNC:
    currentFunc = node->val;
    emitLabel(currentFunc);
    if(currentFunc != "main:")
      emit("pop r15");
    break;
  case RET:
    emit("pop rax");
    if(currentFunc != "main:")
      emit("push r15");
    emit("ret");
    break;
  default:
    //what is our default behavior
    // error("Operation undefined");
    break;
  }   
    
  

}


void Parser::vardefs(TreeNode *node){


  if(node == NULL){
    return;
  }
  
  //traverse the tree nodes and store the variables to put into the
  //.bss section in assembly code
   if(node->op == PUSHV || node->op == STORE){
     vars[0] = node->val;
     int i;
     for(i = n-1; vars[i] != node->val; --i);
     if(i == 0)
       vars[n++]= node->val;

  }

 
   //visit all nodes
 vardefs(node -> leftChild);
 vardefs(node -> rightChild);

}

//main code that takes the root node and creates the asm code
void Parser::genasm(TreeNode *node){
  //declare global variable for n
  n = 1;
  //global main
  cout << "   global main" << endl;
  cout << "   extern printf" << endl;
  //.bss segment
  cout << "    segment .bss" << endl;
  vardefs(node);    //IS THIS THE ROOT NODE      
  for(int i = 1; i < n; i++){
    emit(vars[i] + " resq 1");  // 1 -num of qwords
  }
 


  // test section
  cout << "    section .text" << endl;
  //pass it the root node
  geninst(node);
  
  //data section
  cout << endl << "    section .data" << endl;
  for(int i = 0; i <nfmts; ++i){
    cout << "   fmt" << i+1 << ": db "<< fmts[i] << ",0" << endl;
  }

  cout << "   fmt:  db '%ld ', 0" << endl;
  cout << "   endl: db 10, 0" << endl;
  
}

