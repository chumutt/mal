#include <iostream>
#include <string>

#include "linenoise.hpp"
#include "printer.hpp"
#include "reader.hpp"
#include "types.hpp"

using namespace std;
using namespace linenoise;

Value *READ(string s) { return read_str(s); }

Value *EVAL(Value *s) { return s; }

string PRINT(Value *s) { return pr_str(s); }

string rep(string s) {
  auto ast = READ(s);
  auto result = EVAL(ast);
  return PRINT(result);
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
    cout << rep(s) << endl;
    cin.clear();
  }
  SaveHistory(history_path);
  return 0;
}
