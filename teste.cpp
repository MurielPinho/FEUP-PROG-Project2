#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <ctime>
#include <cstdlib>
#include <windows.h>

#include "cwcreator.h"

using namespace std;

// ==========================================================================================
// COLOR CODES: (alternative: use symbolic const’s)
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

// ==========================================================================================
// Set text color
void setcolor(unsigned int color)
{
  HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);

  SetConsoleTextAttribute(hcon, color);
}

// ==========================================================================================
void clrscr(void)
{
  COORD  coordScreen = { 0, 0 }; // upper left corner
  DWORD  cCharsWritten;
  DWORD  dwConSize;
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(hCon, &csbi);
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  // fill with spaces
  FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
  GetConsoleScreenBufferInfo(hCon, &csbi);
  FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

  // cursor to upper left corner
  SetConsoleCursorPosition(hCon, coordScreen);
}

// ==========================================================================================
// Set text color & background
void setcolor(unsigned int color, unsigned int background_color)
{
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

  if (background_color == BLACK) SetConsoleTextAttribute(hCon, color);
  else SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
                               BACKGROUND_RED);
}

Board::Board()
{}

Board::Board(int lin, int col)
{
  setLines(lin);
  setColumns(col);
  vector<string> words;
  char aux[col];

  for (int i = 0; i < col; i++) {
    aux[i] = '.';
  }

  for (int i = 0; i < lin; i++) {
    words.push_back(aux);
  }
  setInGameBoard(words);
}

void Board::showBoard()
{
  cout << "   ";

  for (unsigned int i = 0; i < columns; i++)
  {
    setcolor(RED);
    cout << convertNumber(i, false) << " ";
  }
  cout << endl;

  for (unsigned int i = 0; i < lines; i++)
  {
    setcolor(RED);
    cout << convertNumber(i, true) << " ";

    for (size_t j = 0; j < columns; j++)
    {
      setcolor(BLACK, WHITE);
      cout << " " << inGameBoard.at(i).at(j);
    }
    setcolor(7);
    cout << endl;
  }
}

void Board::setLines(int l)
{
  lines = l;
}

void Board::setColumns(int c)
{
  columns = c;
}

void Board::setInGameBoard(vector<string>b)
{
  inGameBoard = b;
}

char Board::convertNumber(int n,  bool upper)
{
  char c;

  if (upper)
  {
    c = char(n + 65);
    return c;
  }
  else
  {
    c = char(n + 97);
    return c;
  }
  return '.';
}

int Board::convertLetter(char l, bool upper)
{
  if (upper)
  {
    l = int(l) - 65;
    return l;
  }
  else
  {
    l = int(l) - 97;
    return l;
  }
  return 0;
}

bool Board::addWord(string word, string Reference)
{
  unsigned int l, c;

  l = convertLetter(Reference.at(0), true);
  c = convertLetter(Reference.at(1), false);

  // Sentido ou tamanho mal-informado
  if ((Reference.at(2) != 'V') && (Reference.at(2) != 'H'))
  {
    cout << "No Direction" << endl;
    return false;
  }
  else if ((Reference.at(2) == 'V') && (word.size() + l > lines))
  {
    cout << "Word is too big" << endl;
    return false;
  }
  else if ((Reference.at(2) == 'H') && (word.size() + c > columns))
  {
    cout << "Word is too big" << endl;
    return false;
  }

  // Verifica se a posicao esta aceitavel
  if (Reference.at(2) == 'H')
  {
    for (size_t i = 0, j = c; i < word.size(); i++, j++)
    {
      if (!(((inGameBoard.at(l).at(j) == '.') || (inGameBoard.at(l).at(j) == '#')) ||
            ((inGameBoard.at(l).at(j) != '.') && (inGameBoard.at(l).at(j) != '#') &&
             (inGameBoard.at(l).at(j) == word.at(i)))))
      {
        cout << "Conflict with existing word" << endl;
        return false;
      }
    }
  }
  else
  {
    for (size_t i = 0, j = l; i < word.size(); i++, j++)
    {
      if (!(((inGameBoard.at(j).at(c) == '.') || (inGameBoard.at(j).at(c) == '#')) ||
            ((inGameBoard.at(j).at(c) != '.') && (inGameBoard.at(j).at(c) != '#') &&
             (inGameBoard.at(j).at(c) == word.at(i)))))
      {
        cout << "Conflict with existing word" << endl;
        return false;
      }
    }
  }

  if (Reference.at(2) == 'H')
  {
    // adiciona # anterior
    int aux = c;

    if ((aux - 1 >= 0) && (inGameBoard.at(l).at(aux - 1) == '.'))
    {
      inGameBoard.at(l).at(aux - 1) = '#';
    }

    // adiciona palavra
    for (size_t i = 0; i < word.size(); i++, c++)
    {
      inGameBoard.at(l).at(c) = word.at(i);
    }

    // adiciona # posterior
    if ((c < columns) && (inGameBoard.at(l).at(c) == '.'))
    {
      inGameBoard.at(l).at(c) = '#';
    }
  }
  else
  {
    // adiciona # anterior
    int aux = l;

    if ((aux - 1 >= 0) && (inGameBoard.at(aux - 1).at(c) == '.'))
    {
      inGameBoard.at(aux - 1).at(c) = '#';
    }

    // adiciona palavra
    for (size_t i = 0; i < word.size(); i++, l++)
    {
      inGameBoard.at(l).at(c) = word.at(i);
    }

    // adiciona # posterior
    if ((l < lines) && (inGameBoard.at(l).at(c) == '.'))
    {
      inGameBoard.at(l).at(c) = '#';
    }
  }
  return true;
}

bool Board::removeWord(string Reference)
{
  map<string, string>::iterator position;
  position = addedWords.find(Reference);

  if (position != addedWords.end())
  {
    addedWords.erase(Reference);
    rewriteBoard();
    return true;
  }

  return false;
}

void Board::writeInFile(ofstream& outfile)
{
  for (unsigned int i = 0; i < lines; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {
      outfile << inGameBoard.at(i).at(j);
    }
    outfile << endl;
  }

  outfile << endl;

  for (const auto& x : addedWords)
  {
    outfile << x.first << " " << x.second << endl;
  }
}

void Board::insertInMap(string key, string value)
{
  addedWords.insert(pair<string, string>(key, value));
}

void Board::showMap()
{
  for (const auto& x : addedWords)
  {
    cout << x.first << " " << x.second << endl;
  }
}

bool Board::fullBoard()
{
  unsigned int counter = 0;

  for (size_t i = 0; i < lines; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {
      if (inGameBoard.at(i).at(j) == '.')
      {
        counter++;
      }
    }
  }

  if (counter > 1)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void Board::fillBoard()
{
  for (size_t i = 0; i < lines; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {
      if (inGameBoard.at(i).at(j) == '.')
      {
        inGameBoard.at(i).at(j) = '#';
      }
    }
  }
}

void Board::rewriteBoard()
{
  string lcd, word;

  vector<string> words;
  char aux[columns];

  for (unsigned int i = 0; i < columns; i++)
  {
    aux[i] = '.';
  }

  for (unsigned int i = 0; i < lines; i++)
  {
    words.push_back(aux);
  }
  setInGameBoard(words);

  for (const auto& i : addedWords) {
    lcd  = i.first;
    word = i.second;
    addWord(word, lcd);
  }
}

void Dictionary::CreateDictionary(ifstream& infile, string file4read)
{
  string line, key, synonym;

  regex reg("[A-Za-z: ,]+");
  char *tok = NULL, *write = NULL;
  bool  FirstWord;


  while (!infile.eof())
  {
    // Conversao para char* com o objetivo de utilizar strtok
    getline(infile, line);
    write = new char[line.length() + 1];
    strcpy(write, line.c_str());
    FirstWord = true;


    // Separação de palavras simples
    if (regex_match(line, reg))
    {
      tok = strtok(write, ":,");

      while (tok != NULL)
      {
        if (tok[0] == ' ') tok = &tok[1];

        if (tok[strlen(tok) - 1] == ' ') tok[strlen(tok) - 1] = '\0';

        if (FirstWord)
        {
          key = strFix(tok);
          inGameDictionary.push_back(key);
          FirstWord = false;
        }
        else
        {
          synonym = strLower(tok);
          Synonyms[key].push_back(synonym);
        }
        tok = strtok(NULL, ":,");
      }
    }
  }
  setName(file4read);
}

void Dictionary::showDictionary(string Reference, int lines, int columns)
{
  unsigned int size;

  if (Reference.at(2) != 'H')
  {
    size = lines - ((int)Reference.at(0) - 65);
  }
  else
  {
    size = columns - ((int)Reference.at(1) - 97);
  }

  for (size_t i = 0; i < inGameDictionary.size(); i++)
  {
    if (inGameDictionary.at(i).size() <= size)
    {
      cout << inGameDictionary.at(i) << endl;
    }
  }
}

bool Dictionary::VerifyWord(string word)

{
  string temp;

  word = strFix(word);

  for (size_t i = 0; i < inGameDictionary.size(); i++) {
    temp = inGameDictionary.at(i);

    if (word == temp)
    {
      return true;
    }
  }
  return false;
}

string Dictionary::strFix(string s)
{
  bool first = true;

  for (size_t i = 0; i < s.size(); i++)
  {
    if (first) {
      if (islower(s.at(i)))
      {
        s.at(i) = toupper(s.at(i));
      }
      first = false;
    }
    else
    {
      if (isupper(s.at(i)))
      {
        s.at(i) = tolower(s.at(i));
      }
    }
  }
  return s;
}

string Dictionary::strLower(string s)
{
  for (size_t i = 0; i < s.size(); i++)
  {
    if (isupper(s.at(i)))
    {
      s.at(i) = tolower(s.at(i));
    }
  }
  return s;
}

vector<string>Dictionary::searchWord(string word)
{
  vector<string> words;
  int flag = 0;

  for (size_t i = 0; i < inGameDictionary.size(); i++)
  {
    if (inGameDictionary.at(i).size() >= word.size())
    {
      for (size_t j = 0; j < word.size(); j++)
      {
        for (size_t k = 0; k < inGameDictionary.at(i).size(); k++)
        {
          if (tolower(word.at(j)) == tolower(inGameDictionary.at(i).at(k)))
          {
            flag = 1;
            k    = inGameDictionary.at(i).size();
          }
          else
          {
            flag = 0;
          }
        }

        if (flag == 0)
        {
          j = word.size();
        }
      }

      if (flag != 0)
      {
        words.push_back(inGameDictionary.at(i));
      }
    }
  }

  for (size_t i = 0; i < words.size(); i++)
  {
    cout << words.at(i) << endl;
  }
  return words;
}

void Dictionary::setName(string name)
{
  DictionaryName = name;
}

string Dictionary::getName()
{
  return DictionaryName;
}

int Board::getLines()
{
  return lines;
}

int Board::getColumns()
{
  return columns;
}
