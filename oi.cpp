// #include <string>

// #include <vector>
// #include <iostream>
// #include <fstream>
// #include <regex>
// #include "cwcreator.h"

#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
string strLower(string s);
int    main()
{
  string word;

  getline(cin, word);
  word = strLower(word);
  cout << word << endl;

  //
  // if (word == "Abdomen")
  // {
  //   cout << true << endl;
  // }
  // cout << false << endl;
  return 0;
}

string strLower(string s)
{
  bool first = true;

  for (size_t i = 0; i < s.size(); i++)
  {
    if (first) {
      if (islower(s.at(i)))
      {
        s.at(i) = toupper(s.at(i));
      }
      first = false;
    }
    else
    {
      if (isupper(s.at(i)))
      {
        s.at(i) = tolower(s.at(i));
      }
    }
  }
  return s;
}
