#pragma once

#include <stdexcept>
#include <string>

#include "Common.h"
#include "solucions/parser.hpp"

class PuntDeInteresBase {
   private:
    Coordinate m_coord;
    std::string m_name;

   public:
    PuntDeInteresBase();
    PuntDeInteresBase(Coordinate coord, std::string name);
    PuntDeInteresBase(const NodeParser& parser) {
        auto name = parser.getTag("name");
        auto lat = parser.getAttribute("lat");
        auto lon = parser.getAttribute("lon");

        if (name != nullptr) {
            this->m_name = *name;
        }

        if (lat != nullptr) {
            this->m_coord.lat = std::stod(*lat);
        }

        if (lon != nullptr) {
            this->m_coord.lat = std::stod(*lon);
        }
    }

    Coordinate getCoord();
    virtual std::string getName();
    virtual unsigned int getColor();
};
