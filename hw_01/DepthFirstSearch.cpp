//
// Created by simerjan on 10.03.21.
//

#include "DepthFirstSearch.h"
#include <stdexcept>

using std::runtime_error;
using std::ref;

void DepthFirstSearch::expand(Tile &tile)
{
    if(tile.getState() != TileEnum::START){
        tile.setState(TileEnum::CLOSED);
    }

    for(Tile &neighbour : tile.getNeighbours())
    {
        if(neighbour.getState() == TileEnum::END || neighbour.getState() == TileEnum::FRESH){
            neighbour.setExpandedBy(tile);
            available.push(ref(neighbour));

            // END discovered - will be stepped on in the next move
            if(neighbour.getState() == TileEnum::END){
                return;
            }
            // set state for fresh tile
            neighbour.setState(TileEnum::OPEN);
        }
    }
}

Tile &DepthFirstSearch::next(const Tile &targetTile)
{
    if(available.empty()){
        throw runtime_error("no more available tiles");
    }
    auto tile = available.top();
    available.pop();

    return tile.get();
}
