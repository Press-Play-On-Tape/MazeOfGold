#include <Arduboy2Core.h>
#include <Sprites.h>
#include "src/Enums.h"

const uint8_t NUM_COINS       = 10;

void resetCoin(uint8_t i) {

    maze.getEnemy(i).x = random(0, WIDTH - 8);
    maze.getEnemy(i).y = random(-64, 0);                     // start above the screen
    maze.getEnemy(i).data = random(1, 3);

}

void initCoins() {

    for (uint8_t i = 0; i < NUM_COINS; ++i) {
        resetCoin(i);
    }

}

void updateAndDrawCoins() {

    for (uint8_t i = 0; i < NUM_COINS; ++i) {

        maze.getEnemy(i).y += maze.getEnemy(i).data; 

        if (maze.getEnemy(i).y > 64) resetCoin(i);  

        Sprites::drawSelfMasked(maze.getEnemy(i).x, maze.getEnemy(i).y, Images::Coin, (arduboy.frameCount + i) % 8);
    }

}

void handleTitle() {

    updateAndDrawCoins();

    Sprites::drawExternalMask(0, 22, Images::Title, Images::Title_Mask, 0, 0);
    
    if (arduboy.frameCount > 96) {
        Sprites::drawOverwrite(33, 47, Images::Press_A_Mask, 0);
        Sprites::drawSelfMasked(34, 48, Images::Press_A, 0);
    }

    if (arduboy.justPressed(A_BUTTON)) {

        gameState = GameState::Menu_Select;

    }	

}
