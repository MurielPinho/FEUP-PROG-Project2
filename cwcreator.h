#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

void setcolor(unsigned int color);
void setcolor(unsigned int color, unsigned int background_color);


class Board {
public:
  Board();
  Board(int lin, int col);
  void showBoard();
  bool addWord(string word, string Reference);
  bool removeWord(string Reference);
  void setLines(int l);
  void setColumns(int c);
  int getLines();
  int getColumns();
  void setInGameBoard(vector<string>b);
  int  convertLetter(char l, bool upper);
  char convertNumber(int n, bool upper);
  void writeInFile(ofstream& outfile);
  bool fullBoard();
  void fillBoard();
  void insertInMap(string key, string value);
  void showMap();
  void rewriteBoard();
private:
  unsigned int lines, columns;
  vector<string> inGameBoard;
  map <string, string> addedWords;

};

class Dictionary {
public:

  void          CreateDictionary(ifstream& infile, string file4read);
  void          showDictionary(string Reference, int lines, int columns);
  bool          VerifyWord(string word);
  vector<string>searchWord(string word);
  string        strFix(string s);
  string        strLower(string s);
  void          setName(string name);
  string        getName();
private:
  string DictionaryName;
  map<string, vector<string>>Synonyms;
  vector<string>inGameDictionary;
};
