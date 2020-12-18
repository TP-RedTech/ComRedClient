#include "httpClient.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  client::Client c("127.0.0.1", "5555");
  cout << c.connect(3, 30).second << endl;
  cout << c.connect(1, 30).second << endl;
  return 0;
}