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
vector<string>searchWord(string word);


void          Dictionary::CreateDictionary()
{

  string   file4read, file4write, line, key;
  ifstream infile, outfile;
  regex    reg("[A-Z a-z :,]+");
  char    *tok = NULL, *write = NULL;
  bool     FirstWord;

  // getline(cin, file4read);
  file4read = "dic.txt";
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
    if (regex_match(write, reg))
    {
      tok = strtok(write, ":,");

      while (tok != NULL)
      {
        if (tok[0] == ' ') tok = &tok[1];

        if (tok[strlen(tok) - 1] == ' ') tok[strlen(tok) - 1] = '\0';

        if (FirstWord)
        {
          key = tok;

          inGameDictionary.push_back(key);


          FirstWord = false;
        }
        else
        {
          Synonyms[key].push_back(tok);
          cout << tok << endl;
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
  for (size_t i = 0; i < inGameDictionary.size(); i++) {
    if (word == inGameDictionary.at(i))
    {
      return true;
    }
  }
  return false;
}

// vector<string>searchWord(string word);
