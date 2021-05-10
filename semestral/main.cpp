
#include "table.h"

using namespace std;


int main()
{
    Agent agent = Agent::loadFromFile("random.ag");
    Table table;
    table.addPlayer(Player("Simikac", 200));
    table.addPlayer(Player("big brainz AI", 200, &agent));
    table.startGame();

    return 0;
}
