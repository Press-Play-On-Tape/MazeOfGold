#include <Arduboy2.h>
#include <Sprites.h>

void handleMenu_MoveUp() {

    if (player.getInventoryCount() == 0) {
        menu.y = 0;
        menu.top = 0;
    }
    else if (menu.y == 0 && menu.top == 0) {
        // do nothing
    }
    else if (player.getInventoryCount() == menu.y + 1) {
        menu.y--;
    }
    else if (menu.top > 0) {
        menu.top--;
        menu.y--;
    }
    else if (menu.y >= 1 && menu.top == 0) {
        menu.y--;
    }
    else if (menu.y ==  player.getInventoryCount() - 1) {
        menu.y--;
    }
    else if (menu.y <  player.getInventoryCount() - 1) {
        menu.y--;
        menu.top--;
    }
    
}

void handleMenu_MoveDown() {

    if (player.getInventoryCount() == 0) {
        menu.y = 0;
        menu.top = 0;
    }
    else if (menu.y == 0 && player.getInventoryCount() > 1) {
        menu.y++;
    }
    else if (menu.y <  player.getInventoryCount() - 2) {
        menu.y++;
        menu.top++;
    }
    else if (menu.y <  player.getInventoryCount() - 1) {
        menu.y++;
    }

}

void handleMenu() {


    // updatePlayer();
    updateCamera();

    if (arduboy.frameCount % 2 == 0) {  // enemies move slower
        updateEnemys(level);
    }

    checkCollisions(level);

    drawMaze(level);
    drawChests(level);
    drawEnemies(level);
    drawItems(level);
    drawPlayer();
    drawChestCount(0, 0);
    drawMenu();


    if (arduboy.justPressed(UP_BUTTON)) {

        handleMenu_MoveUp();

    }

    if (arduboy.justPressed(DOWN_BUTTON)) {

        handleMenu_MoveDown();

    }

    if (arduboy.justPressed(A_BUTTON)) {

        switch (player.getInventoryItem(menu.y)) {
        
            case ItemType::Map:
                mapLevel = level;
                gameState = GameState::Map;
                break;
        
            case ItemType::Bomb:
                
                Item &item = maze.getItem(2);
                item.x = player.x;
                item.y = player.y;
                item.itemType = ItemType::Bomb_Active;
                item.data = (13 * 9) - 1;
                player.removeItem(menu.y);
                menu.direction = MenuDirection::Closing;

                handleMenu_MoveUp();

                break;

        }

    }

    if (arduboy.justPressed(B_BUTTON)) {
        menu.direction = MenuDirection::Closing;
    }
    
}

void handleMenu_ShowMap() {

    if (arduboy.frameCount % 2 == 0) {  // enemies move slower
        updateEnemys(level);
    }

    checkCollisions(level);

    drawMaze_Small(mapLevel);
    drawChests_Small(mapLevel);
    drawEnemies_Small(mapLevel);
    drawPlayer_Small();

    Sprites::drawOverwrite(92, 2, Images::HUD_Maze, mapLevel);
    drawChestCount(102, 16);

    if (arduboy.pressed(LEFT_BUTTON)) {
        mapLevel = 0;
    }
    if (arduboy.pressed(RIGHT_BUTTON)) {
        mapLevel = 1;
    }

    if (arduboy.pressed(UP_BUTTON) && camera_Small.y > 0) {
        camera_Small.y--;
    }

    if (arduboy.pressed(DOWN_BUTTON) && camera_Small.y < 26) {
        camera_Small.y++;
    }

    if (arduboy.justPressed(B_BUTTON)) {
        gameState = GameState::ShowMenu;
        menu.direction = MenuDirection::Closing;
    }

}