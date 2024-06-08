#include <iostream>
#include <string>
using namespace std;
string symbol;
string number;
string list;

string pr_str(string s) {
  if (s == symbol) {
    cout << "symbol!\n";
  } else if (s == number) {
    cout << "number!\n";
  } else if (s == list) {
    cout << "list!\n";
  }
  return s;
}
