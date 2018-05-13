#include <utility>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "cwcreator.h"

using namespace std;


void beginProgram();
int  options();
bool  puzzleCreator(Dictionary& crosswords, Board& game);
void strUpper(string &s);
bool Board2File(Dictionary crosswords, Board game);



map <string, string> addedWords;

int  main()
{
  int opt;
  string word;
  Dictionary crosswords;
  Board game;
  vector<string> words;

  beginProgram();

  opt = options();

  while(opt != 0)
  {
      if(opt == 1)
      {
          if(puzzleCreator(crosswords, game))
          {
              cin.clear();
              if(Board2File(crosswords, game))
              {
                  cout << "Board saved" << endl;
              }
              addedWords.clear();
//              cin.clear();
          }
          else
          {
              cerr << "Error opening file" << endl;
              exit(1);
          }
      }
      else if (opt == 2)
      {
          //puzzleLoad();
          cout << "de passas" << endl;
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
  string lcd, word, file4read;
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
  cout << "Board size (lines columns) ?" << endl;
  cin >> lines >> columns;
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  Board aux(lines, columns);
  game = aux;

  game.showBoard();
  /*if(Iniciar funcionalizaçao)
  {
      return 1;
  }
  else
  {
      return 2;
  }*/
//Iniciar funcionalizaçao
  while (cout << "Position ( LCD / CRTL-Z = stop ) ? ", getline(cin, lcd))
  {
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
          if(!game.addWord(word, lcd))
          {
              cout << "Word has not been added" << endl;
          }
          else
          {
              addedWords.insert(pair<string, string>(lcd, word));
          }
      }
      else
      {
          cout << "Word does not exist" << endl;
      }
    }
    game.showBoard();
  }

  if(cin.eof())
  {
      return true;
  }
//terminar funcionalizaçao
  infile.close();

}
bool Board2File(Dictionary crosswords, Board game)
{
    char aux;
    ofstream outfile;
    string file4write;

    do
    {
        cout << "Save in File (y / n) ? ";
        cin >> aux;
    } while(aux!= 'y' && aux!='n');

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(aux == 'n')
    {
        return false;
    }
    else
    {
        cout << "Save file ?";
        getline(cin, file4write);

        outfile.open(file4write);
        if (outfile.fail())
    	{
    		cerr << "Error opening file: " << file4write << endl;
    		exit(1);
    	}

        outfile << crosswords.getName() << endl << endl;

        game.writeInFile(outfile);

        for (const auto & x : addedWords)
        {
          outfile << x.first << " - " << x.second << endl;
        }
        outfile.close();
    }
    return true;
}
