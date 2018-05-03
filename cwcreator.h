#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Board {
public:

  Board();
  Board(vector<vector<string> >inGameBoard, int lines, int columns);
  void showBoard(vector<vector<string> >inGameBoard);
  bool addWord(vector<vector<string> >inGameBoard);

private:

  int lines, columns;
  vector<vector<string> >inGameBoard;
}

class Dictionary {
public:

  Dictionary();

private:
}
