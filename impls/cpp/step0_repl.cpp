#include <iostream>
#include <string>
using namespace std;

void pPpt() { cout << "user> "; }

void PRINT(string s) { cout << s << endl; }

string READ(string s) {
  getline(cin, s);

  return s;
}

string EVAL(string s) { return s; }

string rep() {
  string input;
  pPpt();
  PRINT(READ(EVAL(input)));

  return input;
}

int main() {
  while (true) {
    rep();
    if (cin.eof()) { // ctrl+d to quit
      break;
    }
    cin.clear();
  }

  return 0;
}
