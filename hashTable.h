/*
  Christie Altadonna
  cha415
  PA #6
  Defining the hash table to take strings: comes from Femisters Demos
*/




#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hash.h"
#include "link.h"
#include <iostream>
#include <string>

using namespace std;

class HashTable{
public:
  HashTable(int n);
  HashTable();
  HashTable(const HashTable &t);
  ~HashTable();

  HashTable& add(string key, string value);

  bool inTable(string key) const;

  const string get(string key) const;

  void remove(string key);

private:
  int size;
  Link **table; 
	       
};

#endif
