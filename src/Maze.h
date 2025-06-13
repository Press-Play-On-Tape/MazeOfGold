#pragma once

#include "Constants.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"

class Maze {

    private:

        uint8_t maze[Constants::MazeHeight][Constants::MazeWidth]; 
        Item chests[Constants::MaxChests];
        Enemy enemies[Constants::MaxEnemys];
        Item items[Constants::MaxItems];
        uint8_t activeChests = 0;
        uint8_t enemyCount = 2;

    private:

        void push(uint8_t *stack, int &stackSize, int x, int y) {

            stack[stackSize++] = x;
            stack[stackSize++] = y;

        }

        void pop(uint8_t *stack, int &stackSize, int &x, int &y) {

            stackSize -= 2;
            x = stack[stackSize];
            y = stack[stackSize + 1];

        }


        bool isChestLocatedHere(uint8_t level, uint8_t iLow, uint8_t iHigh, uint8_t x, uint8_t y) {

            if (iHigh == 255)       return false;
            if ( x < 0 || y < 0)    return false;

            for (uint8_t i = iLow; i <= iHigh; i++) {

                Item &chest = this->chests[i];

                if (chest.level == level && chest.x == x && chest.y == y) {

                    return true;

                }

            }

            return false;

        }


        void generateMaze_Clear() {

            for (int y = 0; y < Constants::MazeHeight; y++) {
                for (int x = 0; x < Constants::MazeWidth; x++) {
                    maze[y][x] = 16 + 1; 
                }
            }

        }

        void generateMaze_OneLevel(uint8_t exitType, uint8_t level, uint8_t *buffer) {

            memset(buffer, 0, 1024);

            int x = 1;
            int y = 1;
            this->setCell(level, x, y, CellTypes::Empty);

            if (exitType == 1) {
                this->setCell(level, 1, 21, CellTypes::Empty);
                this->setCell(level, 2, 21, CellTypes::Empty);
                this->setCell(level, 3, 21, CellTypes::Empty);
                this->setCell(level, 4, 21, CellTypes::Empty);
            }
            else if (exitType == 2) {
                this->setCell(level, 18, 1, CellTypes::Empty);
                this->setCell(level, 19, 1, CellTypes::Empty);
                this->setCell(level, 20, 1, CellTypes::Empty);
                this->setCell(level, 21, 1, CellTypes::Empty);
            }
            else if (exitType == 3) {
                this->setCell(level, 21, 18, CellTypes::Empty);
                this->setCell(level, 21, 19, CellTypes::Empty);
                this->setCell(level, 21, 20, CellTypes::Empty);
                this->setCell(level, 21, 21, CellTypes::Empty);
            }

            uint8_t *stack = buffer;
            int stackSize = 0;

            push(stack, stackSize, x, y);

            while (stackSize > 0) {
                
                pop(stack, stackSize, x, y);
                int neighbors[4];
                int nCount = 0;

                for (int dir = 0; dir < 4; dir++) {

                    int nx = x + Constants::DirectionOffsetX[dir] * 2;
                    int ny = y + Constants::DirectionOffsetY[dir] * 2;

                    if (nx > 0 && ny > 0 && nx < Constants::MazeWidth && ny < Constants::MazeHeight) {
                                    
                        if (this->getCell(level, nx, ny) == 1) {
                            neighbors[nCount++] = dir;
                        }
                    
                    }

                }

                if (nCount > 0) {

                    push(stack, stackSize, x, y);

                    int dir = neighbors[random(nCount)];
                    int nx = x + Constants::DirectionOffsetX[dir] * 2;
                    int ny = y + Constants::DirectionOffsetY[dir] * 2;

                    this->setCell(level, x + Constants::DirectionOffsetX[dir], y + Constants::DirectionOffsetY[dir], 0);	// remove wall
                    this->setCell(level, nx, ny, 0);

                    push(stack, stackSize, nx, ny);

                }

            }


            // Punch holes through walls ..

            for (uint8_t i = 0; i < 10; i++) {

                while (true) {

                    uint8_t x = random(1, Constants::MazeWidth - 1);
                    uint8_t y = random(1, Constants::MazeHeight - 4);

                    if (this->getCell(level, x, y) == CellTypes::Wall && 

                        ((this->getCell(level, x, y - 1) == CellTypes::Wall && 
                          this->getCell(level, x, y + 1) == CellTypes::Wall && 
                          this->getCell(level, x - 1, y) == CellTypes::Empty && 
                          this->getCell(level, x + 1, y) == CellTypes::Empty) || 

                         (this->getCell(level, x, y - 1) == CellTypes::Empty && 
                          this->getCell(level, x, y + 1) == CellTypes::Empty && 
                          this->getCell(level, x - 1, y) == CellTypes::Wall && 
                          this->getCell(level, x + 1, y) == CellTypes::Wall))

                       ) {

                        if (exitType == 1 && x <= 4 && y == 20 )            { /* Do nothing */ }
                        else if (exitType == 2 && x >= 18 && y == 2)        { /* Do nothing */ }
                        else if (exitType == 3 && x == 20 && y >= 18)       { /* Do nothing */ }
                        else {

                            this->setCell(level, x, y, CellTypes::Empty);
                            break;

                        }

                    }

                }

            }


            if (exitType == 1 && level == 0) {

                this->setCell(level, 3, 21, CellTypes::GateClosed);

            }
            else if (exitType == 2 && level == 0) {

                this->setCell(level, 19, 1, CellTypes::GateClosed);

            }
            else if (exitType == 3 && level == 0) {

                this->setCell(level, 21, 19, CellTypes::GateClosed);

            }

        }

        uint8_t generateMaze_Stairs(uint8_t exitType, uint8_t l1, uint8_t l2) {
        
            uint8_t stairsPlaced = 0;

            if (exitType == 0) {

                for (int y = 1; y < Constants::MazeHeight - 1; y++) {

                    for (int x = 1; x < Constants::MazeWidth - 1; x++) {

                        if (x == 1 && y == 1) { continue;}

                        if (!this->isWall(l1, x, y) && !this->isWall(1, x, y)) {

                            if ((!this->isWall(l1, x - 1, y) && this->isWall(l1, x, y - 1)  && this->isWall(l1, x + 1, y)  && this->isWall(l1, x, y + 1)) ||
                                (this->isWall(l1, x - 1, y)  && !this->isWall(l1, x, y - 1) && this->isWall(l1, x + 1, y)  && this->isWall(l1, x, y + 1)) ||
                                (this->isWall(l1, x - 1, y)  && this->isWall(l1, x, y - 1)  && !this->isWall(l1, x + 1, y) && this->isWall(l1, x, y + 1)) ||
                                (this->isWall(l1, x - 1, y)  && this->isWall(l1, x, y - 1)  && this->isWall(l1, x + 1, y)  && !this->isWall(l1, x, y + 1))) {

                                if ((!this->isWall(l2, x - 1, y) && this->isWall(l2, x, y - 1)  && this->isWall(l2, x + 1, y)  && this->isWall(l2, x, y + 1)) ||
                                    (this->isWall(l2, x - 1, y)  && !this->isWall(l2, x, y - 1) && this->isWall(l2, x + 1, y)  && this->isWall(l2, x, y + 1)) ||
                                    (this->isWall(l2, x - 1, y)  && this->isWall(l2, x, y - 1)  && !this->isWall(l2, x + 1, y) && this->isWall(l2, x, y + 1)) ||
                                    (this->isWall(l2, x - 1, y)  && this->isWall(l2, x, y - 1)  && this->isWall(l2, x + 1, y)  && !this->isWall(1, x, y + 1))) {

                                    this->setCell(0, x, y, 2);
                                    this->setCell(1, x, y, 2);
                                    stairsPlaced++;

                                }                            

                            }

                        }

                    }

                }

            }
            else if (exitType == 1) {

                this->setCell(0, 1, 21, CellTypes::Stairs);
                this->setCell(1, 1, 21, CellTypes::Stairs);
                stairsPlaced++;          

            }
            else if (exitType == 2) {

                this->setCell(0, 21, 1, CellTypes::Stairs);
                this->setCell(1, 21, 1, CellTypes::Stairs);
                stairsPlaced++;          

            }
            else if (exitType == 3) {

                this->setCell(0, 21, 21, CellTypes::Stairs);
                this->setCell(1, 21, 21, CellTypes::Stairs);
                stairsPlaced++;          

            }

            return stairsPlaced;
        
        }


        void spawnChests(uint8_t level, uint8_t iLow, uint8_t iHigh) {

            for (uint8_t i = iLow; i <= iHigh; i++) {

                int x, y;
                
                do {

                    x = random(1, Constants::MazeWidth - 1);
                    y = random(1, Constants::MazeHeight - 1);

                } while (this->getCell(level, x, y) != CellTypes::Empty
                         || this->getCell(level, x - 1, y) == CellTypes::Stairs
                         || this->getCell(level, x + 1, y) == CellTypes::Stairs
                         || this->getCell(level, x, y - 1) == CellTypes::Stairs
                         || this->getCell(level, x, y - 2) == CellTypes::Stairs
                         || this->isChestLocatedHere(level, iLow, i - 1, x, y)
                         || this->isChestLocatedHere(level, iLow, i - 1, x - 1, y)
                         || this->isChestLocatedHere(level, iLow, i - 1, x + 1, y)
                         || this->isChestLocatedHere(level, iLow, i - 1, x, y - 1)
                         || this->isChestLocatedHere(level, iLow, i - 1, x, y + 1)
                );

                chests[i].level = level;
                chests[i].x = x;
                chests[i].y = y;
                chests[i].itemType = ItemType::None;
            
            }

            activeChests = Constants::MaxChests;
        }

        void clearEnemys() {

            for (int i = 0; i < Constants::MaxEnemys; i++) {

                Enemy &enemy = enemies[i];
                enemy.x = 0;
                enemy.y = 0;
                enemy.dir = 0;
                
            }

        }

        void spawnEnemys(uint8_t level, uint8_t iLow, uint8_t iHigh) {

            for (uint8_t i = iLow; i < iHigh; i++) {

                int x, y;

                do {
                
                    x = random(4, Constants::MazeWidth);
                    y = random(4, Constants::MazeHeight);

                } while (this->getCell(level, x, y) != CellTypes::Empty);

                Enemy &enemy = enemies[i];
                enemy.level = level;
                enemy.x = x * tileSize;
                enemy.y = y * tileSize;
                enemy.vx = 0;
                enemy.vy = 0;
                enemy.lastX = enemy.x;
                enemy.lastY = enemy.y;
                enemy.dir = random(4);

            }

        }

        void spawnItems(Player &player, uint8_t exitType, uint8_t level, uint8_t iLow, uint8_t iHigh) {

            for (uint8_t i = iLow; i < iHigh; i++) {

                int x, y;

                do {

                    x = random(5, Constants::MazeWidth - 1);
                    y = random(5, Constants::MazeHeight - 1);

                } while (this->getCell(level, x, y) != CellTypes::Empty ||
                         (exitType == 1 && x == 2 && y == 21) ||
                         (exitType == 2 && x == 20 && y == 1) ||
                         (exitType == 3 && x == 21 && y == 20));
                

                ItemType rnd = ItemType::None;

                bool hasBomb = player.getItemIdx(ItemType::Bomb) != Constants::NoItem;
                bool hasGun = player.getItemIdx(ItemType::Gun) != Constants::NoItem;

                if (exitType == 0 || iLow > 0) {

                    uint8_t maxRnd = (hasBomb && hasGun ? 6 : 2);
                    maxRnd = random(0, maxRnd);      

                    if (maxRnd == 0) {

                        if (!hasGun && hasBomb) {

                            rnd = random(0, 2) == 0 ? ItemType::Gun : ItemType::Bullets;

                        }
                        else if (hasGun && !hasBomb) {

                            rnd = random(0, 2) == 0 ? ItemType::Bomb : ItemType::Bullets;

                        }
                        else if (hasGun && hasBomb) {

                            rnd = random(0, 2) == 0 ? ItemType::Bomb : ItemType::Bullets;

                        }
                        else {

                            rnd = random(0, 2) == 0 ? ItemType::Gun : ItemType::Bomb;
                        
                        }

                    }

                }
                else {
                
                    rnd = ItemType::Key;

                }

                Item &item = this->items[i];
                item.level = level;
                item.x = x * tileSize;
                item.y = y * tileSize;
                item.itemType = rnd;
            
            }

        }


    public:

        Maze() { }


        uint8_t getEnemyCount()                     { return this->enemyCount; }
        uint8_t getActiveChests()                   { return this->activeChests; }

        Item &getChest(uint8_t idx)                 { return this->chests[idx]; }
        Item &getItem(uint8_t idx)                  { return this->items[idx]; }
        Enemy &getEnemy(uint8_t idx)                { return this->enemies[idx]; }
        
        void setEnemyCount(uint8_t val)             { this->enemyCount = val; }
        void setActiveChests(uint8_t val)           { this->activeChests = val; }

        void setCell(uint8_t level, uint8_t x, uint8_t y, uint8_t value) {
        
            int byteIndex = (x + (level == 1 ? Constants::MazeWidth : 0)) / 2;

            if (x % 2 == 0) {
                maze[y][byteIndex] = (maze[y][byteIndex] & 0x0F) | (value << 4);
            } 
            else {
                maze[y][byteIndex] = (maze[y][byteIndex] & 0xF0) | (value & 0x0F);
            }

        }

        uint8_t getCell(uint8_t level, uint8_t x, uint8_t y) {

            if (x < 0 || x >= Constants::MazeWidth || y < 0 || y >= Constants::MazeHeight) {
                return 1; // Out of bounds, return wall
            }

            uint8_t byteIndex = (x + (level == 1 ? Constants::MazeWidth : 0)) / 2;

            if (x % 2 == 0) {
                return (maze[y][byteIndex] >> 4) & 0x0F;
            } 
            else {
                return maze[y][byteIndex] & 0x0F;
            }

        }

        bool isWall(uint8_t level, uint8_t x, uint8_t y) {

            if (x < 0 || x >= Constants::MazeWidth || y < 0 || y >= Constants::MazeHeight) {
                return true; 
            }

            uint8_t byteIndex = (x + (level == 1 ? Constants::MazeWidth : 0)) / 2;                     

            if (x % 2 == 0) {
                uint8_t wall = ((maze[y][byteIndex] >> 4) & 0x0F);
                return wall == CellTypes::Wall; 
            } 
            else {
                uint8_t wall = (maze[y][byteIndex] & 0x0F);
                return wall == CellTypes::Wall;
            }

        }

        bool isWalkable(uint8_t level, uint8_t x, uint8_t y) {

            if (x < 0 || x >= Constants::MazeWidth || y < 0 || y >= Constants::MazeHeight) {
                return false;
            }

            uint8_t byteIndex = (x + (level == 1 ? Constants::MazeWidth : 0)) / 2;

            if (x % 2 == 0) {
                uint8_t wall = ((maze[y][byteIndex] >> 4) & 0x0F);
                return wall == CellTypes::Empty || wall == CellTypes::Stairs || wall == CellTypes::GateOpen;
            } 
            else {
                uint8_t wall = (maze[y][byteIndex] & 0x0F);
                return wall == CellTypes::Empty || wall == CellTypes::Stairs || wall == CellTypes::GateOpen;
            }

        }

        void generateMaze(Player &player, uint8_t *buffer) {

            uint8_t stairsPlaced = 0;
            uint8_t exitType = random(0, 8);

            if (exitType != 1 && exitType != 2 && exitType !=3) {
                exitType = 0;
            }

            while (stairsPlaced < 1) {

                this->generateMaze_Clear();
                this->generateMaze_OneLevel(exitType, 0, buffer);
                this->generateMaze_OneLevel(exitType, 1, buffer);
                stairsPlaced = this->generateMaze_Stairs(exitType, 0, 1);

            }

            this->spawnChests(0, 0, 4);
            this->spawnChests(1, 5, 9);
            this->clearEnemys();
            this->spawnEnemys(0, 0, this->getEnemyCount());
            this->spawnEnemys(1, 6, 6 + this->getEnemyCount());
            this->spawnItems(player, exitType, 0, 0, 1);
            this->spawnItems(player, exitType, 1, 1, 2);                

        }


        uint8_t getEmptyItem() {

            for (uint8_t i = 0; i < Constants::MaxItems; i++) {

                if (!this->items[i].isActive()) return i;

            }

            return Constants::NoItem;

        }
};
