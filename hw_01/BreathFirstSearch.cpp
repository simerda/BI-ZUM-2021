//
// Created by simerjan on 10.03.21.
//

#include "BreathFirstSearch.h"
#include <stdexcept>

using std::runtime_error;
using std::ref;

void BreathFirstSearch::expand(Tile &tile)
{
    if(tile.getState() != TileEnum::START){
        tile.setState(TileEnum::CLOSED);
    }

    for(Tile &neighbour : tile.getNeighbours())
    {
        if(neighbour.getState() == TileEnum::END || neighbour.getState() == TileEnum::FRESH){
            neighbour.setExpandedBy(tile);

            // END discovered - will be stepped on in the next move
            if(neighbour.getState() == TileEnum::END){
                available.push_front(ref(neighbour));
                return;
            }
            // fresh tile
            available.push_back(ref(neighbour));
            neighbour.setState(TileEnum::OPEN);
        }
    }
}

Tile &BreathFirstSearch::next()
{
    if(available.empty()){
        throw runtime_error("no more available tiles");
    }
    auto tile = available.front();
    available.pop_front();

    return tile.get();
}