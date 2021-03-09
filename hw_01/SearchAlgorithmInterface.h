//
// Created by simerjan on 09.03.21.
//

#ifndef HW_01_SEARCHALGORITHMINTERFACE_H
#define HW_01_SEARCHALGORITHMINTERFACE_H


#include "Tile.h"

class SearchAlgorithmInterface {

public:
    virtual ~SearchAlgorithmInterface() = default;

    virtual void expand(Tile &tile) = 0;

    virtual Tile& next() = 0;
};


#endif //HW_01_SEARCHALGORITHMINTERFACE_H
