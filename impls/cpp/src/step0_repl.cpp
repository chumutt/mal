#include "./../linenoise.hpp"
#include <iostream>
#include <string>
using namespace std;

string R(string s) { return s; }

string E(string s) { return s; }

string P(string s) { return s; }

void p() { cout << "user> "; }

string r(string s) {
  P(R(E(s)));
  return P(s);
}

int main() {
  const auto history_path = "history.txt";
  string s;
  for (;;) {
    p();
    if (!getline(cin, s)) { // ctrl+d to quit
      break;
    }
    cout << r(s) << endl;
    cin.clear();
  }
  return 0;
}
