#include "cwcreator.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{

    int lin, col;
    cin >> lin;
    cin >> col;
    Board q(lin, col);
    q.addWord("ola", "AbV");
    q.showBoard();
    q.addWord("pk", "DbH");
    q.showBoard();

    return 0;
}
