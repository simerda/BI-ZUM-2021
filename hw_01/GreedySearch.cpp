//
// Created by simerjan on 10.03.21.
//

#include "GreedySearch.h"
#include <stdexcept>

using std::ref;
using std::runtime_error;

void GreedySearch::expand(Tile &tile)
{
    if (tile.getState() != TileEnum::START) {
        tile.setState(TileEnum::CLOSED);
    }

    for (Tile &neighbour : tile.getNeighbours()) {
        // END discovered - will be stepped on in the next move
        if (neighbour.getState() == TileEnum::END) {
            neighbour.setExpandedBy(tile);
            available = vector<reference_wrapper<Tile>>();
            available.push_back(ref(neighbour));
            return;
        }

        // add fresh neighbours
        if (neighbour.getState() == TileEnum::FRESH) {
            neighbour.setExpandedBy(tile);
            neighbour.setState(TileEnum::OPEN);
            available.push_back(ref(neighbour));
        }
    }
}

Tile &GreedySearch::next(const Tile &targetTile)
{
    if (available.empty()) {
        throw runtime_error("no more available tiles");
    }
    uint32_t bestMetric = INT32_MAX;
    unsigned int index = 0;

    for (unsigned int i = 0; i < available.size(); i++) {
        if (metric(available[i].get(), targetTile) < bestMetric) {
            bestMetric = metric(available[i].get(), targetTile);
            index = i;
        }
    }

    Tile &selected = available[index].get();
    auto iterator = available.begin();
    advance(iterator, index);
    available.erase(iterator);

    return selected;
}


/**
 * Manhattan length.
 *
 * @param tile
 * @param targetTile
 * @return
 */
unsigned int GreedySearch::metric(const Tile &tile, const Tile &targetTile)
{
    return abs((int)tile.getXPos() - (int)targetTile.getXPos())
    + abs((int) tile.getYPos() - (int)targetTile.getYPos());
}
