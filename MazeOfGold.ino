#include <Arduboy2.h>
#include <Sprites.h>
#include "src/Enums.h"
#include "src/Images.h"
#include "src/Constants.h"
#include "src/Menu.h"
#include "src/Maze.h"
#include "src/Player.h"

#define DEBUG_BREAK    asm volatile("break\n");

Arduboy2 arduboy;


// // Directions
// const int Constants::DirectionOffsetX[4] = {0, 1, 0, -1};
// const int Constants::DirectionOffsetY[4] = {-1, 0, 1, 0};

// Maze
Maze maze;


// Camera offset
Point camera = { 0, 0 };
Point camera_Small = { 0, 0 };

int clearedLevel;

int up = 0;
int left = 0;
int down = 0;
int right = 0;

Menu menu;
Player player;
Item puff;

GameState gameState = GameState::Menu;

uint8_t level = 0;
uint8_t mapLevel = 0;

void setup() {

	arduboy.boot();
	arduboy.setFrameRate(25);

	randomSeed(arduboy.generateRandomSeed());

}

void loop() {

	uint8_t stairsPlaced = 0;

	if (!(arduboy.nextFrame())) return;

	arduboy.pollButtons();
	arduboy.clear();

	switch (gameState) {
	
		case GameState::Menu:

			Sprites::drawOverwrite(0, 25, Images::Title, 0);

			if (arduboy.justPressed(A_BUTTON)) {

				randomSeed(arduboy.generateRandomSeed());
				gameState = GameState::GamePlay;
				maze.setEnemyCount(2);

				clearedLevel = 1;

				while (stairsPlaced < 1) {
					maze.generateMaze_Clear();
					maze.generateMaze(0, arduboy.sBuffer);
					maze.generateMaze(1, arduboy.sBuffer);
					stairsPlaced = maze.generateMaze_Stairs(0, 1);
				}

				maze.spawnChests(0, 0, 4);
				maze.spawnChests(1, 5, 9);
				maze.clearEnemys();
				maze.spawnEnemys(0, 0, maze.getEnemyCount());
				maze.spawnEnemys(1, 10, 10 + maze.getEnemyCount());

				maze.spawnItems(0, 0, 1);
				maze.spawnItems(1, 1, 2);

				player.reset();
				menu.y = 0;
				menu.top = 0;

				// Camera offset
				camera.x = 0;
				camera.y = 0;	
			}	
			break;

		case GameState::GamePlay:

			updatePlayer();
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
			drawPuff();
			drawChestCount(0, 0);

			break;

		case GameState::ShowMenu:

			handleMenu();
			break;

		case GameState::Map:

			handleMenu_ShowMap();
			break;

		case GameState::GameOver:
			drawMaze(level);
			drawChests(level);
			drawEnemies(level);
			drawPlayer();
			drawPuff();

			arduboy.setCursor(37, 30);
			arduboy.print("Game Over");

			if (arduboy.justPressed(A_BUTTON)) {
				gameState = GameState::Menu;
			}
			break;

		case GameState::LevelUp:
			drawMaze(level);
			drawChests(level);
			drawEnemies(level);
			drawPlayer();
			drawPuff();

			arduboy.setCursor(40, 30);
			arduboy.print("Level Up");

			if (arduboy.justPressed(A_BUTTON)) {

				if (maze.getEnemyCount() < Constants::MaxEnemys) maze.setEnemyCount(maze.getEnemyCount() + 1);

				gameState = GameState::GamePlay;
				clearedLevel++;
				level = 0;
				stairsPlaced = 0;

				while (stairsPlaced < 1) {
					maze.generateMaze_Clear();
					maze.generateMaze(0, arduboy.sBuffer);
					maze.generateMaze(1, arduboy.sBuffer);
					stairsPlaced = maze.generateMaze_Stairs(0, 1);
				}


				maze.spawnChests(0, 0, 4);
				maze.spawnChests(1, 5, 9);
				maze.clearEnemys();
				maze.spawnEnemys(0, 0, maze.getEnemyCount());
				maze.spawnEnemys(1, 10, 10 + maze.getEnemyCount());

				maze.spawnItems(0, 0, 1);
				maze.spawnItems(1, 1, 2);

				player.reset();

				// Camera offset
				camera.x = 0;
				camera.y = 0;
			}
			break;

	}

	arduboy.display();

}
