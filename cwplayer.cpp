#include <utility>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <ctime>
#include <random>
#include <chrono>
#include <cctype>
#include <sstream>
#include <iomanip>

#include "cwcreator.h"

using namespace std;

bool beginGame(Dictionary crosswords, Board game, Board& player, Player& playerStats);
void configurePlayer(Player& playerStats);
void puzzleLoad(Dictionary& crosswords, Board& game, Player& playerStats);
void initialClues(Dictionary crosswords, Board game);
string showOneClue(Dictionary crosswords, Board game, string reference);
void strUpper(string& s);
string strLowerSpecial(string s);
bool wordControl(Dictionary crosswords, Board& game, Board original, Player& playerStats);
bool verifyInput(string Reference);
int verifySize(string lcd, string word, Board original);
bool verifyPosition(string lcd, Board original);
void player2file(Player& playerStats);
bool CompareMaps(const map<string, string>& l, const map<string, string>& r);


string fileName;


int main()
{
    Dictionary crosswords;
    Board game, player;
    Player playerStats;
    char control;
    configurePlayer(playerStats);
    do
    {
        puzzleLoad(crosswords, game, playerStats);
        if(beginGame(crosswords, game, player, playerStats))
        {
            cout << "CONGRATULATIONS!!!" << endl;
            player2file(playerStats);
            cout << "Check your stats at: " << fileName << "_p.txt" << endl;
            fileName = "";
        }
        else
        {
            cout << "Nice try" << endl << "The answer was:" << endl;
            game.showAnswer();
            cout << "Your answer was: " << endl;
            player.showBoardPlayer();
            player.clearMap();
            player.clearMapPlayer();
            game.clearMap();
            game.clearMapPlayer();
        }

        cout << "Play again (y / n) ? ";
        cin >> control;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (control != 'n');

    return 0;
}

bool beginGame(Dictionary crosswords, Board game, Board& player, Player& playerStats)
{
    string name;
    time_t b, e;

    b = time(0);
    player = game;
    player.convert2player();
    playerStats.setClues(0);
    //show initial clues
    initialClues(crosswords, game);
    if (wordControl(crosswords, player, game, playerStats))
    {
        e = time(0);
        playerStats.setTime(b, e);
        return true;
    }

    return false;

}

void configurePlayer(Player& playerStats)
{
    string name;

    cout << "CROSSWORDS PUZZLE" << endl;
    cout << "==================================================" << endl;
    cout << "What's your name?" << endl;
    getline(cin, name);
    playerStats.setName(name);
}

void puzzleLoad(Dictionary& crosswords, Board& game, Player& playerStats)
{
    int troca = 0, l, board;
    ostringstream boardNumber, name;
    ifstream infile, dictionaryInfile, numInfile;
    string file4read, line, word, key, number;
    vector<string> aux;

    cout << "Please choose a Board ? " ;
    cin >> board;
    boardNumber << "B";
    boardNumber << setfill('0') << setw(3) << to_string(board) << ".txt";
    name << "B" << setfill('0') << setw(3) << to_string(board);
    fileName = name.str();
    file4read = boardNumber.str();
    infile.open(file4read);
    if(infile.fail())
    {
        cerr << "Error opening board" << endl;
        exit(1);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (!infile.eof())
    {
        getline(infile, line);
        if (line ==  "")
        {
            ++troca;
        }
        else if(troca == 0)
        {
            string name;
            crosswords.setName(line);
            name = crosswords.getName();
            dictionaryInfile.open(name);
            if(infile.fail())
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
            key = line.substr(0,3);
            l = line.find(" ");
            l = l + 1;
            word = line.substr(l);
            game.insertInMap(key, word);
        }
    }
    game.setLines(aux.size());
    game.setColumns(aux.at(0).size());
    game.setInGameBoard(aux);
    infile.close();
}

bool wordControl(Dictionary crosswords, Board& game, Board original, Player& playerStats)
{
    string lcd, word;

    game.showBoardPlayer();
    while (cout << "Position ( LCD = / CRTL-Z = finish ) ? ", getline(cin, lcd))
    {
      cout << "Word ( - = remove / ? = new clue ) ? ";
      getline(cin, word);
      if (verifyInput(lcd) && verifyPosition(lcd, original))
      {

        if (word == "-")
        {
            if(verifySize(lcd, word, original))
            {
                if (!game.removeWordPlayer(lcd))
                {
                  cout << "Couldn't find word " << endl;
                }
            }
        }
        else if (word == "?")
        {
          playerStats.updateClues();
          cout << "New clue: ";
          cout << showOneClue(crosswords, game, lcd) << endl;
        }
        else
        {
          if(crosswords.VerifyWord(word))
          {
              strUpper(word);
              if(verifySize(lcd, word, original))
              {
                  cout << "Invalid word" << endl;
              }
              else
              {
                  if(!game.addWord(word, lcd))
                  {
                      cout << "Word has not been added" << endl;
                  }
                  else
                  {
                      game.insertInMapPlayer(lcd, word);
                  }
              }
          }
          else
          {
              cout << "Word does not exist" << endl;
          }
        }
      }
      else
      {
        cout << "Invalid input" << endl;
      }
      game.showBoardPlayer();
    }

    if (cin.eof())
    {
      cin.clear();
      if (CompareMaps(game.getMapPlayer(), original.getMap()))
      {
        return true;
      }
    }
    return false;

}

void initialClues(Dictionary crosswords, Board game)
{
    unsigned int clue;
    vector<string> horizontal, vertical;
    map <string, string> references = game.getMap();
    map <string, vector<string>> synonyms = crosswords.getSynonyms();
    map<string, vector<string>>::iterator aux;
    string key, toAdd, coordX, coordY;

    for(map<string, string>::iterator it = references.begin(); it != references.end(); ++it)
    {
        key = it->second;
        key = strLowerSpecial(key);
        aux = synonyms.find(key);
        srand((unsigned int)time(0));
        clue = rand () % aux->second.size();

        if(aux != synonyms.end())
        {
            if(it->first.at(2)=='H')
            {
                coordX = it->first.at(0);
                coordY = it->first.at(1);
                toAdd = coordX + coordY + " " + aux->second.at(clue);
                horizontal.push_back(toAdd);
            }
            else
            {
                coordX = it->first.at(0);
                coordY = it->first.at(1);
                toAdd = coordX + coordY + " " + aux->second.at(clue);
                vertical.push_back(toAdd);
            }
        }
    }
    if (horizontal.size() != 0)
    {
        cout << "HORIZONTAL CLUES:" << endl;
        for (size_t i = 0; i < horizontal.size(); i++) {
            cout << horizontal.at(i) << endl;
        }
    }
    if(vertical.size() != 0)
    {
        cout << endl << "VERTICAL CLUES:" << endl;
        for (size_t i = 0; i < vertical.size(); i++) {
            cout << vertical.at(i) << endl;
        }
    }

}

string showOneClue(Dictionary crosswords, Board game, string reference)
{
    unsigned int clue;
    map <string, string> references = game.getMap();
    map <string, vector<string>> synonyms = crosswords.getSynonyms();
    map<string, vector<string>>::iterator aux;
    string key1, key2;

    for(map<string, string>::iterator it = references.begin(); it != references.end(); ++it)
    {
        key1 = it->first;
        key2 = it->second;
        key2 = strLowerSpecial(key2);
        aux = synonyms.find(key2);
        srand((unsigned int)time(0));
        clue = rand () % aux->second.size();

        if(aux != synonyms.end() && reference == key1)
        {
            return aux->second.at(clue);
        }
    }
    return "";
}

string strLowerSpecial(string s)
{
    for (size_t i = 1; i < s.size(); i++)
    {
      if (isupper(s.at(i)))
      {
        s.at(i) = tolower(s.at(i));
      }
    }
    return s;
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

int verifySize(string lcd, string word, Board original)
{
    map <string, string> references = original.getMap();
    string key;

    for(map<string, string>::iterator it = references.begin(); it != references.end(); ++it)
    {
        if(lcd == it->first)
        {
            key = it->second;
            if(key.size() != word.size())
            {
                return true;
            }
        }
    }
    return 0;
}

bool verifyPosition(string lcd, Board original)
{
    map <string, string> references = original.getMap();

    for(map<string, string>::iterator it = references.begin(); it != references.end(); ++it)
    {
        if(lcd == it->first)
        {
            return true;
        }
    }
    return false;

}

void player2file(Player& playerStats)
{
    string file4write = fileName + "_p.txt";
    ofstream outfile(file4write, ios_base::app | ios_base::out);

    if (outfile.fail())
    {
      cerr << "Error opening file" << endl;
      exit(1);
    }

    outfile << "Name: " << playerStats.getName() << " | Number of Clues used: " << playerStats.getClues() << " | Time (in seconds): " <<  playerStats.getTime() << endl;

    outfile.close();
}

bool CompareMaps(const map<string, string>& l, const map<string, string>& r)
{
  if(l.size() != r.size())
    return false;

  map<string, string>::const_iterator i, j;
  for(i = l.begin(), j = r.begin(); i != l.end(); ++i, ++j)
  {
    if((i->first != j->first) || (i->second != j->second))
      return false;
  }

  return true;
}
