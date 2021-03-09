//
// Created by simerjan on 09.03.21.
//

#ifndef HW_01_RANDOMSEARCH_H
#define HW_01_RANDOMSEARCH_H


#include "SearchAlgorithmInterface.h"

class RandomSearch: public SearchAlgorithmInterface {

public:
    void expand(Tile &tile) override;

    Tile& next() override;

private:
    vector<reference_wrapper<Tile>> available;

};


#endif //HW_01_RANDOMSEARCH_H
