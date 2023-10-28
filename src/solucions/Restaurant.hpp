#pragma once

#include <stdint.h>

#include <stdexcept>
#include <string>

#include "../Common.h"
#include "../PuntDeInteresBase.h"
#include "parser.hpp"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase {
   private:
    std::string cuisine;
    bool wheelchair;

   public:
    PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name, std::string cuisine, bool wheelchair) : PuntDeInteresBase(coord, name) {
        this->cuisine = cuisine;
        this->wheelchair = wheelchair;
    }

    PuntDeInteresRestaurantSolucio(const EntryParser& parser) : PuntDeInteresBase(parser) {
        auto cuisine = parser.getTag("cuisine");
        if (cuisine != nullptr) {
            this->cuisine = *cuisine;
        }

        auto wheelchair = parser.getTag("wheelchair");
        if (wheelchair == nullptr) {
            this->wheelchair = false;
        } else {
            this->wheelchair = (*wheelchair) == "yes";
        }
    }

    unsigned int getColor() {
        if (string_contains(this->cuisine, "pizza")) {
            return 0x03FCBA;
        } else if (string_contains(this->cuisine, "chinese")) {
            return 0xA6D9F7;
        } else if (this->wheelchair) {
            return 0x251351;
        } else {
            return PuntDeInteresBase::getColor();
        }
    }
};
