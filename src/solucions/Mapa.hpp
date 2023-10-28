#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "../MapaBase.h"
#include "../Util.h"
#include "Botiga.hpp"
#include "Restaurant.hpp"
#include "parser.hpp"

class MapaSolucio : public MapaBase {
   private:
    std::vector<std::unique_ptr<PuntDeInteresBase>> pids;

    void getPdis(std::vector<PuntDeInteresBase*>& dst) {
        dst.reserve(dst.size() + this->pids.size());
        for (auto it = this->pids.begin(); it != this->pids.end(); it++) {
            dst.push_back(it->get());
        }
    }

    void getCamins(std::vector<CamiBase*>& dst) {
        for (auto it = this->pids.begin(); it != this->pids.end(); it++) {
            // (*it)->
        }
    }

    void parsejaXmlElements(std::vector<XmlElement>& xmlElements) {
        for (auto elem = xmlElements.begin(); elem != xmlElements.end(); elem++) {
            if (elem->id_element == "node") {
                this->parseNode(*elem);
            }
        }
    }

    void parseNode(XmlElement& node) {
        const NodeParser parser(node);

        auto amenity = parser.getAttribute("amenity");
        if (amenity != nullptr && *amenity == "restaurant") {
            this->pids.push_back(std::make_unique<PuntDeInteresRestaurantSolucio>(parser));
        }

        auto shop = parser.getAttribute("shop");
        if (shop != nullptr) {
            this->pids.push_back(std::make_unique<PuntDeInteresBotigaSolucio>(*shop, parser));
        }
    }
};
