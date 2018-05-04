#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;


class Board {
public:

  Board();
  void showBoard();
  bool addWord(string word, string lineReference, string colReference, string dirReference);
  bool removeWord(string word, string lineReference, string colReference, string dirReference);

private:

  int lines, columns;
  vector<string>inGameBoard;
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
