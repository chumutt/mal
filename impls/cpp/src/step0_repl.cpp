#include "linenoise.hpp"
#include <iostream>
#include <string>

std::string R(std::string s) { return s; }
std::string E(std::string s) { return s; }
std::string P(std::string s) { return s; }

std::string r(std::string s) {
  P(R(E(s)));
  return P(s);
}
int main() {
  const auto history_path = "history.txt";
  linenoise::LoadHistory(history_path);
  std::string s;
  for (;;) {
    auto quit = linenoise::Readline("user> ", s);
    linenoise::AddHistory(s.c_str());
    if (quit) { // ctrl+d to quit
      break;
    }
    std::cout << r(s) << "\n";
    std::cin.clear();
  }
  linenoise::SaveHistory(history_path);
  return 0;
}
