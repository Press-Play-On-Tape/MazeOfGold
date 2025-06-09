#pragma once

#include "Constants.h"
#include "Enums.h"

class Player {

    public:
        
        int16_t x = 1 * tileSize;
        int16_t y = 1 * tileSize;
        int8_t vx = 0;
        int8_t vy = 0;

        uint8_t dir;
        uint8_t inventoryCount;

        ItemType inventory[10];
        bool dead = false;

        Player() { }

        bool addItem(ItemType item) {
        
            if (this->inventoryCount == 10) return false;

            this->inventory[this->inventoryCount] = item;
            this->inventoryCount++;
            return true;

        }

        bool removeItem(uint8_t idx) {
        
            for (uint8_t i = idx + 1; i < 10; i++) {
            
                this->inventory[i - 1] = this->inventory[i];

            }

            this->inventory[9] = ItemType::None;
            this->inventoryCount--;

        }


        void reset() {

            this->x = 1 * tileSize;
            this->y = 1 * tileSize;
            this->vx = 0;
            this->vy = 0;
            this->dir = 2;

            this->inventoryCount = 0;
            this->addItem(ItemType::Map);
            this->addItem(ItemType::Bomb);
            this->dead = false;

        }

        uint8_t getInventoryCount()                     { return this->inventoryCount; }
        ItemType &getInventoryItem(uint8_t idx)         { return this->inventory[idx]; }
        bool isDead()                                   { return this->dead; }

        void setDead(bool val)                          { this->dead = val; }

};