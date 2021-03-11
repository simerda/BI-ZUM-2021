#include <iostream>
#include "Maze.h"
#include "SearchAlgorithmInterface.h"
#include "RandomSearch.h"
#include "DepthFirstSearch.h"
#include "BreathFirstSearch.h"
#include "GreedySearch.h"
#include "AStarSearch.h"

using namespace std;

int main()
{
    try{
    string path;
    cout << "Enter path to the input file:" << endl;
    if(! getline(cin, path)){
        cout << "Wrong input!" << endl;
        return 1;
    }
    Maze maze(path);

    cout << "Choose algorithm for path finding:\n\n1) Random search\n2) DFS\n3) BFS\n4) Greedy search\n5) A*" << endl;

    int selection = -1;
    while (!(cin >> selection) || selection <= 0 || selection > 5){
        cin.clear();
        cin.ignore(INT32_MAX, '\n');

        cout << "Invalid selection, choose again." << endl;
    }
    cin.ignore(INT32_MAX, '\n');

    SearchAlgorithmInterface* searchAlgorithm;
    switch (selection) {
        case 1: searchAlgorithm = new RandomSearch;
            break;
        case 2: searchAlgorithm = new DepthFirstSearch;
            break;
        case 3: searchAlgorithm = new BreathFirstSearch;
            break;
        case 4: searchAlgorithm = new GreedySearch;
            break;
        case 5: searchAlgorithm = new AStarSearch;
            break;
    }
    maze.solve(*searchAlgorithm);
    delete searchAlgorithm;
    } catch (const runtime_error &e) {
        cout << string("Error: ") + e.what() << endl;
        return 1;
    }
    return 0;
}
