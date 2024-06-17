#include <iostream>
#include <string>

#include "linenoise.hpp"
#include "printer.hpp"
#include "reader.hpp"
#include "types.hpp"

using namespace linenoise;

Value *READ(std::string s) { return read_str(s); }

Value *EVAL(Value *s) { return s; }

std::string PRINT(Value *s) { return pr_str(s); }

std::string rep(std::string s) {
  auto ast = READ(s);
  auto result = EVAL(ast);
  return PRINT(result);
}

int main() {
  const auto history_path = "history.txt";
  LoadHistory(history_path);
  std::string s;
  for (;;) {
    auto quit = Readline("user> ", s);
    AddHistory(s.c_str());
    if (quit) { // ctrl+d to quit
      break;
    }
    std::cout << rep(s) << std::endl;
    std::cin.clear();
  }
  SaveHistory(history_path);
  return 0;
}
