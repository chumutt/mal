#include "linenoise.hpp"
#include "printer.hpp"
#include "reader.hpp"
#include "types.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace linenoise;

Value *R(string s) { return read_str(s); }

Value *E(Value *s) { return s; }

string P(Value *s) { return pr_str(s); }

string r(string s) {
  auto ast = R(s);
  auto result = E(ast);
  return P(result);
}

int main() {
  const auto history_path = "history.txt";
  LoadHistory(history_path);
  string s;
  for (;;) {
    auto quit = Readline("user> ", s);
    AddHistory(s.c_str());
    if (quit) { // ctrl+d to quit
      break;
    }
    cout << r(s) << endl;
    cin.clear();
  }
  SaveHistory(history_path);
  return 0;
}
