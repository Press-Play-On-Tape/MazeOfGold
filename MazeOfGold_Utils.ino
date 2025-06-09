#include <Arduboy2Core.h>
#include <Sprites.h>


void updateEnemys(uint8_t level) {

    for (int i = 0; i < Constants::MaxEnemys; i++) {

        Enemy &enemy = maze.getEnemy(i);

        if (!enemy.isActive()) continue;

        if ((enemy.x % tileSize == 0) && (enemy.y % tileSize == 0)) {

            int testX = enemy.x + (Constants::DirectionOffsetX[enemy.dir] * tileSize);
            int testY = enemy.y + (Constants::DirectionOffsetY[enemy.dir] * tileSize);

            bool forwardClear = (maze.getCell(enemy.level, testX / tileSize, testY / tileSize) == 0);
            bool wantTurn = (random(100) < 20);

            if (!forwardClear || wantTurn) {

                int dirs[2] = {(enemy.dir + 1) % 4, (enemy.dir + 3) % 4};

                if (random(2) == 0) {
                    int temp = dirs[0];
                    dirs[0] = dirs[1];
                    dirs[1] = temp;
                }

                bool moved = false;

                for (int d = 0; d < 2; d++) {

                    int newDir = dirs[d];
                    int newX = enemy.x + (Constants::DirectionOffsetX[newDir] * tileSize);
                    int newY = enemy.y + (Constants::DirectionOffsetY[newDir] * tileSize);

                    if (maze.getCell(enemy.level, newX / tileSize, newY / tileSize) == 0) {

                        if (!(newX == enemy.lastX && newY == enemy.lastY)) {

                            enemy.lastX = enemy.x;
                            enemy.lastY = enemy.y;
                            enemy.dir = newDir;

                            switch (enemy.dir) {
                            
                                case 0:
                                case 2:
                                    enemy.y += Constants::DirectionOffsetY[enemy.dir] * 2;
                                    break;

                                default:
                                    enemy.x += Constants::DirectionOffsetX[enemy.dir] * 2;
                                    break;

                            }

                            moved = true;
                            break;

                        }
                    }
                }

                if (!moved && forwardClear) {

                    enemy.lastX = enemy.x;
                    enemy.lastY = enemy.y;
                    enemy.x += Constants::DirectionOffsetX[enemy.dir] * 2;
                    enemy.y += Constants::DirectionOffsetY[enemy.dir] * 2;

                } 
                else if (!moved) {

                    enemy.dir = (enemy.dir + 2) % 4;
                    enemy.lastX = enemy.x;
                    enemy.lastY = enemy.y;
                    enemy.x += Constants::DirectionOffsetX[enemy.dir] * 2;
                    enemy.y += Constants::DirectionOffsetY[enemy.dir] * 2;
                }

            } 
            else {

                enemy.lastX = enemy.x;
                enemy.lastY = enemy.y;
                enemy.x += Constants::DirectionOffsetX[enemy.dir] * 2;
                enemy.y += Constants::DirectionOffsetY[enemy.dir] * 2;

            }

        } 
        else {

            // Continue movement ..

            int forwardX = enemy.x + (Constants::DirectionOffsetX[enemy.dir] * 2);
            int forwardY = enemy.y + (Constants::DirectionOffsetY[enemy.dir] * 2);

            enemy.lastX = enemy.x;
            enemy.lastY = enemy.y;
            enemy.x = forwardX;
            enemy.y = forwardY;

        }

    }

}

void checkCollisions(uint8_t level) {

    Rect playerRect;
    playerRect.x = player.x + 1;
    playerRect.y = player.y;
    playerRect.width = 10;
    playerRect.height = 12;

    for (int i = 0; i < Constants::MaxChests; i++) {

        Item &chest = maze.getChest(i);
        Rect chestRect;

        if (chest.level != level) continue;

        chestRect.x = chest.x * tileSize;
        chestRect.y = chest.y * tileSize;
        chestRect.width = 12;
        chestRect.height = 12;

        if (arduboy.collide(chestRect, playerRect) && chest.isActive()) { 

            chest.x = 0;
            chest.y = 0;

            maze.setActiveChests(maze.getActiveChests() - 1);

            if (maze.getActiveChests() == 0) {
                gameState = GameState::LevelUp;
            }
            else {
            
                displayChests = 12;

            }
        
        }

    }


    for (int i = 0; i < Constants::MaxEnemys; i++) {

        Enemy &enemy = maze.getEnemy(i);
        Rect enemyRect;

        if (enemy.level != level || !enemy.isActive()) continue;

        enemyRect.x = enemy.x + 1;
        enemyRect.y = enemy.y;
        enemyRect.width = 10;
        enemyRect.height = 12;

        if (arduboy.collide(enemyRect, playerRect)) { 

            death.x = player.x;
            death.y = player.y;
            death.itemType = ItemType::Death_Player;
            death.data = 0;            
            player.setDead(true);
            
        }

    }

    for (int i = 0; i < Constants::MaxItems; i++) {

        Item &item = maze.getItem(i);
        Rect itemRect;

        if (item.level != level || !item.isActive()) continue;

        switch (item.itemType) {

            case ItemType::Bomb:
                {
                    itemRect.x = item.x + 1;
                    itemRect.y = item.y;
                    itemRect.width = 10;
                    itemRect.height = 12;

                    if (arduboy.collide(itemRect, playerRect)) { 

                        if (player.addItem(item.itemType)) {

                            item.x = 0;
                            item.y = 0;

                        }
                        
                    }

                }

                break;

        }

    }


    // Puff .. caused by bomb.

    if (puff.isActive() && puff.itemType == ItemType::Puff_Bomb) {

        Rect puffRect;
        puffRect.x = puff.x + 1;
        puffRect.y = puff.y;
        puffRect.width = 12;
        puffRect.height = 12;

        if (arduboy.collide(puffRect, playerRect)) { 

            death.x = player.x;
            death.y = player.y;
            death.itemType = ItemType::Death_Player;
            death.data = 0;            
            player.setDead(true);

        }
        else {
            
            for (int i = 0; i < Constants::MaxEnemys; i++) {

                Enemy &enemy = maze.getEnemy(i);
                Rect enemyRect;

                if (enemy.level != level || !enemy.isActive()) continue;

                enemyRect.x = enemy.x + 1;
                enemyRect.y = enemy.y;
                enemyRect.width = 10;
                enemyRect.height = 12;

                if (arduboy.collide(enemyRect, puffRect)) { 

                    death.x = enemy.x;
                    death.y = enemy.y;
                    death.itemType = ItemType::Death_Enemy;
                    death.data = 0;

                    enemy.x = 0;
                    enemy.y = 0;

                }

            }

        }

    }

}


void updatePlayer() {

	uint8_t tileX = player.x / tileSize;
	uint8_t tileY = player.y / tileSize;


    if (player.isDead()) return;


	if (player.vx == 0 && player.vy == 0 && player.x % tileSize == 0 && player.y % tileSize == 0) {

		if (arduboy.pressed(LEFT_BUTTON) && maze.isWalkable(level, tileX - 1, tileY)) {
			player.vx = -2;
			player.dir = 3;
		} 
		else if (arduboy.pressed(RIGHT_BUTTON) && maze.isWalkable(level, tileX + 1, tileY)) {
			player.vx = 2;
			player.dir = 1;
		} 
		else if (arduboy.pressed(UP_BUTTON) && maze.isWalkable(level, tileX, tileY - 1)) {
			player.vy = -2;
			player.dir = 0;
		} 
		else if (arduboy.pressed(DOWN_BUTTON) && maze.isWalkable(level, tileX, tileY + 1)) {
			player.vy = 2;
			player.dir = 2;
		}
		else if (arduboy.pressed(B_BUTTON)) {

			menu.direction = MenuDirection::Openning;
			menu.x = 128;
			gameState = GameState::ShowMenu;

		}
		
	}

	player.x += player.vx;
	player.y += player.vy;

	// Stop when aligned with grid ..

	bool stop = false;

	if (player.vx != 0 && player.x % tileSize == 0) { 
		player.vx = 0;
		stop = true;
	}

	if (player.vy != 0 && player.y % tileSize == 0) {
		player.vy = 0;
		stop = true;
	}

	if (stop) {

		tileX = player.x / tileSize;
		tileY = player.y / tileSize;

		if (maze.getCell(level, tileX, tileY) == 2) {

            puff.x = player.x;
            puff.y = player.y;
            puff.data = 2 * 6;
            puff.itemType = ItemType::Puff_Stairs;
			level = !level;
		}

	}

}

void updateCamera() {

	camera.x = player.x  - (WIDTH / 2) + (tileSize / 2);
	camera.y = player.y  - (HEIGHT / 2) + (tileSize / 2);

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;

	int maxCameraX = Constants::MazeWidth * tileSize - WIDTH;
	int maxCameraY = Constants::MazeHeight * tileSize - HEIGHT;

	if (camera.x > maxCameraX) camera.x = maxCameraX;
	if (camera.y > maxCameraY) camera.y = maxCameraY;

}
