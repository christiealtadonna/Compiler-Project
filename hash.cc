/*
Christie Altadonna
cha415
PA #6
Defining the hash: comes from Femisters Demos
 */

#include "hash.h"

Hash::Hash(string str) {
  int tmp = 0;
  for (int i=0; i < (int) str.length(); ++i) tmp += str[i];
  if (tmp < 0) key = -tmp; else key = tmp;
}

int Hash::hash() const{
  return key;
}

