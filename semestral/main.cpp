#include <iostream>
#include "table.h"

using namespace std;






int main()
{
    Table table;
    table.addPlayer(Player("Player 1", 200));
    table.addPlayer(Player("Player 2", 200));
    table.startGame();





    return 0;
}
