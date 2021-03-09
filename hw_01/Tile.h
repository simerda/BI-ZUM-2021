//
// Created by simerjan on 09.03.21.
//

#ifndef HW_01_TILE_H
#define HW_01_TILE_H

#include <string>
#include <vector>
#include <functional>

using std::string;
using std::vector;
using std::reference_wrapper;

enum TileEnum{
    WALL,
    FRESH,
    OPEN,
    CLOSED,
    START,
    END
};

class Tile {

public:
    Tile(TileEnum state);

    static Tile fromChar(const char character);

    TileEnum getState() const;
    void setState(const TileEnum &state);

    string toString() const;

    void addNeighbour(reference_wrapper<Tile> tile);

private:
    TileEnum state;
    vector<reference_wrapper<Tile>> neighbours;
};


#endif //HW_01_TILE_H
