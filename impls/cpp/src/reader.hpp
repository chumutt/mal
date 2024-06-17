#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "types.hpp"

class Tokenizer {
public:
  Tokenizer(std::string &input) : m_input{input} {}

  std::optional<std::string_view> next() {
    auto view = std::string_view(m_input);

    while (m_index < m_input.length()) {
      char c = m_input.at(m_index);

      switch (c) {
      case ' ':  // space
      case '\t': // tab
      case '\n': // new line
      case ',':  // comma
        ++m_index;
        break;
      case '~': {
        ++m_index;
        if (m_index + 1 < m_input.length() && m_input.at(m_index + 1) == '@') {
          ++m_index;
          return view.substr(m_index - 2, 2);
        }
        return view.substr(m_index - 1, 1);
      }
      case '[':  // open bracket
      case ']':  // closed bracket
      case '{':  // open curly
      case '}':  // closed curly
      case '(':  // open paren
      case ')':  // closed paren
      case '\'': // single quote
      case '`':  // backtick
      case '^':  // caret
      case '@':
        return view.substr(m_index++, 1);
      case '"': {
        size_t start = m_index;
        ++m_index;
        while (m_index < m_input.length()) {
          c = m_input.at(m_index);
          switch (c) {
          case '"':
            ++m_index;
            return view.substr(start, m_index - start);
          case '\\':
            ++m_index;
            break;
          }
          ++m_index;
        }
        // If no ending double quote to pair with first double quote,
        // return whatever is left & EOF.
        std::cout << "EOF\n";
        return view.substr(start, m_index - start);
      }
      case ';': {
        size_t start = m_index;
        while (m_index < m_input.length()) {
          c = m_input.at(m_index);
          if (c == '\n')
            break;
          ++m_index;
        }
        return view.substr(start, m_index - start);
      }
      default: {
        size_t start = m_index;
        bool done = false;
        while (!done && m_index < m_input.length()) {
          c = m_input.at(m_index);
          switch (c) {
          case ' ':  // space
          case '\t': // tab
          case '\n': // new line
          case '[':
          case ']':
          case '{':
          case '}':
          case '(':
          case ')':
          case '\'':
          case '"':
          case '`':
          case ',':
          case ';':
            done = true;
            break;
          default:
            ++m_index;
          }
        }
        return view.substr(start, m_index - start);
      }
      }
    }
    return {}; // return nothing if no token (a.k.a. why 'optional<string_view>
               // next()...' is necessary).
  }

private:
  std::string &m_input;
  size_t m_index{0};
};

class Reader {
public:
  Reader(std::vector<std::string_view> &tokens) : m_tokens{tokens} {}

  std::optional<std::string_view> next() {
    if (m_index < m_tokens.size())
      return m_tokens.at(m_index++);
    return {};
  }

  std::optional<std::string_view> peek() {
    if (m_index < m_tokens.size())
      return m_tokens.at(m_index);
    return {};
  }

private:
  std::vector<std::string_view> &m_tokens;
  size_t m_index{0};
};

Value *read_str(std::string &input);

Value *read_form(Reader &reader);

Value *read_quoted_value(Reader &reader);

Value *read_with_meta(Reader &reader);

ListValue *read_list(Reader &reader);

ListValue *read_vector(Reader &reader);

HashMapValue *read_hash_map(Reader &reader);

Value *read_atom(Reader &reader);
