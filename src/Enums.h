#pragma once

#include "Constants.h"


enum class MenuDirection : uint8_t {
    None,
    Openning,
    Closing,
};

enum class GameState : uint8_t {
    Menu,
    Menu_Select,
    GamePlay,
    ShowMenu,
    Map,
    GameOver,
    LevelUp,
};

enum class ItemType : uint8_t {
    None,
    Map,
    Bomb,
    Gun,
    Bullets,
    Wine,
    Bomb_Active,

};
