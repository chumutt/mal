#include <iostream>
#include <string>

#include "linenoise.hpp"
#include "printer.hpp"
#include "reader.hpp"
#include "types.hpp"

Value *READ(std::string s) { return read_str(s); }

Value *EVAL(Value *s) { return s; }

std::string PRINT(Value *s) { return pr_str(s, true); }

std::string rep(std::string s) {
  auto ast = READ(s);
  auto result = EVAL(ast);
  return PRINT(result);
  try {
    auto ast = READ(s);
    auto result = EVAL(ast);
    return PRINT(result);
  } catch (ExceptionValue *exception) {
    std::cerr << std::exception->message() << std::endl;
    return "";
  }
}

int main() {
  const auto history_path = "history.txt";
  linenoise::LoadHistory(history_path);

  std::string s;
  for (;;) {
    auto quit = linenoise::Readline("user> ", s);
    if (quit) { // ctrl+d to quit
      break;
    }
    std::cout << rep(s) << "\n";
    linenoise::AddHistory(s.c_str());
  }
  linenoise::SaveHistory(history_path);

  return 0;
}
