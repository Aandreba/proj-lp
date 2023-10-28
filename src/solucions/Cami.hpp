#pragma once

#include <vector>

#include "../CamiBase.h"
#include "../Common.h"

class CamiSolucio : public CamiBase {
   public:
    std::vector<Coordinate> getCamiCoords() {
        return {
            {41.4928803, 2.1452381},
            {41.4929072, 2.1452474},
            {41.4933070, 2.1453852},
            {41.4939882, 2.1456419},
        };
    }
};
