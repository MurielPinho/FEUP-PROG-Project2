#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "cwcreator.h"

using namespace std;


void beginProgram();
int  options();
void puzzleCreator();

int  main() {
  beginProgram();
  Dictionary j;
  j.CreateDictionary();

  // j.showDictionary();

  // while (true)
  // {
  //   switch (options()) {
  //   case 1:
  //     puzzleCreator();
  //     break;
  //
  //   case 2:
  //     break;
  //
  //   case 0:
  //     return 0;
  //   }
  // }
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
  cout << endl << "--------------------------------------------------" << endl;
  cout << endl << "OPTIONS:" << endl;
  cout << "1 - Create puzzle" << endl;
  cout << "2 - Resume puzzle" << endl;
  cout << "0 - Exit" << endl;
}

int options()
{
  int opt;

  cout << endl << "Option ? ";

  cin >> opt;

  return opt;
}

//
// void puzzleCreator()
// {
//   Board  game;
//   string lcd, word;
//
//   cout << endl << "--------------------------------------------------" << endl;
//   cout << "CREATE PUZZLE" << endl;
//   cout << "--------------------------------------------------" << endl;
//
//   do {
//     game.showBoard();
//     cout << "Position ( LCD / CRTL-Z = stop ) ? ";
//     getline(cin, lcd);
//     cout << "Word ( - = remove / ? = help ) ? ";
//     getline(cin, word);
//
//     if (word == "-")
//     {
//       game.removeWord(word, lcd.at(0), lcd.at(1), lcd.at(2));
//     }
//     else if (word == "?")
//     {
//       game.showDictionary();
//     }
//     else
//     {
//       game.addWord(word, lcd.at(0), lcd.at(1), lcd.at(2));
//     }
//   } while (!cin.eof());
// }
