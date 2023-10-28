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
        this->nodes = parser.getNodeRefs(node_pool);
    }
};
