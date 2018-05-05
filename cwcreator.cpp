#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "cwcreator.h"

using namespace std;


void beginProgram();
int  options();
void puzzleCreator(Dictionary& crosswords);


int  main() {
  string word;
  Dictionary crosswords;

  vector<string> words;

  system("clear");

  beginProgram();


  while (true)
  {
    switch (options()) {
    case 1:

      puzzleCreator(crosswords);
      break;

    case 2:
      break;

    case 0:
      return 0;
    }
  }
  return 0;
}

void beginProgram()
{
  cout << "CROSSWORDS PUZZLE CREATOR" << endl;
  cout << "==================================================" << endl;
  cout << "INSTRUCTIONS:" << endl << " ..." << endl;
  cout << "Position ( LCD / CRTL-Z = stop )" << endl
       << " LCD stands for Line Column and Direction" << endl;
  cout << " ..." << endl << endl << " ... //TO COMPLETE" << endl << " ..." << endl;
  cout << endl << "--------------------------------------------------" << endl << endl;
}

int options()
{
  int opt;

  system("clear");
  cout <<  "OPTIONS:" << endl;
  cout << "1 - Create puzzle" << endl;
  cout << "2 - Resume puzzle" << endl;
  cout << "0 - Exit" << endl;
  cout << endl << "Option ? ";
  cin >> opt;
  cin.ignore();
  cout << endl;
  return opt;
}

void puzzleCreator(Dictionary& crosswords)
{
  string lcd, word;


  cout << "--------------------------------------------------" << endl;
  cout << "CREATE PUZZLE" << endl;
  cout << "--------------------------------------------------" << endl;
  cout << "Dictionary file name ? ";
  crosswords.CreateDictionary();
  cout << "Board size (lines columns) ?" << endl;
  Board game;

  //
  // cw.showBoard();
  // cw.addWord("muriel", "JeH");
  // cw.showBoard();


  do {
    game.showBoard();
    cout << "Position ( LCD / CRTL-Z = stop ) ? ";
    getline(cin, lcd);
    cout << "Word ( - = remove / ? = help ) ? ";
    getline(cin, word);

    if (word == "-")
    {
      game.removeWord(word, lcd);
    }
    else if (word == "?")
    {
      crosswords.showDictionary();
    }
    else
    {
      game.addWord(word, lcd);
    }
  } while (!cin.eof());
}
