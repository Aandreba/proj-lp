#pragma once

#include <stdint.h>

#include <string>

#include "../Common.h"
#include "../PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase {
   private:
    std::string cuisine;
    bool wheelchair;

   public:
    PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name, std::string cuisine, bool wheelchair) : PuntDeInteresBase(coord, name) {
        this->cuisine = cuisine;
        this->wheelchair = wheelchair;
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
