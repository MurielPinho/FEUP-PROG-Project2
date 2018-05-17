
#include "cwcreator.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

int main()
{
  int b;
  string a, c;
  ostringstream number;
  ifstream infile;
  ofstream outfile;
  infile.open("teste.txt");
  getline(infile,c);
  infile.close();
  outfile.open("teste.txt");
  b = stoi(c);
  b++;
  number << "B";
  number << setfill('0') << setw(3) << to_string(b) << ".txt" ;
  a  = number.str();
  cout << a << endl;
  outfile << a << endl;
  outfile.close();



return 0;
}
