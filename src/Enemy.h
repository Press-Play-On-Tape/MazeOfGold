#include <Arduboy2Core.h>
#include <Sprites.h>

class Enemy {

    public:

        uint8_t level;
        int16_t x;
        int16_t y;
        int8_t vx;
        int8_t vy;
        int16_t lastX;
        int16_t lastY;
        int8_t dir;

        void reset() {

            this->x = 0;
            this->y = 0;

        }

        bool isActive() {
        
            return this->x > 0 && this->y > 0;

        }
        
};
