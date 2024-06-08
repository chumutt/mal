#include <iostream>
#include <iterator>
#include <regex>
#include <string>
using namespace std;

string testString = "(     + 2 3 3 2 (+ 2 2  ) )";
string read_str(string s) { return s; }
string tokenize(string s) {
  regex token_regex("[\\s,]*(~@|[\[\\]{}()'`~^@]|\"(?:\\.|[^\\\"])*\"?|;.*|[^\\s\[\\]{}('\"`,;)]*)");
  regex letter_regex("(\\l+)");
  auto letters_begin = sregex_iterator(s.begin(), s.end(), letter_regex);
  auto letters_end = sregex_iterator();
  for (sregex_iterator i = letters_begin; i != letters_end; ++i)
  if (regex_search(s, token_regex))
    cout << "Text contains MAL tokens.";
  else
    cout << "Text doesn't contain any MAL tokens.";
  return 0; }

string read_form(string s) { return 0; }

string read_list(string s) { return 0; }

string read_atom(string s) { return 0; }
