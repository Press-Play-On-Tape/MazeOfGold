#pragma once

#include "Constants.h"
#include "Enemy.h"
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

            int byteIndex = (x + (level == 1 ? Constants::MazeWidth : 0)) / 2;

            if (x % 2 == 0) {
                return (maze[y][byteIndex] >> 4) & 0x0F;
            } 
            else {
                return maze[y][byteIndex] & 0x0F;
            }

        }

        bool isWall(uint8_t level, uint8_t x, uint8_t y) {

            if (x < 0 || x >= Constants::MazeWidth || y < 0 || y >= Constants::MazeHeight) {
                return true; // Out of bounds, return wall
            }

            int byteIndex = (x + (level == 1 ? Constants::MazeWidth : 0)) / 2;

            if (x % 2 == 0) {
                return ((maze[y][byteIndex] >> 4) & 0x0F) == 1;
            } 
            else {
                return (maze[y][byteIndex] & 0x0F) == 1;
            }

        }

        bool isWalkable(uint8_t level, uint8_t x, uint8_t y) {

            if (x < 0 || x >= Constants::MazeWidth || y < 0 || y >= Constants::MazeHeight) {
                return false;
            }

            return !this->isWall(level, x, y);

        }

        void generateMaze_Clear() {

            for (int y = 0; y < Constants::MazeHeight; y++) {
                for (int x = 0; x < Constants::MazeWidth; x++) {
                    maze[y][x] = 16 + 1; 
                }
            }

        }

        void generateMaze(uint8_t level, uint8_t *buffer) {

            memset(buffer, 0, 1024);

            int x = 1;
            int y = 1;
            this->setCell(level, x, y, 0);

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

            for (uint8_t i = 0; i < 10; i++) {

                while (true) {

                    uint8_t x = random(1, Constants::MazeWidth - 1);
                    uint8_t y = random(1, Constants::MazeHeight - 1);

                    if (this->getCell(level, x, y)  == 1 && ((this->getCell(level, x, y - 1) == 1 && this->getCell(level, x, y + 1) == 1 && this->getCell(level, x - 1, y) == 0 && this->getCell(level, x + 1, y) == 0) || 
                        (this->getCell(level, x, y - 1) == 0 && this->getCell(level, x, y + 1) == 0 && this->getCell(level, x - 1, y) == 1 && this->getCell(level, x + 1, y) == 1))) {
                        this->setCell(level, x, y, 0);
                        break;
                    }

                }

            }

        }

        uint8_t generateMaze_Stairs(uint8_t l1, uint8_t l2) {
        
            uint8_t stairsPlaced = 0;

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

            return stairsPlaced;
        
        }


        void spawnChests(uint8_t level, uint8_t iLow, uint8_t iHigh) {

            for (int i = iLow; i <= iHigh; i++) {

                int x, y;
                
                do {

                    x = random(Constants::MazeWidth);
                    y = random(Constants::MazeHeight);

                } while (this->getCell(level, x, y) != 0);

                chests[i] = {level, x, y, ItemType::None};
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
                
                    x = random(5, Constants::MazeWidth);
                    y = random(5, Constants::MazeHeight);

                } while (this->getCell(level, x, y) != 0);

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

        void spawnItems(uint8_t level, uint8_t iLow, uint8_t iHigh) {

            for (uint8_t i = iLow; i < iHigh; i++) {

                int x, y;

                do {

                    x = random(5, Constants::MazeWidth);
                    y = random(5, Constants::MazeHeight);

                } while (this->getCell(level, x, y) != 0);

                Item &item = this->items[i];
                item.level = level;
                item.x = x * tileSize;
                item.y = y * tileSize;
                item.itemType = ItemType::Bomb;
            
            }

        }
};
