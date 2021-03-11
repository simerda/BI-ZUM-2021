#include <iostream>
#include "Maze.h"
#include "RandomSearch.h"
#include "DepthFirstSearch.h"
#include "BreathFirstSearch.h"
#include "GreedySearch.h"
#include "AStarSearch.h"

using namespace std;

int main()
{

    string path;
    cout << "Enter path to the input file:" << endl;
    if(! getline(cin, path)){
        cout << "Wrong input!" << endl;
        return 1;
    }

    Maze maze(path);
    AStarSearch searchAlgorithm;
    maze.solve(searchAlgorithm);

    return 0;
}
