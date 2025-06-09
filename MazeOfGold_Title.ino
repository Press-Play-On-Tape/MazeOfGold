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

    arduboy.drawFastHLine(0, 22, 128, BLACK);
    arduboy.drawFastHLine(0, 23, 128, WHITE);
    arduboy.drawFastHLine(0, 24, 128, BLACK);
    Sprites::drawOverwrite(0, 25, Images::Title, 0);
    arduboy.drawFastHLine(0, 39, 128, BLACK);
    arduboy.drawFastHLine(0, 40, 128, WHITE);
    arduboy.drawFastHLine(0, 41, 128, BLACK);

    if (arduboy.justPressed(A_BUTTON)) {

        gameState = GameState::Menu_Select;

    }	

}