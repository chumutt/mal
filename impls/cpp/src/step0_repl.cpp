#include "./../linenoise.hpp"
#include <iostream>
#include <string>
using namespace std;

string R(string s) { return s; }

string E(string s) { return s; }

string P(string s) { return s; }

void p() { cout << "user> "; }

string r(string s) {
  p();
  P(R(E(s)));
  return s;
}

int main() {
  string s;
  for (;;) {
    r(s);
    if (cin.eof()) { // ctrl+d to quit
      break;
    }
    cin.clear();
  }
  return 0;
}
