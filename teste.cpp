#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include "cwcreator.h"

using namespace std;


void          beginProgram();
int           options();
void          CreateDictionary();
void          puzzleCreator();
bool          VerifyWord(string word);
string        strFix(string s);
string        strLower(string s);
void          showBoard();
void          setLines(int l);
void          setColumns(int c);
void          setInGameBoard(vector<vector<char> >b);
bool          addWord(string word);
bool          removeWord(string word, string Reference);
int           convertLetter(char l, bool upper);
char          convertNumber(int n,  bool upper);
vector<string>searchWord(string word);

void          Dictionary::CreateDictionary()
{
  string   file4read, file4write, line, key, synonym;
  ifstream infile, outfile;
  regex    reg("[A-Za-z: ,]+");
  char    *tok = NULL, *write = NULL;
  bool     FirstWord;

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

  infile.close();
}

void Dictionary::showDictionary()
{
  for (size_t i = 0; i < inGameDictionary.size(); i++)
  {
    cout << inGameDictionary.at(i) << endl;
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

Board::Board()
{
    lines = 2;
    columns = 2;
    vector<vector<char> > words(lines, vector<char>(columns, '.'));
    setInGameBoard(words);
}


Board::Board(int lin, int col)
{
  setLines(lin);
  setColumns(col);
  vector<vector<char> > words(lin, vector<char>(col, '.'));
  setInGameBoard(words);
}

void Board::showBoard()
{
  //system("clear");
  cout << "   ";

  for (unsigned int i = 0; i < columns; i++)
  {
    cout << convertNumber(i, false) << " ";
  }
  cout << endl;

  for (unsigned int i = 0; i < lines; i++)
  {
    cout << convertNumber(i, true) << " ";

    for (size_t j = 0; j < columns; j++)
    {
      cout << " " << inGameBoard.at(i).at(j);
    }
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

void Board::setInGameBoard(vector<vector<char> >b)
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
  int  l, c;
  bool v;

  l = convertLetter(Reference.at(0), true);
  c = convertLetter(Reference.at(1), false);

  if (Reference.at(2) == 'V')
  {
    v = 1;
  }
  else
  {
    v = 0;
  }

  if (v)
  {
    if (l + word.size() <= lines)
    {
      if (l - 1 >= 0)
      {
        inGameBoard.at(l - 1).at(c) = '#';
      }

      for (size_t i = l; i < word.size() + l; i++)
      {
        inGameBoard.at(i).at(c) = word.at(i - l);
      }

      if (l + word.size() != lines)
      {
        inGameBoard.at(l + word.size()).at(c) = '#';
      }
    }
    else
    {
      cout << "Deu ruim" << endl;
    }
  }
  else
  {
    if (c + word.size() <= columns)
    {
      if (c - 1 >= 0)
      {
        inGameBoard.at(l).at(c - 1) = '#';
      }

      for (size_t i = c; i < word.size() + c; i++)
      {
        inGameBoard.at(l).at(i) = word.at(i - c);
      }

      if (c + word.size() != columns)
      {
        inGameBoard.at(l).at(c + word.size()) = '#';
      }
    }
    else
    {
      cout << "Deu ruim" << endl;
    }
  }


  return true;
}

bool Board::removeWord(string word, string Reference)
{
  int  l, c;
  bool v;

  l = convertLetter(Reference.at(0), true);
  c = convertLetter(Reference.at(1), false);

  if (Reference.at(2) == 'V')
  {
    v = 1;
  }
  else
  {
    v = 0;
  }

  if (inGameBoard.at(l).at(c) != '.')
  {
    if (v)
    {
      if (inGameBoard.at(l).at(l - 2) == '.') {
        inGameBoard.at(l - 1).at(c) = '.';
      }
      int i = l;

      while (inGameBoard.at(i).at(c) != '#')
      {
        if ((inGameBoard.at(i).at(c - 1) == '.') && (inGameBoard.at(i).at(c + 1) == '.'))
        {
          inGameBoard.at(i).at(c) = '.';
        }
        i++;
      }
      inGameBoard.at(i).at(c) = '.';
    }
    else
    {
      if (inGameBoard.at(l).at(c - 2) == '.') {
        inGameBoard.at(l).at(c - 1) = '.';
      }
      int i = c;

      while (inGameBoard.at(l).at(i) != '#')
      {
        if ((inGameBoard.at(l - 1).at(i) == '.') && (inGameBoard.at(l + 1).at(i) == '.'))
        {
          inGameBoard.at(l).at(i) = '.';
        }
        i++;
      }
      inGameBoard.at(l).at(i) = '.';
    }
  }

  return true;
}
