//
// Created by simerjan on 10.03.21.
//

#ifndef HW_01_DEPTHFIRSTSEARCH_H
#define HW_01_DEPTHFIRSTSEARCH_H

#include "SearchAlgorithmInterface.h"
#include <stack>

using std::stack;

class DepthFirstSearch: public SearchAlgorithmInterface{

public:
    void expand(Tile &tile) override;

    Tile& next() override;

private:
    stack<reference_wrapper<Tile>> available;
};


#endif //HW_01_DEPTHFIRSTSEARCH_H
