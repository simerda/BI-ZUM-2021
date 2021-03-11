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
    PATH,
    START,
    END
};

class Tile {

public:
    Tile(unsigned int xPos, unsigned int yPos, TileEnum state);

    static Tile fromChar(unsigned int xPos, unsigned int yPos, char character);

    TileEnum getState() const;
    void setState(const TileEnum &state);

    string toString() const;

    void addNeighbour(Tile &tile);

    vector<reference_wrapper<Tile>>& getNeighbours();

    void setExpandedBy(Tile &tile);

    Tile * getExpandedBy() const;

    unsigned int getXPos() const;

    unsigned int getYPos() const;

    unsigned int getDistanceFromStart() const;

    void setDistanceFromStart(unsigned int distance);

private:
    Tile * expandedBy = nullptr;
    vector<reference_wrapper<Tile>> neighbours;
    unsigned int xPos;
    unsigned int yPos;
    unsigned int distanceFromStart = 0;
    TileEnum state;
};


#endif //HW_01_TILE_H
