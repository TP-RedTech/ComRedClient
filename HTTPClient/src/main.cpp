#include <iostream>
#include "client.h"

using namespace std;

int main(int argc, char **argv) {
  client::Client c("127.0.0.1", "5555");
  int idDoc = 3;
  int person1 = 1;
  int person2 = 2;
  auto res = c.create(person1, "TestDoc");
  cout << res.second << endl;
  res = c.connect(person1, idDoc);
  res = c.connect(person2, idDoc);
  res = c.update(person1, idDoc, 0, "a");
  cout << res.second << endl;
  res = c.update(person2, idDoc, 0, "1,b");
  res = c.update(person1, idDoc, 0, "2,c");
  res = c.update(person2, idDoc, 0, "3,d");
  res = c.getTextDocument(idDoc);
  return 0;
}