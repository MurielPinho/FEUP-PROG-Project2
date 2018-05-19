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
  void showBoardPlayer();
  void showAnswer();
  bool addWord(string word, string Reference);
  bool removeWord(string Reference);
  void setLines(int l);
  void setColumns(int c);
  int  getLines();
  int  getColumns();
  void setInGameBoard(vector<string>b);
  vector<string> getInGameBoard();
  int  convertLetter(char l, bool upper);
  char convertNumber(int n, bool upper);
  void writeInFile(ofstream& outfile);
  bool fullBoard();
  void fillBoard();
  void insertInMap(string key, string value);
  void insertInMapPlayer(string key, string value);
  void showMap();
  void rewriteBoard();
  void convert2player();
  map <string, string> getMap();
  map <string, string> getMapPlayer();
  bool removeWordPlayer(string Reference);
  void rewriteBoardPlayer();
  void clearMap();
  void clearMapPlayer();

private:

  unsigned int lines, columns;
  vector<string>inGameBoard;
  map<string, string>addedWords;
  map<string, string>addedWordsPlayer;
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
  map <string, vector<string>> getSynonyms();

private:

  string DictionaryName;
  map<string, vector<string> >Synonyms;
  vector<string>inGameDictionary;
};

class Player {
public:
    Player();
    Player(string name);
    void setName(string name);
    string getName();
    void setTime(time_t begin, time_t end);
    time_t getTime();
    void setClues(unsigned int n);
    void updateClues();
    unsigned int getClues();
    void setBoardName(string name);
    string getBoardName();
private:
    string playerName;
    unsigned int numberClues;
    time_t playTime;
    string boardName;
};
