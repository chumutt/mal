int main() {
#include "reader.hpp"

std::vector<std::string_view> tokenize(std::string) {
  Tokenizer tokenizer{input};
  std::vector<std::string_view> vector;
  while (auto token = tokenizer.next()) {
    vector.push_back(*token);
  }
  return vector;
}

Value *read_str(std::string &input) {
  auto tokens = autotokenize(input);
  Reader reader{tokens};
  return read_form(reader);
}

Value *read_list(std::string &input) {
  auto tokens = autotokenize(input);
  Reader reader{tokens};
  return read_list(reader);
}

Value *read_form(Reader &reader) {
  auto token = reader.peek();

  if (!token)
    return nullptr;
  switch (token[0]) {}
}
return 0;
}
