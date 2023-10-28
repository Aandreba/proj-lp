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
    std::vector<PuntDeInteresBase*> nodes;

   public:
    CamiSolucio(const EntryParser& parser, std::vector<std::unique_ptr<PuntDeInteresBase>>& node_pool) {
        auto highway = parser.getTag("highway");
        if (highway != nullptr) {
            this->highway = *highway;
        }
        this->nodes = PuntDeInteresBase::getNodeRefs(parser, node_pool);
    }

    std::vector<Coordinate> getCamiCoords() {
        std::vector<Coordinate> result;
        result.reserve(this->nodes.size());

        for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {
            result.push_back((*it)->getCoord());
        }

        return result;
    }
};
