#include <stdint.h>

#include <string>

#include "../PuntDeInteresBase.h"

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase {
   private:
    std::string shop;
    std::string opening_hours;

   public:
    unsigned int getColor() const {
        if (this->shop == "supermarket") {
            return 0xA5BE00;
        } else if (this->shop == "tobacco") {
            return 0xFFAD69;
        } else if (this->shop == "bakery") {
            if (this->shop.find("Div 06:00-22:00") != std::string::npos || this->shop.find("Dill 06:00-22:00") != std::string::npos) {
                return 0x4CB944;
            } else {
                return 0xE85D75;
            }
        } else {
            return 0xEFD6AC;
        }
    }
};
