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


Maze maze;
Menu menu;
Player player;
Item puff;
Item death;
Item bullet;

GameState gameState = GameState::PPOT_Init;

uint8_t clearedLevel = 0;
uint8_t level = 0;
uint8_t mapLevel = 0;
uint8_t showEnemyCursors = 0;
uint8_t show = 0;
uint8_t displayChests = 0;
uint8_t enableMaps = 0;
uint8_t menuCursor = 0;

bool darkMode = false;
int16_t darkModeCounter = -256;


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
	
		case GameState::PPOT_Init:
			splashScreen_Init();
			[[fallthrough]]

		case GameState::PPOT:
			splashScreen();
			break;

		case GameState::Menu_Init:

			initCoins();
			gameState = GameState::Menu;
			[[fallthrough]]
	
		case GameState::Menu:

			handleTitle();
			break;

		case GameState::Menu_Select:

			Sprites::drawExternalMask(0, 22, Images::Title, Images::Title_Mask, 0, 0);
			Sprites::drawOverwrite(19, 44, Images::Cursors, menuCursor == 1 || arduboy.frameCount % 40 < 20 ? showEnemyCursors : 2);
			Sprites::drawOverwrite(19, 52, Images::EnableMaps, menuCursor == 0 || arduboy.frameCount % 40 < 20 ? enableMaps : 2);

			if (arduboy.justPressed(UP_BUTTON)) {
				menuCursor = 0;
			}

			if (arduboy.justPressed(DOWN_BUTTON)) {
				menuCursor = 1;
			}

			if (arduboy.justPressed(LEFT_BUTTON)) {

				if (menuCursor == 0) {
					showEnemyCursors = 0;
				}
				else {
					enableMaps = 0;
				}

			}

			if (arduboy.justPressed(RIGHT_BUTTON)) {

				if (menuCursor == 0) {
					showEnemyCursors = 1;
				}
				else {
					enableMaps = 1;
				}

			}

			if (arduboy.justPressed(A_BUTTON)) {

				randomSeed(arduboy.generateRandomSeed());
				gameState = GameState::GamePlay;
				arduboy.frameCount = 0;
				maze.setEnemyCount(2);

				clearedLevel = 0;
				startGame(true);

			}	
			break;

		case GameState::GamePlay:

			handleDarkMode();
			updatePlayer();
			updateCamera();
			updateEnemys(level);
			checkCollisions(level);
			drawMaze(level);
			drawChests(level);
			drawEnemies(level);
			drawItems(level);
			drawPlayer();
			drawDeath();
			drawPuff();
			drawBullet();	
			drawFlashlight();    

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
			darkMode = false;
			darkModeCounter = -256;

			drawMaze(level);
			drawChests(level);
			drawEnemies(level);
			drawPlayer();
			drawDeath();
			drawPuff();
			drawFlashlight();    

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
			drawFlashlight();    

			Sprites::drawOverwrite(0, 26, Images::LevelUp, 0);

			if (arduboy.justPressed(A_BUTTON)) {

				if (maze.getEnemyCount() < Constants::MaxEnemys / 2) maze.setEnemyCount(maze.getEnemyCount() + 1);

				gameState = GameState::GamePlay;
				clearedLevel++;
				startGame(false);

			}
			break;

	}

	arduboy.display();

}

void startGame(bool clearInventory) {

	uint8_t stairsPlaced = 0;

	level = 0;

	maze.generateMaze(player, arduboy.sBuffer);
	player.reset(clearInventory, enableMaps == 0);

	camera.x = 0;
	camera.y = 0;

	menu.y = 0;
	menu.top = 0;

	displayChests = 0;
	arduboy.frameCount == 0;
	darkMode = false;
	darkModeCounter = -256;

}

void handleDarkMode() {

	if (darkModeCounter == -256 && arduboy.frameCount > 512 && (level == 1 || clearedLevel > 1) && random(512) == 0) {
		darkModeCounter = 312;
	}

	switch (darkModeCounter) {

		case 312:
		case 310:
		case 308:
		case 305:

		case 10:
		case 7:
		case 5:
			arduboy.invert(true);
			darkModeCounter--;
			break;

		case 302:
			arduboy.invert(true);
			darkModeCounter--;
			darkMode = true;
			break;

		case 2:
			arduboy.invert(true);
			darkModeCounter--;
			darkMode = false;
			break;

		case -256:
			break;

		default:
			arduboy.invert(false);
			darkModeCounter--;
			break;

	}

}