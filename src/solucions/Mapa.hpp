#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "../MapaBase.h"
#include "../Util.h"
#include "Botiga.hpp"
#include "Cami.hpp"
#include "Restaurant.hpp"
#include "binary_map.hpp"
#include "parser.hpp"

class MapaSolucio : public MapaBase {
   private:
    std::vector<std::unique_ptr<PuntDeInteresBase>> ips;
    std::vector<CamiSolucio> ways;

    void getPdis(std::vector<PuntDeInteresBase*>& dst) {
        dst.reserve(dst.size() + this->ips.size());
        for (auto it = this->ips.begin(); it != this->ips.end(); it++) {
            dst.push_back(it->get());
        }
    }

    void getCamins(std::vector<CamiBase*>& dst) {
        dst.reserve(dst.size() + this->ways.size());
        for (auto it = this->ways.begin(); it != this->ways.end(); it++) {
            dst.push_back(&*it);
        }
    }

    void parsejaXmlElements(std::vector<XmlElement>& xmlElements) {
        std::vector<XmlElement*> ways;
        binary_map<unsigned long, Coordinate> nodes;

        for (auto elem = xmlElements.begin(); elem != xmlElements.end(); elem++) {
            if (elem->id_element == "node") {
                const auto info = this->parseNode(*elem);
                nodes.insert(std::move(info.first), std::move(info.second));
            } else if (elem->id_element == "way") {
                ways.push_back(&*elem);
            }
        }

        this->ways.reserve(this->ways.size() + ways.size());
        for (auto way = ways.begin(); way != ways.end(); way++) {
            const EntryParser parser(**way);
            this->ways.emplace_back(parser, nodes);
        }
    }

    std::pair<unsigned long, Coordinate> parseNode(XmlElement& node) {
        const EntryParser parser(node);

        auto cuisine = parser.getTag("cuisine");
        if (cuisine != nullptr) {
            auto rest = std::make_unique<PuntDeInteresRestaurantSolucio>(*cuisine, parser);
            const auto info = std::make_pair(rest->id, rest->getCoord());
            this->ips.push_back(std::move(rest));
            return info;
        }

        auto shop = parser.getTag("shop");
        if (shop != nullptr) {
            auto shop_ptr = std::make_unique<PuntDeInteresBotigaSolucio>(*shop, parser);
            const auto info = std::make_pair(shop_ptr->id, shop_ptr->getCoord());
            this->ips.push_back(std::move(shop_ptr));
            return info;
        }

        PuntDeInteresBase generic(parser);
        return std::make_pair(generic.id, generic.getCoord());
    }
};
