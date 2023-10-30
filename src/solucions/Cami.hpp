#pragma once

#include <memory>
#include <vector>

#include "../CamiBase.h"
#include "../Common.h"
#include "../PuntDeInteresBase.h"
#include "parser.hpp"

class CamiSolucio : public CamiBase {
   public:
    std::string highway;
    std::vector<Coordinate> coords;

   public:
    CamiSolucio(const EntryParser& parser, const binary_map<unsigned long, Coordinate>& node_pool) {
        auto highway = parser.getTag("highway");
        if (highway != nullptr) {
            this->highway = *highway;
        }
        this->coords = PuntDeInteresBase::getNodeCoords(parser, node_pool);
    }

    std::vector<Coordinate> getCamiCoords() {
        return this->coords;
    }
};
