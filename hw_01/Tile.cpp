//
// Created by simerjan on 09.03.21.
//

#include "Tile.h"
#include <stdexcept>
#include <functional>

using std::runtime_error;

Tile::Tile(unsigned int xPos, unsigned int yPos, TileEnum state): xPos(xPos), yPos(yPos), state(state)
{
}

Tile Tile::fromChar(unsigned int xPos, unsigned int yPos, const char character)
{
    if(character == ' '){
        return Tile(xPos, yPos, TileEnum::FRESH);
    }

    if(character == 'X'){
        return Tile(xPos, yPos, TileEnum::WALL);
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
        return "\x1B[32m#\033[0m";
    }

    if(state == TileEnum::CLOSED){
        return "\x1B[33m◈\033[0m";
    }

    if(state == TileEnum::START){
        return "S";
    }

    if(state == TileEnum::END){
        return "E";
    }

    if(state == TileEnum::PATH){
        return "\x1B[31mo\033[0m";
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

void Tile::setExpandedBy(Tile &tile)
{
    expandedBy = &tile;
}

Tile *Tile::getExpandedBy() const
{
    return expandedBy;
}

unsigned int Tile::getXPos() const
{
    return xPos;
}

unsigned int Tile::getYPos() const
{
    return yPos;
}

unsigned int Tile::getDistanceFromStart() const
{
    return distanceFromStart;
}

void Tile::setDistanceFromStart(unsigned int distance)
{
    distanceFromStart = distance;
}
