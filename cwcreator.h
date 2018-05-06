#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;


class Board {
public:

  Board ();
  Board(int lin, int col);
  void showBoard();
  bool addWord(string word, string Reference);
  bool removeWord(string word, string Reference);
  void setLines(int l);
  void setColumns(int c);
  void setInGameBoard(vector<vector<char> >b);
  int  convertLetter(char l, bool upper);
  char convertNumber(int n, bool upper);

private:

  unsigned int lines, columns;
  vector<vector<char> >inGameBoard;
};

class Dictionary {
public:

  void          CreateDictionary();
  void          showDictionary();
  bool          VerifyWord(string word);
  vector<string>searchWord(string word);
  string        strFix(string s);
  string        strLower(string s);

private:

  map<string, vector<string> >Synonyms;
  vector<string>inGameDictionary;
};
