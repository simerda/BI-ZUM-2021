//
// Created by simerjan on 10.03.21.
//

#ifndef HW_01_GREEDYSEARCH_H
#define HW_01_GREEDYSEARCH_H


#include "SearchAlgorithmInterface.h"

class GreedySearch: public SearchAlgorithmInterface {

public:
    void expand(Tile &tile) override;

    Tile& next(const Tile &targetTile) override;

private:
    unsigned int metric(const Tile &tile, const Tile &targetTile);

    vector<reference_wrapper<Tile>> available;

};


#endif //HW_01_GREEDYSEARCH_H
