#include <Arduboy2.h>

// ----------------------------------------------------------------------------
//  Initialise state ..
//
void splashScreen_Init() {

    gameState = GameState::PPOT;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void splashScreen() { 

    if (arduboy.justPressed(A_BUTTON | B_BUTTON) > 0) {
        
        gameState = GameState::Menu_Init; 
        arduboy.frameCount == 0;

    }


    Sprites::drawOverwrite(32, 17, Images::PPOT, 0);

    uint8_t y = 17; // Default pixel position 1 is hidden in the top line of the image
    
    switch (arduboy.frameCount % 24) {

        case 6 ... 11:
            y = 30; // Move pixel down to position 2
            [[fallthrough]]

        case 0 ... 5:
            Sprites::drawOverwrite(91, 25, Images::PPOT_Arrow, 0); // Flash 'Play' arrow
            break;

        case 12 ... 17:
            y = 31; // Move pixel down to position 3
            break;

        default: // 36 ... 47:
            y = 32; // Move pixel down to position 4
            break;

    }

    arduboy.drawPixel(52, y, WHITE); // Falling pixel represents the tape spooling
    if (y % 2 == 0) { // On even steps of pixel movement, update the spindle image
        Sprites::drawOverwrite(45, 28, Images::PPOT_Spindle, 0);
    }

}
