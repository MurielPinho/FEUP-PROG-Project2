#include <utility>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <regex>
#include <sstream>
#include "cwcreator.h"

using namespace std;


void beginProgram();
int  options();
bool puzzleCreator(Dictionary& crosswords, Board& game);
string puzzleLoad(Dictionary& crosswords, Board& game);
void strUpper(string& s);
bool Board2File(Dictionary crosswords, Board game);
bool ReBoard2File(Dictionary crosswords, Board game, string name);
bool wordControl(Dictionary crosswords, Board& game);
char resumeOrFinish();
bool verifyInput(string Reference);


int  main()
{
  int opt;
  string word;
  Dictionary crosswords;
  Board game;

  vector<string> words;

  beginProgram();

  opt = options();

  while (opt != 0)
  {
    if (opt == 1)
    {
      if (puzzleCreator(crosswords, game))
      {
        cin.clear();

        if (Board2File(crosswords, game))
        {
          cout << "Board saved" << endl;
        }
      }
      else
      {
        cerr << "Error opening file" << endl;
        exit(1);
      }
    }
    else if (opt == 2)
    {
      word = puzzleLoad(crosswords, game);

      if (!wordControl(crosswords, game))
      {
        cout << "Board Full" << endl;
      }
      else
      {
        cin.clear();
      }

      if (ReBoard2File(crosswords, game, word))
      {
        cout << "Board saved" << endl;
      }
    }
    else
    {
      cout << "Invalid option" << endl;
    }
    opt = options();
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

void strUpper(string& s)
{
  for (size_t i = 0; i < s.size(); i++)
  {
    if (islower(s.at(i)))
    {
      s.at(i) = toupper(s.at(i));
    }
  }
}

int options()
{
  int opt;

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

bool puzzleCreator(Dictionary& crosswords, Board& game)
{
  string   lcd, word, file4read;
  ifstream infile;
  int lines, columns;

  cout << "--------------------------------------------------" << endl;
  cout << "CREATE PUZZLE" << endl;
  cout << "--------------------------------------------------" << endl;
  cout << "Dictionary file name ? ";

  getline(cin, file4read);

  infile.open(file4read);

  if (infile.fail())
  {
    return false;
  }

  crosswords.CreateDictionary(infile, file4read);

  do {
    cout << "Board size (lines columns) ? " << endl;
    cin >> lines >> columns;
  } while (lines < 1 || lines > 26 || columns < 1 || columns > 26);
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  Board aux(lines, columns);
  game = aux;

  if (wordControl(crosswords, game))
  {
    return true;
  }
  else
  {
    cout << "Board is Full" << endl;
    return true;
  }
  infile.close();
  return true;
}

bool Board2File(Dictionary crosswords, Board game)
{
  char aux;
  int  gamesNumber;
  ifstream infile;
  ofstream outfile;
  string   file4write, strGamesNumber;
  ostringstream boardNumber;

  infile.open("GamesNumber.txt");

  do
  {
    cout << "Save in File (y / n) ? ";
    cin >> aux;
  } while (aux != 'y' && aux != 'n');

  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if (aux == 'n')
  {
    return false;
  }
  else
  {
    if (infile.fail())
    {
      cerr << "Error opening file" << endl;
      exit(1);
    }
    getline(infile, strGamesNumber);
    gamesNumber = stoi(strGamesNumber);
    gamesNumber++;
    outfile.open("GamesNumber.txt");
    outfile << gamesNumber;
    outfile.close();
    boardNumber << "B";
    boardNumber << setfill('0') << setw(3) << to_string(gamesNumber) << ".txt";
    file4write = boardNumber.str();
    outfile.open(file4write);

    if (outfile.fail())
    {
      cerr << "Error opening file" << endl;
      exit(1);
    }

    outfile << crosswords.getName() << endl << endl;

    game.writeInFile(outfile);

    outfile.close();
  }
  return true;
}

bool ReBoard2File(Dictionary crosswords, Board game, string name)
{
  char aux;
  int  gamesNumber;
  ifstream infile;
  ofstream outfile;
  string   file4write, strGamesNumber;
  ostringstream boardNumber;

  do
  {
    cout << "Save in File (y / n) ? ";
    cin >> aux;
  } while (aux != 'y' && aux != 'n');

  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if (aux == 'n')
  {
    return false;
  }
  else
  {
    file4write = name;
    outfile.open(file4write);

    if (outfile.fail())
    {
      cerr << "Error opening file" << endl;
      exit(1);
    }

    outfile << crosswords.getName() << endl << endl;

    game.writeInFile(outfile);

    outfile.close();
  }
  return true;
}

string puzzleLoad(Dictionary& crosswords, Board& game)
{
  int troca = 0, l;
  ifstream infile, dictionaryInfile;
  string   file4read, line, word, key;

  vector<string> aux;


  cout << "Load File ? ";
  getline(cin, file4read);

  infile.open(file4read);

  if (infile.fail())
  {
    cerr << "Error opening file" << endl;
    exit(1);
  }

  while (!infile.eof())
  {
    getline(infile, line);

    if (line ==  "")
    {
      ++troca;
    }
    else if (troca == 0)
    {
      string name;
      crosswords.setName(line);
      name = crosswords.getName();
      dictionaryInfile.open(name);

      if (infile.fail())
      {
        cerr << "Error opening file: " << name << endl;
        exit(1);
      }
      crosswords.CreateDictionary(dictionaryInfile, name);
    }
    else if (troca == 1)
    {
      aux.push_back(line);
    }
    else if (troca == 2)
    {
      key  = line.substr(0, 3);
      l    = line.find(" ");
      l    = l + 1;
      word = line.substr(l);
      game.insertInMap(key, word);
    }
  }
  game.setLines(aux.size());
  game.setColumns(aux.at(0).size());
  game.setInGameBoard(aux);
  infile.close();

  return file4read;
}

bool wordControl(Dictionary crosswords, Board& game)
{
  string lcd, word;

  game.showBoard();

  while (cout << "Position ( LCD / CRTL-Z = stop ) ? ", getline(cin, lcd))
  {
    cout << "Word ( - = remove / ? = help ) ? ";
    getline(cin, word);

    if (verifyInput(lcd))
    {
      if (word == "-")
      {
        if (!game.removeWord(lcd))
        {
          cout << "Couldn't find word " << endl;
        }
      }
      else if (word == "?")
      {
        crosswords.showDictionary(lcd, game.getLines(), game.getColumns());
      }
      else
      {
        if (crosswords.VerifyWord(word))
        {
          strUpper(word);

          if (!game.addWord(word, lcd))
          {
            cout << "Word has not been added" << endl;
          }
          else
          {
            game.insertInMap(lcd, word);
          }
        }
        else
        {
          cout << "Word does not exist" << endl;
        }
      }

      if (game.fullBoard())
      {
        return false;
      }

    }
    else
    {
      cout << "Invalid input" << endl;
    }
    game.showBoard();
  }

  if (cin.eof())
  {
    cin.clear();

    if (resumeOrFinish() == 'f')
    {
      game.fillBoard();
    }
    return true;
  }

  return false;
}

char resumeOrFinish()
{
  char aux;

  do {
    cout << "Save for later or Finish (s / f) ? ";
    cin >> aux;
  } while (aux != 's' && aux != 'f');

  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');


  return aux;
}

bool verifyInput(string Reference)
{
  char l, c;

  l = Reference.at(0);
  c = Reference.at(1);

  if ((l >= 'A') && (l <= 'Z'))
  {
    if ((c >= 'a') && (c <= 'z'))
    {
      return true;
    }
  }
  return false;
}
