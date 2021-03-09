//
// Created by simerjan on 09.03.21.
//

#ifndef HW_01_MAZE_H
#define HW_01_MAZE_H

#include "Tile.h"
#include "SearchAlgorithmInterface.h"
#include <vector>
using std::vector;


class Maze {

public:
    Maze(const string &path);

    void print();

    void solve(SearchAlgorithmInterface &searchAlgorithm);

private:
    vector<vector<Tile>> field;
    int startX, startY, endX, endY;
};


#endif //HW_01_MAZE_H
