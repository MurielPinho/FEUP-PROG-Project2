#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

void setcolor(unsigned int color);
void setcolor(unsigned int color, unsigned int background_color);

class Board {
public:

  Board();  //construtor
  Board(int lin, int col); //construtor
  void showBoard(); //imprime board versao creator
  void showBoardPlayer(); //imprime board versao player
  void showAnswer(); //imprime board versao resposta
  bool addWord(string word, string Reference);
  bool removeWord(string Reference);
  void setLines(int l);
  void setColumns(int c);
  int  getLines();
  int  getColumns();
  void setInGameBoard(vector<string>b);
  vector<string> getInGameBoard();
  int  convertLetter(char l, bool upper); //conversao das coordenadas para numeros
  char convertNumber(int n, bool upper);  //conversao das coordenadas para numeros
  void writeInFile(ofstream& outfile);
  bool fullBoard();     //verifica se tabuleiro esta cheio
  void fillBoard();     //competa o tabuleiro com #
  void insertInMap(string key, string value);
  void insertInMapPlayer(string key, string value);
  void showMap();           //debug purposes
  void rewriteBoard();      //Usado na remoção de palavra para reescrever possiveis palavras desfeitas
  void convert2player();    //Converte tabuleiro para versão jogador
  map <string, string> getMap();
  map <string, string> getMapPlayer();
  bool removeWordPlayer(string Reference); //remove palavra versão player
  void rewriteBoardPlayer();    //idem ao rewriteBoard mas para jogador
  void clearMap();          //limpa o map
  void clearMapPlayer();    //limpa o map player

private:

  unsigned int lines, columns;
  vector<string>inGameBoard;
  map<string, string>addedWords;
  map<string, string>addedWordsPlayer;
};

class Dictionary {
public:

  void          CreateDictionary(ifstream& infile, string file4read); //construtor
  void          showDictionary(string Reference, int lines, int columns);
  bool          VerifyWord(string word); //Verifica se a palavra existe
  vector<string>searchWord(string word); //debug purposes
  string        strFix(string s);        //conserta headers do dicionario
  string        strLower(string s);      //conserta sinonimos
  void          setName(string name);
  string        getName();
  map <string, vector<string>> getSynonyms();

private:

  string DictionaryName;
  map<string, vector<string> >Synonyms;
  vector<string>inGameDictionary;
};

class Player {
public:
    Player();   //construtor
    Player(string name);    //construtor
    void setName(string name);
    string getName();
    void setTime(time_t begin, time_t end);
    time_t getTime();
    void setClues(unsigned int n);
    void updateClues(); //adiciona 1 ao contador de dicas
    unsigned int getClues();
    void setBoardName(string name);
    string getBoardName();
private:
    string playerName;
    unsigned int numberClues;
    time_t playTime;
    string boardName;
};
