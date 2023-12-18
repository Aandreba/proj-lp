#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "./MapaBase.h"
#include "./Util.h"
#include "BallTree.h"
#include "Botiga.hpp"
#include "Cami.hpp"
#include "GrafSolucio.h"
#include "MyUtils.hpp"
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

        this->clear();
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

        auto name = parser.getTag("name");
        if (name == nullptr || (*name) == "itsatrap" || (*name) == "isatrap") {
            PuntDeInteresBase generic = parser.parseBase();
            return std::make_pair(parser.getId(), generic.getCoord());
        }

        auto cuisine = parser.getTag("cuisine");
        if (cuisine != nullptr) {
            auto rest = std::make_unique<PuntDeInteresRestaurantSolucio>(*cuisine, parser);
            const auto info = std::make_pair(parser.getId(), rest->getCoord());
            this->ips.push_back(std::move(rest));
            return info;
        }

        auto shop = parser.getTag("shop");
        if (shop != nullptr) {
            auto shop_ptr = std::make_unique<PuntDeInteresBotigaSolucio>(*shop, parser);
            const auto info = std::make_pair(parser.getId(), shop_ptr->getCoord());
            this->ips.push_back(std::move(shop_ptr));
            return info;
        }

        auto punt = std::make_unique<PuntDeInteresBase>(parser.parseBase());
        const auto info = std::make_pair(parser.getId(), punt->getCoord());
        this->ips.push_back(std::move(punt));
        return info;
    }

    void clear() {
        this->ips.clear();
        this->ways.clear();
    }

    CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) {
        CamiBase* min_way = nullptr;
        double min_dist = INF;

        for (size_t i = 0; i < ways.size(); i++) {
            CamiBase* way = &ways[i];

            BallTree bt;
            bt.construirArbre(way->getCamiCoords());
            Coordinate start;
            bt.nodeMesProper(desde->getCoord(), start, nullptr);
            Coordinate end;
            bt.nodeMesProper(a->getCoord(), end, nullptr);

            GrafSolucio graph(ways[i]);
            break;
        }

        return min_way;
    }
};
