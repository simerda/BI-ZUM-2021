//
// Created by simerjan on 09.03.21.
//

#include "Tile.h"
#include <stdexcept>
#include <functional>

using std::runtime_error;

Tile::Tile(TileEnum state): state(state)
{
}

Tile Tile::fromChar(const char character)
{
    if(character == ' '){
        return Tile(TileEnum::FRESH);
    }

    if(character == 'X'){
        return Tile(TileEnum::WALL);
    }

    throw runtime_error("Unrecognized character");
}

TileEnum Tile::getState() const
{
    return state;
}

string Tile::toString() const
{
    if(state == TileEnum::WALL){
        return "X";
    }

    if(state == TileEnum::FRESH){
        return " ";
    }

    if(state == TileEnum::OPEN){
        return "#";
    }

    if(state == TileEnum::CLOSED){
        return "o";
    }

    if(state == TileEnum::START){
        return "S";
    }

    if(state == TileEnum::END){
        return "E";
    }

    throw runtime_error("Implementation error");
}

void Tile::setState(const TileEnum &state)
{
    Tile::state = state;
}

void Tile::addNeighbour(Tile &tile)
{
    neighbours.emplace_back(tile);
}

vector<reference_wrapper<Tile>> &Tile::getNeighbours()
{
    return neighbours;
}
