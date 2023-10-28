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

        if (name == nullptr || lat == nullptr || lon == nullptr) {
            throw new std::logic_error("some attribute was not found");
        }

        this->m_name = *name;
        this->m_coord.lat = std::stod(*lat);
        this->m_coord.lon = std::stod(*lon);
    }

    Coordinate getCoord();
    virtual std::string getName();
    virtual unsigned int getColor();
};
