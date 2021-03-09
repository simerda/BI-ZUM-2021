#include <iostream>
#include "Maze.h"

using namespace std;

int main()
{

    string path;
    cout << "Enter path to the input file:" << endl;
    if(! getline(cin, path)){
        cout << "Wrong input!" << endl;
        return 1;
    }

        Maze maze = Maze::parseFromFile(path);
        maze.print();

    return 0;
}
