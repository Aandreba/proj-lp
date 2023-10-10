#pragma once

#include <stdint.h>

#include <string>

#include "../Common.h"
#include "../PuntDeInteresBase.h"

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase {
   private:
    std::string shop;
    std::string opening_hours;

   public:
    PuntDeInteresBotigaSolucio(Coordinate coord, std::string name, std::string shop, std::string opening_hours) : PuntDeInteresBase(coord, name) {
        this->opening_hours = opening_hours;
        this->shop = shop;
    }

    unsigned int getColor() const {
        if (this->shop == "supermarket") {
            return 0xA5BE00;
        } else if (this->shop == "tobacco") {
            return 0xFFAD69;
        } else if (this->shop == "bakery") {
            if (string_contains(this->opening_hours, "Div 06:00-22:00") || string_contains(this->opening_hours, "Dill 06:00-22:00")) {
                return 0x4CB944;
            } else {
                return 0xE85D75;
            }
        } else {
            return 0xEFD6AC;
        }
    }
};
