#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>

using namespace std;

// Funcoes
// ==============================================================
// Contagem do numero de palavras
void counter(int v[], int  n, char c);

// ==============================================================
// Impressao de ponto a cada 100 palavras
void dots(int v[], int  n, char c);

// ==============================================================
// Converter letra em numero
int letter(char c);

// ==============================================================
// Verificar Duplicadas
bool duplicate(const string word, const vector<string>lista);

int  main()
{
  vector<vector<string> > words(26, vector<string>(0));
  string   file4read, file4write, line;
  ifstream infile;
  ofstream outfile;
  char    *tok = NULL, *write = NULL;
  int dup = 0, contador[26] = { 0 }, tot = 0;

  // regex reg("[A-Z ;'-]+");

  regex reg("[A-Z a-z,:]+");
  regex reg2("(.*[- '].*)+");
  system("clear");

  // Impressao interface inicial
  cout << "EXTRACTION OF WORD LIST FROM DICTIONARY" << endl;
  cout << "=======================================" << endl;
  cout << "\nDictionary file ? ";
  getline(cin, file4read);
  cout << "Word list file ? ";
  getline(cin, file4write);
  cout << "\nExtracting simple word files from file " << file4read << "," << endl;
  cout << "beginning with letter ..." << endl;

  // Abertura de arquivos
  infile.open(file4read);
  outfile.open(file4write);

  // Verificação de abertura
  if (infile.fail())
  {
    cerr << "Error opening file: " << file4read << endl;
    exit(1);
  }

  if (outfile.fail())
  {
    cerr << "Error opening file: " << file4write << endl;
    exit(1);
  }

  // Separação de headlines
  while (!infile.eof())
  {
    // Conversao para char* com o objetivo de utilizar strtok
    getline(infile, line);
    write = new char[line.length() + 1];
    strcpy(write, line.c_str());

    // Separação de palavras simples
    if (regex_match(write, reg))
    {
      tok = strtok(write, ": ,");

      while (tok != NULL)
      {
        if (tok[0] == ' ') tok = &tok[1];

        if (tok[strlen(tok) - 1] == ' ') tok[strlen(tok) - 1] = '\0';

        if (!regex_match(tok, reg2))
        {
          // Contagem das palavras
          counter(contador, 25, tok[0]);

          // Impressao de ponto a cada 100 palavras
          dots(contador, 25, tok[0]);

          // Separação de duplicadas
          if (!duplicate(tok,
                         words.at(letter(tok[0])))) words.at(letter(tok[0])).
            push_back(tok);
          else dup++;
        }

        tok = strtok(NULL, ": ,");
      }
    }
  }

  // Contabilizando o total de palavras
  for (size_t i = 0; i < 26; i++)
  {
    tot += contador[i];
  }
  cout << endl <<  "\nNumber of simple words = " <<  tot  << endl;

  // Ordenando o vetor
  cout << "\nSorting words ..." << endl;

  for (size_t i = 0; i < 26; i++)
  {
    sort(words.at(i).begin(), words.at(i).end());
  }
  cout << "\nRemoving duplicate words ..." << endl;

  // Transfere vetor para o arquivo
  cout << "\nNumber of non-duplicate simple words = " << tot - dup << endl;
  cout << "\nSaving words into file " << file4write << " ... " << endl;

  for (size_t i = 0; i < 26; i++)
  {
    for (size_t j = 0; j < words.at(i).size(); j++)
    {
      outfile << words.at(i).at(j) << endl;
    }
  }

  // Fechando os arquivos
  infile.close();
  outfile.close();
  cout << "\nEnd of processing." << endl << endl;


  return 0;
}

// Contagem do numero de palavras
void counter(int v[], int n, char c)
{
  switch (c)
  {
  case 'A':
    v[0] += 1;
    break;

  case 'B':
    v[1] += 1;
    break;

  case 'C':
    v[2] += 1;
    break;

  case 'D':
    v[3] += 1;
    break;

  case 'E':
    v[4] += 1;
    break;

  case 'F':
    v[5] += 1;
    break;

  case 'G':
    v[6] += 1;
    break;

  case 'H':
    v[7] += 1;
    break;

  case 'I':
    v[8] += 1;
    break;

  case 'J':
    v[9] += 1;
    break;

  case 'K':
    v[10] += 1;
    break;

  case 'L':
    v[11] += 1;
    break;

  case 'M':
    v[12] += 1;
    break;

  case 'N':
    v[13] += 1;
    break;

  case 'O':
    v[14] += 1;
    break;

  case 'P':
    v[15] += 1;
    break;

  case 'Q':
    v[16] += 1;
    break;

  case 'R':
    v[17] += 1;
    break;

  case 'S':
    v[18] += 1;
    break;

  case 'T':
    v[19] += 1;
    break;

  case 'U':
    v[20] += 1;
    break;

  case 'V':
    v[21] += 1;
    break;

  case 'W':
    v[22] += 1;
    break;

  case 'X':
    v[23] += 1;
    break;

  case 'Y':
    v[24] += 1;
    break;

  case 'Z':
    v[25] += 1;
    break;
  }
}

// Verificar Duplicadas
bool duplicate(const string word, const vector<string>lista)
{
  for (size_t i = 0; i < lista.size(); i++)
  {
    if (lista.at(i) == word) return true;
  }
  return false;
}

// Impressao de ponto a cada 100 palavras
void dots(int v[], int n, char c)
{
  if (v[letter(c)] == 99) {
    cout << endl << c << endl;
  }

  if (v[letter(c)] % 100 == 0) {
    cout << "." << flush;
  }
}

// Converter letra em numero
int letter(char c)
{
  switch (c)
  {
  case 'A':
    return 0;

  case 'B':
    return 1;

  case 'C':
    return 2;

  case 'D':
    return 3;

  case 'E':
    return 4;

  case 'F':
    return 5;

  case 'G':
    return 6;

  case 'H':
    return 7;

  case 'I':
    return 8;

  case 'J':
    return 9;

  case 'K':
    return 10;

  case 'L':
    return 11;

  case 'M':
    return 12;

  case 'N':
    return 13;

  case 'O':
    return 14;

  case 'P':
    return 15;

  case 'Q':
    return 16;

  case 'R':
    return 17;

  case 'S':
    return 18;

  case 'T':
    return 19;

  case 'U':
    return 20;

  case 'V':
    return 21;

  case 'W':
    return 22;

  case 'X':
    return 23;

  case 'Y':
    return 24;

  case 'Z':
    return 25;
  }
  return 0;
}
