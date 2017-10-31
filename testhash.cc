#include "hashTable.h"

int main(int argc, char **argv){
  HashTable schools(101);
  (((schools += "Lehigh") += "Lafayette") += "DeSales") += "Kutztown";
  schools["Moravian"] = 14;
  cout << "Here is schools:\n" << schools << endl;
  HashTable otherSchools(schools);
  otherSchools["Cedar Crest"] = 14;
  schools["Alvernia"] = 29;
  cout << "Here is schools:\n" << schools << "\nHere is otherSchools:\n" << otherSchools << endl;
  cout << otherSchools["Lehigh"] << endl;
  HashTable w(300); //should crash, because non-prime table size
}


