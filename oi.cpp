// #include <string>

// #include <vector>
// #include <iostream>
// #include <fstream>
// #include <regex>
#include "cwcreator.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  Board w;
  int   lin, col;

  w.showBoard();
  cout << endl;
  cin >> lin;
  cin >> col;
  Board q(lin, col);
  q.showBoard();

  return 0;


  // int lin, col;
  //
  // cin >> lin;
  // cin >> col;
  // cin.ignore();
  // vector<vector<char> > words(lin, vector<char>(col, '.'));
  // system("clear");
  // cout << "   ";
  //
  // for (int i = 97; i < col + 97; i++)
  // {
  //   cout << char(i) << " ";
  // }
  // cout << endl;
  //
  // for (int i = 0; i < lin; i++)
  // {
  //   cout << char(i + 65) << " ";
  //
  //   for (size_t j = 0; j < col; j++)
  //   {
  //     cout << " " << words.at(i).at(j);
  //   }
  //   cout << endl;
  // }
  // return 0;
}
