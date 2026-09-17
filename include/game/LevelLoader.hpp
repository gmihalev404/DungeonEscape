#pragma once

#include "game/Level.hpp"

#include <string>

class LevelLoader
{
public:
    static Level loadFromFile(const std::string& path);

private:
    static TileType charToTile(char symbol);
};