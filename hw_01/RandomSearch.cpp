//
// Created by simerjan on 09.03.21.
//

#include "RandomSearch.h"
#include <functional>
#include <iterator>

using std::ref;
using std::advance;
using std::runtime_error;

void RandomSearch::expand(Tile &tile)
{
    if(tile.getState() != TileEnum::START){
        tile.setState(TileEnum::CLOSED);
    }

    for(Tile &neighbour : tile.getNeighbours())
    {
        // END discovered - will be stepped on in the next move
        if(neighbour.getState() == TileEnum::END){
            neighbour.setExpandedBy(tile);
            available = vector<reference_wrapper<Tile>>();
            available.push_back(ref(neighbour));
            return;
        }

        // add fresh neighbours
        if(neighbour.getState() == TileEnum::FRESH){
            neighbour.setExpandedBy(tile);
            neighbour.setState(TileEnum::OPEN);
            available.push_back(ref(neighbour));
        }
    }
}

Tile &RandomSearch::next()
{
    if(available.empty()){
        throw runtime_error("no more available tiles");
    }
    unsigned int selected = rand() % available.size();
    reference_wrapper<Tile> selectedTile = available[selected];

    auto iterator = available.begin();
    advance(iterator, selected);
    available.erase(iterator);

    return selectedTile.get();
}
