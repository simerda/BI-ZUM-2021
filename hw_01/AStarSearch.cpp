//
// Created by simerjan on 11.03.21.
//

#include "AStarSearch.h"
#include <stdexcept>
#include <cmath>
#include <climits>

using std::ref;
using std::runtime_error;
using std::hypot;


void AStarSearch::expand(Tile &tile)
{
    if (tile.getState() != TileEnum::START) {
        tile.setState(TileEnum::CLOSED);
    }

    unsigned int nextDistance = tile.getDistanceFromStart() + 1;
    for (Tile &neighbour : tile.getNeighbours()) {
        neighbour.setDistanceFromStart(nextDistance);

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

Tile &AStarSearch::next(const Tile &targetTile)
{
    if (available.empty()) {
        throw runtime_error("no more available tiles");
    }
    double bestMetric = MAXFLOAT;
    unsigned int index = 0;

    for (unsigned int i = 0; i < available.size(); i++) {
        uint32_t currMetric = metric(available[i].get(), targetTile) + available[i].get().getDistanceFromStart();

        if (currMetric < bestMetric) {
            bestMetric = currMetric;
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
 * Euclidean distance.
 *
 * @param tile
 * @param targetTile
 * @return
 */
double AStarSearch::metric(const Tile &tile, const Tile &targetTile)
{
    return hypot(
            abs((int) tile.getXPos() - (int) targetTile.getXPos()),
            abs((int) tile.getYPos() - (int) targetTile.getYPos())
    );
}
