#include <iostream>
#include "Maze.h"
#include "RandomSearch.h"

using namespace std;

int main()
{

    string path;
    cout << "Enter path to the input file:" << endl;
    if(! getline(cin, path)){
        cout << "Wrong input!" << endl;
        return 1;
    }

    RandomSearch test;

    Maze maze(path);
    RandomSearch searchAlgorithm;
    maze.solve(searchAlgorithm);

    return 0;
}
