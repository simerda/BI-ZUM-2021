//
// Created by simerjan on 09.03.21.
//

#ifndef HW_01_MAZE_H
#define HW_01_MAZE_H

#include "Tile.h"
#include <vector>
using std::vector;


class Maze {

public:

    Maze(const vector<vector<Tile>> &field, int startX, int startY, int endX, int endY);

    static Maze parseFromFile(const string &path);

    void print();

private:
    vector<vector<Tile>> field;
    int startX, startY, endX, endY;
};


#endif //HW_01_MAZE_H
