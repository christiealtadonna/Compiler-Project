/*
  Christie Altadonna
  cha415
  PA #6
  Implementing the hash: comes from Femisters Demos
*/


#ifndef HASH_H
#define HASH_H
#include <string>
using namespace std;

class Hash{
public:
  Hash(string);
  int hash() const;
private:
  int key;  
};
#endif
