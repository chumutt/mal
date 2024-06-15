#include "reader.hpp"
#include "types.hpp"

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

  switch (token.value()[0]) {
  case '(':
    return read_list(reader);
  default:
    return read_atom(reader);
  }
}

ListValue *read_list(Reader &reader) {
  reader.next(); // consume '('
  auto *list = new ListValue{};
  // while we have tokens...
  while (auto token = reader.peek()) {
    if (*token == ")") {
      reader.next();
      break;
    }
    list->push(read_form(reader));
  }
  return list;
}

Value *read_atom(Reader &reader) { return new SymbolValue{*reader.next()}; }
