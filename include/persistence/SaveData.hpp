#pragma once

#include "game/Tile.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

struct SaveData
{
    int levelNumber;
    int coins;
    bool hasKey;

    sf::Time elapsedTime;
    sf::Vector2i playerPosition;

    std::vector<std::vector<TileType>> tiles;
};