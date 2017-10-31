/*
  Christie Altadonna
  cha415
  PA #6
  Defining the link class to take strings not doubles: comes from Femisters Demos
*/




#ifndef LINK_H
#define LINK_H

#include <string>
using namespace std;

class Link{
public:
  const string key;
  string data;  //the actual information
  Link *next;

  Link(const string key, string data, Link *next);

};
#endif
