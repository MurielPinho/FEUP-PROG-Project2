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
void strUpper(string &s);

int  main() {
  string word;
  Dictionary crosswords;

  vector<string> words;

//  system("clear");

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
void strUpper(string &s)
{
    for(size_t i = 0; i < s.size(); i++)
    {
        if(islower(s.at(i)))
        {
            s.at(i) = toupper(s.at(i));
        }
    }
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
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << endl;
  return opt;
}

void puzzleCreator(Dictionary& crosswords)
{
  string lcd, word;
  int lines, columns;

  cout << "--------------------------------------------------" << endl;
  cout << "CREATE PUZZLE" << endl;
  cout << "--------------------------------------------------" << endl;
  cout << "Dictionary file name ? ";
  crosswords.CreateDictionary();
  cout << "Board size (lines columns) ?" << endl;
  cin >> lines >> columns;
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  Board game(lines, columns);

  do {
    game.showBoard();
    cout << "Position ( LCD / CRTL-Z = stop ) ? ";
    getline(cin, lcd);
    cout << "Word ( - = remove / ? = help ) ? ";
    getline(cin, word);

    if (word == "-")
    {
      strUpper(word);
      game.removeWord(word, lcd);
    }
    else if (word == "?")
    {
      crosswords.showDictionary();
    }
    else
    {
      if(crosswords.VerifyWord(word))
      {
          strUpper(word);
          game.addWord(word, lcd);
      }
      else
      {
          cout << "Word does not exist" << endl;
      }
    }
  } while (!cin.eof());
}
