#pragma once
#include <string>
#include <string_view>
using namespace std;

class Tokenizer {
public:
  Tokenizer(string &input) : m_input{input} {}
  string_view next() {
    while (m_index < m_input.length()) {
      char c = m_input.at(m_index);

      switch (c) {
      case ' ':
        // TODO
        break;
      }
      ++m_index;
    }
  }

private:
  string &m_input;
  size_t m_index{0};
};

// Value *read_str(string &input) {
//   // TODO: tokenize -> ast -> return ast
// }
