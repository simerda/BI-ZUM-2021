//
// Created by simerjan on 10.03.21.
//

#ifndef HW_01_BREATHFIRSTSEARCH_H
#define HW_01_BREATHFIRSTSEARCH_H


#include "SearchAlgorithmInterface.h"
#include <deque>

using std::deque;

class BreathFirstSearch: public SearchAlgorithmInterface {

public:
    void expand(Tile &tile) override;

    Tile& next(const Tile &targetTile) override;

private:
    deque<reference_wrapper<Tile>> available;

};


#endif //HW_01_BREATHFIRSTSEARCH_H
