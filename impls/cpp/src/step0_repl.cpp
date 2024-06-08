#include "./../linenoise.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace linenoise;

string R(string s) { return s; }

string E(string s) { return s; }

string P(string s) { return s; }

string r(string s) {
  P(R(E(s)));
  return P(s);
}

int main() {
  const auto history_path = "history.txt";
  LoadHistory(history_path);
  string s;
  for (;;) {
    auto quit = Readline("user> ", s);
    if (quit) { // ctrl+d to quit
      break;
      AddHistory(s.c_str());
    }
    cout << r(s) << endl;
    cin.clear();
  }
  SaveHistory(history_path);
  return 0;
}
