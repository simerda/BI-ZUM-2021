//
// Created by simerjan on 11.03.21.
//

#ifndef HW_01_ASTARSEARCH_H
#define HW_01_ASTARSEARCH_H

#include "SearchAlgorithmInterface.h"

class AStarSearch: public SearchAlgorithmInterface {

public:
    void expand(Tile &tile) override;

    Tile& next(const Tile &targetTile) override;

    double metric(const Tile &tile, const Tile &targetTile);

private:
    vector<reference_wrapper<Tile>> available;
};


#endif //HW_01_ASTARSEARCH_H
