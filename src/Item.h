#pragma once

#include "Constants.h"
#include "Enums.h"

class Item {
    
    public:
        uint8_t level;
        int16_t x;
        int16_t y;
        ItemType itemType;
        int16_t data;

        void reset() {

            this->x = 0;
            this->y = 0;

        }

        bool isActive() {
        
            return this->x > 0 && this->y > 0;

        }
};