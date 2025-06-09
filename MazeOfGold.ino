#include <Arduboy2Core.h>
#include <Sprites.h>
#include "src/Enums.h"
#include "src/Images.h"
#include "src/Constants.h"
#include "src/Menu.h"
#include "src/Maze.h"
#include "src/Player.h"

#define DEBUG_BREAK    asm volatile("break\n");

Arduboy2 arduboy;


// Camera offset
Point camera = { 0, 0 };
Point camera_Small = { 0, 0 };

uint8_t clearedLevel;

Maze maze;
Menu menu;
Player player;
Item puff;
Item death;

GameState gameState = GameState::Menu_Init;
// GameState gameState_Next = GameState::Menu_Init;
// uint8_t gameState_Transition;

uint8_t level = 0;
uint8_t mapLevel = 0;
uint8_t showEnemyCursors = 0;
uint8_t displayChests;

void setup() {

	arduboy.boot();
	arduboy.setFrameRate(25);
	randomSeed(arduboy.generateRandomSeed());
	
}

void loop() {

	if (!(arduboy.nextFrame())) return;

	arduboy.pollButtons();
	arduboy.clear();

	switch (gameState) {
	
		case GameState::Menu_Init:

			initCoins();
			gameState = GameState::Menu;
			[[fallthrough]]
	
		case GameState::Menu:

			handleTitle();
			break;

		case GameState::Menu_Select:

			arduboy.drawFastHLine(0, 23, 128, WHITE);
			Sprites::drawOverwrite(0, 25, Images::Title, 0);
			arduboy.drawFastHLine(0, 40, 128, WHITE);
			Sprites::drawOverwrite(20, 50, Images::Cursors, showEnemyCursors);

			if (arduboy.justPressed(UP_BUTTON)) {
				showEnemyCursors = 0;
			}

			if (arduboy.justPressed(DOWN_BUTTON)) {
				showEnemyCursors = 1;
			}

			if (arduboy.justPressed(A_BUTTON)) {

				randomSeed(arduboy.generateRandomSeed());
				gameState = GameState::GamePlay;
				maze.setEnemyCount(2);

				clearedLevel = 1;
				startGame();

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
			drawDeath();
			drawPuff();

			if (displayChests > 0) {

				Sprites::drawOverwrite(0, 26, Images::ChestsCollected, 0);
				Sprites::drawOverwrite(98, 26, Images::ChestsCollected_Numbers, 9 - maze.getActiveChests());
				displayChests--;
			
			}

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
			drawDeath();
			drawPuff();

			Sprites::drawOverwrite(0, 26, Images::GameOver, 0);

			if (arduboy.justPressed(A_BUTTON)) {
				gameState = GameState::Menu_Init;
			}
			break;

		case GameState::LevelUp:
			drawMaze(level);
			drawChests(level);
			drawEnemies(level);
			drawPlayer();
			drawDeath();
			drawPuff();

			Sprites::drawOverwrite(0, 26, Images::LevelUp, 0);

			if (arduboy.justPressed(A_BUTTON)) {

				if (maze.getEnemyCount() < Constants::MaxEnemys) maze.setEnemyCount(maze.getEnemyCount() + 1);

				gameState = GameState::GamePlay;
				clearedLevel++;
				startGame();

			}
			break;

	}

	arduboy.display();


	// Do we have a pending gamestate transition?

	// if (gameState_Transition > 0) {
	
	// 	gameState_Transition--;

	// 	if (gameState_Transition == 0) {

	// 		gameState = gameState_Next;

	// 	}

	// }

}

void startGame() {

	uint8_t stairsPlaced = 0;

	level = 0;

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
	maze.spawnEnemys(1, 6, 6 + maze.getEnemyCount());

	maze.spawnItems(0, 0, 1);
	maze.spawnItems(1, 1, 2);

	player.reset();

	// Camera offset
	camera.x = 0;
	camera.y = 0;

	menu.y = 0;
	menu.top = 0;
	displayChests = 0;

}