#pragma once

#include <stdexcept>
#include <string>

#include "Common.h"
#include "solucions/binary_map.hpp"
#include "solucions/parser.hpp"

class PuntDeInteresBase {
   public:
    unsigned long id;

   private:
    Coordinate m_coord;
    std::string m_name;

   public:
    PuntDeInteresBase();
    PuntDeInteresBase(Coordinate coord, std::string name);
    PuntDeInteresBase(const EntryParser& parser) {
        auto id = parser.getAttribute("id");
        auto name = parser.getTag("name");
        auto lat = parser.getAttribute("lat");
        auto lon = parser.getAttribute("lon");

        if (id != nullptr) {
            this->id = std::stoul(*id);
        }

        if (name != nullptr) {
            this->m_name = *name;
        }

        if (lat != nullptr) {
            this->m_coord.lat = std::stod(*lat);
        }

        if (lon != nullptr) {
            this->m_coord.lon = std::stod(*lon);
        }
    }

    Coordinate getCoord();
    virtual std::string getName();
    virtual unsigned int getColor();

    static std::vector<Coordinate> getNodeCoords(const EntryParser& parser, const binary_map<unsigned long, Coordinate>& pool) {
        const auto children = &parser.node.fills;
        std::vector<Coordinate> result;

        for (auto it = children->cbegin(); it != children->cend(); it++) {
            if (it->first == "nd") {
                for (auto jt = it->second.cbegin(); jt != it->second.cend(); jt++) {
                    if (jt->first == "ref") {
                        const auto key = std::stoul(jt->second);

                        try {
                            result.push_back(pool.at(key));
                        } catch (const std::out_of_range&) {
                        }

                        break;
                    }
                }
            }
        }

        return result;
    }
};
