#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "cwcreator.h"

using namespace std;


void          beginProgram();
int           options();
void          puzzleCreator();
Dictionary();
bool          VerifyWord(string word);
vector<string>searchWord(string word);

int           main() {
  beginProgram();

  while (true)
  {
    switch (options()) {
    case 1:
      puzzleCreator();
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

void puzzleCreator()
{
  Board  game;
  string lcd, word;

  cout << endl << "--------------------------------------------------" << endl;
  cout << "CREATE PUZZLE" << endl;
  cout << "--------------------------------------------------" << endl;

  do {
    game.showBoard();
    cout << "Position ( LCD / CRTL-Z = stop ) ? ";
    getline(cin, lcd);
    cout << "Word ( - = remove / ? = help ) ? ";
    getline(cin, word);

    if (word == "-")
    {
      game.removeWord(word, lcd.at(0), lcd.at(1), lcd.at(2));
    }
    else if (word == "?")
    {
      game.showDictionary();
    }
    else
    {
      game.addWord(word, lcd.at(0), lcd.at(1), lcd.at(2));
    }
  } while (!cin.eof());
}

Dictionary::Dictionary()
{
  string   file4read;
  ifstream infile;
  regex    reg("[A-Z a-z :,]+");
  char    *tok = NULL, *write = NULL;

  getline(cin, file4read);
  infile.open(file4read);

  if (infile.fail())
  {
    cerr << "Error opening file: " << file4read << endl;
    exit(1);
  }

  while (!infile.eof())
  {
    // Conversao para char* com o objetivo de utilizar strtok
    getline(infile, line);
    write = new char[line.length() + 1];
    strcpy(write, line.c_str());

    // Separação de palavras simples
    if (regex_match(write, reg))
    {
      tok = strtok(write, ":");

      while (tok != NULL)
      {
        if (tok[0] == ' ') tok = &tok[1];

        if (tok[strlen(tok) - 1] == ' ') tok[strlen(tok) - 1] = '\0';


        tok = strtok(NULL, ":");
      }
    }
  }
}

bool          VerifyWord(string word);
vector<string>searchWord(string word);
