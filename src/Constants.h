#pragma once


const uint8_t DELAY = 12;

const int tileSize = 12;
const int screenTileWidth = (128 / tileSize) + 1;  // 16 tiles wide
const int screenTileHeight = (64 / tileSize) + 1;  // 8 tiles tall

namespace Constants { 

	static constexpr int8_t DirectionOffsetX[4] = {0, 1, 0, -1};
	static constexpr int8_t DirectionOffsetY[4] = {-1, 0, 1, 0};
	static constexpr uint8_t MazeHeight = 23;
	static constexpr uint8_t MazeWidth = 23;
	static constexpr uint8_t MaxChests = 10;
	static constexpr uint8_t MaxEnemys = 12;
	static constexpr uint8_t MaxItems = 4;

	//                        0  1  2  3  4  5  6  7  8  9  0  1  2
	static constexpr uint8_t BombX[] PROGMEM = { 7, 6, 5, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0 };
	static constexpr uint8_t BombY[] PROGMEM = { 1, 0, 0, 0, 1, 2, 2, 2, 1, 1, 1, 1, 1 };

}
