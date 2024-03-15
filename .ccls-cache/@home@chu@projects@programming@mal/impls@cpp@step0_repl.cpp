#include <iostream>
#include <string>
using namespace std;

string READ()
{
  string read = "";
  cin >> read;
  return read;
}

string EVAL()
{
  string eval = "";
  eval = READ();
  return eval;
}

string PRINT()
{
  string print = "";
  print = EVAL();
  return print;
}

string rep()
{
  string rep = "";
  rep = PRINT();
  return rep;
}

int main()
{
  string repOut = rep();
  cout << repOut << endl;

  return 0;
}
