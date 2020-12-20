#include <iostream>
#include "client.h"

using namespace std;

int main(int argc, char **argv) {
  client::Client c("127.0.0.1", "5555");
  int idDoc = 10;
  int person1 = 1;
  int person2 = 2;
  cout << c.create(person1, "TestDoc").second << endl;
//  c.connect(person1, idDoc);
//  c.connect(person2, idDoc);
//  c.update(person1, idDoc, 0, "a");
//  c.update(person2, idDoc, 0, "1,b");
//  c.update(person1, idDoc, 0, "2,c");
//  c.update(person2, idDoc, 0, "3,d");
//  string res = c.getTextDocument(idDoc).second;
//  cout << res << endl;
  return 0;
}