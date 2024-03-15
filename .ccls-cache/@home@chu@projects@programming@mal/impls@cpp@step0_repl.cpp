#include <iostream>
#include <string>
using namespace std;

string rep() {
  cout << "user> ";
  string input;
  getline(cin, input);
  cout << endl;
  cout << input << endl;
  return input;
}

int main()
{
  while (true)
  {
    rep();
    if (cin.eof())
    {
      break;
    }
    cin.clear();
  }
  return 0;
}
