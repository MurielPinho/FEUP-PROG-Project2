#include <string>
#include <vector>
#include <iostream>
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

  Dictionary();
  void          showDictionary();
  bool          VerifyWord(string word);
  vector<string>searchWord(string word);

private:

  vector<string>inGameDictionary;
  vector<vector<string> >Synonyms;
};
