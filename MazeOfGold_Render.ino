#include <Arduboy2Core.h>
#include <Sprites.h>

void drawChestCount(int8_t x, uint8_t y) {

    Sprites::drawExternalMask(x, y, Images::Score, Images::Score_Mask, maze.getActiveChests() - 1, 0);
    
}


void drawMaze(uint8_t level) {

    int startTileX = camera.x / tileSize;
    int startTileY = camera.y / tileSize;

    for (int y = 0; y <= screenTileHeight; y++) {

        for (int x = 0; x <= screenTileWidth; x++) {

            int mazeX = startTileX + x;
            int mazeY = startTileY + y;

            if (mazeX >= 0 && mazeX < Constants::MazeWidth && mazeY >= 0 && mazeY < Constants::MazeHeight) {

                if (mazeX == 0 && mazeY == 0) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 12);
                } 
                else if (mazeX == Constants::MazeWidth - 1 && mazeY == 0) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 13);
                } 
                else if (mazeX == 0 && mazeY == Constants::MazeHeight - 1) {  // Bottom left
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 14);
                } 
                else if (mazeX == Constants::MazeWidth - 1 && mazeY == Constants::MazeHeight - 1) {  // Bottom right
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 15);
                } 
                else if (mazeX == Constants::MazeWidth - 1 && maze.isWall(level, mazeX - 1, mazeY)) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 18);
                } 
                else if (mazeX == Constants::MazeWidth - 1) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 10);
                }
                else if (maze.isWall(level, mazeX, mazeY - 1) && mazeY == Constants::MazeHeight - 1) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 19);
                } 
                else if (mazeY == Constants::MazeHeight - 1) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 11);
                }
                else if (mazeY == 0 && maze.isWall(level, mazeX, mazeY + 1)) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 17);
                } 
                else if (mazeY == 0) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 9);
                } 
                else if (mazeX == 0 && maze.isWall(level, mazeX + 1, mazeY)) { 
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 16);
                } 
                else if (mazeX == 0) {
                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 8);
                } 
                else if (maze.isWall(level, mazeX, mazeY)) {

                    if (maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 5);
                    } 
                    else if (maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 20);
                    } 
                    else if (maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 21);
                    } 
                    else if (maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 2);
                    } 
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 4);
                    } 
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {  // Updwards
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 6);
                    } 
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 22);
                    } 
                    else if (maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 23);
                    } 
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 3);
                    } 
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 1);
                    } 
                    else if (maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {  // 4 corners
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 7);
                    } 
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {  // corners
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 24);
                    } 
                    else if (maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 25);
                    } 
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 26);
                    } 
                    else if (maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 27);
                    } 
                    else if (maze.isWall(level, mazeX, mazeY)) {
                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 0);
                    }
                }
                else if (maze.getCell(level, mazeX, mazeY) == CellTypes::Stairs) {

                    if (maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 28);

                    }
                    else if (maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 29);

                    }
                    else if (maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 30);

                    }
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 31);

                    }
                    // ||
                    else if (maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 33);

                    }
                    // |^
                    else if (maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 34);

                    }
                    // |_
                    else if (maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && !maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 34);

                    }
                    // ^|
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 35);

                    }
                    // _|
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && maze.isWall(level, mazeX + 1, mazeY) && !maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 35);

                    }
                    // --
                    else if (!maze.isWall(level, mazeX - 1, mazeY) && !maze.isWall(level, mazeX + 1, mazeY) && maze.isWall(level, mazeX, mazeY - 1) && maze.isWall(level, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 35);

                    }

                }
                else if (maze.getCell(level, mazeX, mazeY) == CellTypes::GateClosed) {

                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 36);

                }
                else if (maze.getCell(level, mazeX, mazeY) == CellTypes::GateOpen) {

                    Sprites::drawSelfMasked((mazeX * tileSize) - camera.x, (mazeY * tileSize) - camera.y, Images::Blocks, 37);

                }

            }

        }

    }

}


void drawMaze_Small(uint8_t levelToRender) {

    uint8_t tileSize_Small = 4;

    int startTileX = 0;
    int startTileY = 0;

    for (uint8_t y = 0; y <= 23; y++) {

        for (uint8_t x = 0; x <= 23; x++) {

            int mazeX = startTileX + x;
            int mazeY = startTileY + y;

            if (mazeX >= 0 && mazeX < Constants::MazeWidth && mazeY >= 0 && mazeY < Constants::MazeHeight) {

                if (mazeX == 0 && mazeY == 0) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 12);
                } 
                else if (mazeX == Constants::MazeWidth - 1 && mazeY == 0) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 13);
                } 
                else if (mazeX == 0 && mazeY == Constants::MazeHeight - 1) {  // Bottom left
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 14);
                } 
                else if (mazeX == Constants::MazeWidth - 1 && mazeY == Constants::MazeHeight - 1) {  // Bottom right
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 15);
                } 
                else if (mazeX == Constants::MazeWidth - 1 && maze.isWall(levelToRender, mazeX - 1, mazeY)) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 18);
                } 
                else if (mazeX == Constants::MazeWidth - 1) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 10);
                }
                else if (maze.isWall(levelToRender, mazeX, mazeY - 1) && mazeY == Constants::MazeHeight - 1) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 19);
                } 
                else if (mazeY == Constants::MazeHeight - 1) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 11);
                }
                else if (mazeY == 0 && maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 17);
                } 
                else if (mazeY == 0) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 9);
                } 
                else if (mazeX == 0 && maze.isWall(levelToRender, mazeX + 1, mazeY)) { 
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 16);
                } 
                else if (mazeX == 0) {
                    Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 8);
                } 
                else if (maze.isWall(levelToRender, mazeX, mazeY)) {

                    if (maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && !maze.isWall(levelToRender, mazeX, mazeY - 1) && !maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 5);
                    } 
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && !maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 20);
                    } 
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && !maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 21);
                    } 
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && !maze.isWall(levelToRender, mazeX + 1, mazeY) && !maze.isWall(levelToRender, mazeX, mazeY - 1) && !maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 2);
                    } 
                    else if (!maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && !maze.isWall(levelToRender, mazeX, mazeY - 1) && !maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 4);
                    } 
                    else if (!maze.isWall(levelToRender, mazeX - 1, mazeY) && !maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {  // Updwards
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 6);
                    } 
                    else if (!maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 22);
                    } 
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && !maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 23);
                    } 
                    else if (!maze.isWall(levelToRender, mazeX - 1, mazeY) && !maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && !maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 3);
                    } 
                    else if (!maze.isWall(levelToRender, mazeX - 1, mazeY) && !maze.isWall(levelToRender, mazeX + 1, mazeY) && !maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 1);
                    } 
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {  // 4 corners
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 7);
                    } 
                    else if (!maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && !maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {  // corners
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 24);
                    } 
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && !maze.isWall(levelToRender, mazeX + 1, mazeY) && !maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 25);
                    } 
                    else if (!maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && !maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 26);
                    } 
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && !maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && !maze.isWall(levelToRender, mazeX, mazeY + 1)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 27);
                    } 
                    else if (maze.isWall(levelToRender, mazeX, mazeY)) {
                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 0);
                    }
                }
                else if (maze.getCell(level, mazeX, mazeY) == CellTypes::Stairs) {

                    if (maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && !maze.isWall(levelToRender, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 28);

                    }
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && !maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 29);

                    }
                    else if (maze.isWall(levelToRender, mazeX - 1, mazeY) && !maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 30);

                    }
                    else if (!maze.isWall(levelToRender, mazeX - 1, mazeY) && maze.isWall(levelToRender, mazeX + 1, mazeY) && maze.isWall(levelToRender, mazeX, mazeY - 1) && maze.isWall(levelToRender, mazeX, mazeY + 1)) {

                        Sprites::drawSelfMasked((mazeX * tileSize_Small) - camera_Small.x, (mazeY * tileSize_Small) - camera_Small.y, Images::Blocks_Small, 31);

                    }

                }

            }

        }

    }
    
}

void drawChests(uint8_t level) {

    for (int i = 0; i < Constants::MaxChests; i++) {

        Item &chest = maze.getChest(i);

        if (chest.level == level && chest.isActive()) {
            Sprites::drawSelfMasked((chest.x * tileSize) - camera.x, (chest.y * tileSize) - camera.y, Images::Chest, 0);
        }

    }

}

void drawChests_Small(uint8_t levelToRender) {

    uint8_t idx = (arduboy.frameCount / 4) % 2;

    for (int i = 0; i < Constants::MaxChests; i++) {

        Item &chest = maze.getChest(i);

        if (chest.level == levelToRender && chest.isActive()) {
            Sprites::drawSelfMasked((chest.x * 4) - camera_Small.x, (chest.y * 4) - camera_Small.y, Images::Chest_Small, idx);
        }

    }

}


void drawPlayer() {

    if (!player.isDead()) {

        if (player.isHoldingGun()) {

            switch (player.dir) {
            
                case 0:
                    Sprites::drawExternalMask(player.x - camera.x, player.y - camera.y, Images::Player_Gun_00, Images::Player_Gun_00_Mask, 0, 0);
                    break;
            
                case 1:
                    Sprites::drawExternalMask(player.x - camera.x - 2, player.y - camera.y, Images::Player_Gun_01, Images::Player_Gun_01_Mask, 0, 0);
                    break;
            
                case 2:
                    Sprites::drawExternalMask(player.x - camera.x, player.y - camera.y, Images::Player_Gun_02, Images::Player_Gun_02_Mask, 0, 0);
                    break;
            
                case 3:
                    Sprites::drawExternalMask(player.x - camera.x - 1, player.y - camera.y, Images::Player_Gun_03, Images::Player_Gun_03_Mask, 0, 0);
                    break;

            }

            if (menu.direction == MenuDirection::None) {
                Sprites::drawErase(0, 0, Images::MenuItema_Gun_Mask, 0);
                Sprites::drawSelfMasked(1, 0, Images::MenuItems_Gun, player.getBulletCount());
            }

        }
        else {

            uint8_t idx = player.dir * 2 + (((player.x + player.y) % 8) < 4);
            Sprites::drawExternalMask(player.x - camera.x, player.y - camera.y, Images::Player, Images::Player_Mask, idx, idx);

        }

    }

}

void drawPlayer_Small() {

    if (level == mapLevel && arduboy.frameCount % 16 < 8) {
        Sprites::drawSelfMasked((player.x / 3) - camera_Small.x, (player.y / 3) - camera_Small.y, Images::Player_Small, 0);
    }

}


void drawPuff() {

    if (puff.isActive()) {

        uint8_t idx = 6 - (puff.data / 2);

        Sprites::drawExternalMask(puff.x - camera.x, puff.y - camera.y, Images::Puff, Images::Puff_Mask, idx, idx);

        puff.data--;
        
        if (puff.data < 0) {
            puff.x= 0;
            puff.y = 0;
            puff.itemType = ItemType::None;
        }
    
    }

}


void drawDeath() {

    if (death.isActive()) {

        uint8_t idx = death.data < 6 ? 0 : (death.data - 6) / 2;

        Sprites::drawExternalMask(death.x - camera.x, death.y - camera.y, Images::Gravestone, Images::Gravestone_Mask, idx, idx);

        death.data++;
        
        if (death.data == 30) {
            death.x= 0;
            death.y = 0;

            if (death.itemType == ItemType::Death_Player) {
                gameState = GameState::GameOver;
            }

            death.itemType = ItemType::None;

        }
    
    }

}

void drawEnemies(uint8_t level) {

    for (int i = 0; i < Constants::MaxEnemys; i++) {

        Enemy &enemy = maze.getEnemy(i);

        if (enemy.isActive() && enemy.level == level) {

            if (enemy.x - camera.x >= -12 && enemy.x - camera.x < 128 && enemy.y - camera.y > -12 && enemy.y - camera.y < 64) {

                uint8_t idx = enemy.dir * 2 + (((enemy.x + enemy.y) % 8) < 4);
                Sprites::drawSelfMasked(enemy.x - camera.x, enemy.y - camera.y, Images::Enemy_Img, idx);

            }

            else {
            
                if (showEnemyCursors == 0 && gameState == GameState::GamePlay && arduboy.frameCount %16 < 8) {
                    
                    int16_t x = enemy.x - camera.x;
                    int16_t y = enemy.y - camera.y;
                    uint8_t idx = 0;

                    if (x < -64 || x > 128 + 64 || y < -64 || y > 64 + 64) {
                    
                        idx = 1;
                        
                    }

                    // Off left hand side ..

                    if (x < -12 && y < 0) {

                        Sprites::drawOverwrite(-5, -2, Images::Cursor, idx);

                    }
                
                    else if (x < -12 && y >= 0 && y < 64) {

                        Sprites::drawOverwrite(-5, y + 2, Images::Cursor, idx);

                    }
                
                    else if (x < -12 && y >= 64) {

                        Sprites::drawOverwrite(-5, 61, Images::Cursor, idx);

                    }
                
                    // Off top

                    else if (x > -12 && x < 128 && y < 0) {

                        Sprites::drawOverwrite(x + 2, -5, Images::Cursor, idx);

                    }
                
                    // Off Bottom

                    else if (x > -12 && x < 128 && y > 64) {

                        Sprites::drawOverwrite(x + 2, 61, Images::Cursor, idx);

                    }


                    // Off right hand side ..
                    
                    else if (x >= 128 && y < 0) {

                        Sprites::drawOverwrite(125, -4, Images::Cursor, idx);

                    }

                    else if (x >= 128 && y >= 0 && y < 64) {

                        Sprites::drawOverwrite(125, y + 2, Images::Cursor, idx);

                    }

                    else if (x >= 128 && y >= 64) {

                        Sprites::drawOverwrite(125, 61, Images::Cursor, idx);

                    }

                }
            
            }

        }

    }

}


void drawEnemies_Small(uint8_t levelToRender) {

    for (int i = 0; i < Constants::MaxEnemys; i++) {

        Enemy &enemy = maze.getEnemy(i);

        if (enemy.isActive() && enemy.level == levelToRender) {
            Sprites::drawSelfMasked((enemy.x / 3) - camera_Small.x, (enemy.y / 3) - camera_Small.y, Images::Player_Small, 0);
        }

    }

}

 
void drawItems(uint8_t level) {

    for (int i = 0; i < Constants::MaxItems; i++) {

        Item &item = maze.getItem(i);

        if (item.isActive() && item.level == level) {

            switch (item.itemType) {
            
                case ItemType::Gun:
                    Sprites::drawSelfMasked(item.x - camera.x, item.y - camera.y, Images::Gun, 0);
                    break;
            
                case ItemType::Bullets:
                    Sprites::drawSelfMasked(item.x - camera.x, item.y - camera.y, Images::Bullets, 0);
                    break;
            
                case ItemType::Bomb:
                    Sprites::drawSelfMasked(item.x - camera.x, item.y - camera.y, Images::Bomb, 8);
                    break;
            
                case ItemType::Key:
                    Sprites::drawSelfMasked(item.x - camera.x, item.y - camera.y, Images::MenuItems, 6);
                    break;
            
                case ItemType::Bomb_Active:
                    {
                        uint8_t idx = item.data / 6;
                        if (idx > 8) idx = 8;

                        Sprites::drawSelfMasked(item.x - camera.x, item.y - camera.y, Images::Bomb, idx);

                        if (arduboy.frameCount % 5 < 2) { 

                            uint8_t i = item.data / 6;
                            uint8_t xOffset = pgm_read_byte(Constants::BombX + i);
                            uint8_t yOffset = pgm_read_byte(Constants::BombY + i);
                            Sprites::drawSelfMasked(item.x - camera.x + 7 - xOffset, item.y - camera.y - 3 + yOffset, Images::Bomb_Flame, ((item.data / 3) % 4));

                        }

                        item.data--;

                        if (item.data == 8) {

                            puff.x = item.x - 3;
                            puff.y = item.y - 1;
                            puff.data = 6 * 2;
                            puff.itemType = ItemType::Puff_Bomb;
                            
                        }
                        else if (item.data == 0) {
                        
                            item.x = 0;
                            item.y = 0;

                        }

                    }
                    
                    break;

            }

        }

    }

}

void drawMenu() {

    arduboy.fillRect(menu.x, 0, 30, 64, BLACK);
    arduboy.drawFastVLine(menu.x + 1, 0, 64, WHITE);


    if (menu.top > 0) {
    
        Sprites::drawSelfMasked(menu.x + 8, 1, Images::MenuArrows, 0);

    }
    else {

        Sprites::drawSelfMasked(menu.x + 8, 1, Images::MenuArrows, 1);
    
    }

    uint8_t y = 10;

    for (uint8_t i = menu.top; i < menu.top + 3; i++) {
        
        if (i < player.getInventoryCount()) {

            if (player.getInventoryItem(i) != ItemType::Gun) {

                Sprites::drawSelfMasked(menu.x + 6, y, Images::MenuItems, static_cast<uint8_t>(player.getInventoryItem(i)));

            }
            else {

                Sprites::drawSelfMasked(menu.x + 6, y, Images::MenuItems_Gun, player.getBulletCount());

            }

        }
        y = y + 16;

    }

    if (arduboy.frameCount % 24 < 12) {
        Sprites::drawSelfMasked(menu.x + 4, 8 + ((menu.y - menu.top) * 16), Images::MenuCursor, 0);
    }

    if (player.getInventoryCount() < 3 || player.getInventoryCount() == menu.top + 3) {
        Sprites::drawSelfMasked(menu.x + 8, 55, Images::MenuArrows, 3);
    }
    else {
        Sprites::drawSelfMasked(menu.x + 8, 55, Images::MenuArrows, 2);
    }

    if (menu.direction == MenuDirection::Openning && menu.x > 128 - 22) {
    
        menu.x = menu.x - 2;

        if (menu.x == 128 - 22) {
        
            menu.direction = MenuDirection::None;

        }

    }

    if (menu.direction == MenuDirection::Closing) {
    
        if (menu.x < 128) {
    
            menu.x = menu.x + 2;

            if (menu.x == 128) {
            
                menu.direction = MenuDirection::None;
                gameState = GameState::GamePlay;
                    
            }

        }

    }

}


void drawBullet() {

    if (bullet.isActive()) {
    
        if (bullet.itemType == ItemType::Bullet_Normal) {

            arduboy.drawPixel(bullet.x - camera.x, bullet.y - camera.y, WHITE);

            switch (bullet.data) {
            
                case 0:
                    bullet.y = bullet.y - 4;
                    break;
            
                case 1:
                    bullet.x = bullet.x + 4;
                    break;
            
                case 2:
                    bullet.y = bullet.y + 4;
                    break;
            
                case 3:
                    bullet.x = bullet.x - 4;
                    break;
                    
            }

            if (!maze.isWalkable(level, bullet.x  / tileSize, bullet.y / tileSize)) {

                bullet.reset();
                
            }

            if (player.getBulletCount() == 0) {
            
                uint8_t bulletIdx = player.getItemIdx(ItemType::Bullets);

                if (bulletIdx != Constants::NoItem) {

                    player.removeItem(bulletIdx);
                    player.setBulletCount(2);

                }

            }

        }
        else if (bullet.itemType == ItemType::Bullet_None) {

            Sprites::drawExternalMask(bullet.x - camera.x, bullet.y - camera.y, Images::Click, Images::Click_Mask, 0, 0);

            bullet.data = bullet.data - 1;

            if (bullet.data == 0) {

                bullet.reset();
                player.setHoldingGun(false);

            }
        
        }

    }

}
