#pragma once

#include "game/GameSession.hpp"
#include "game/Level.hpp"
#include "game/Player.hpp"
#include "persistence/SaveData.hpp"

class SaveManager
{
public:
    static void save(
        const GameSession& session,
        const Level& level,
        const Player& player
    );

    static SaveData load();

    static bool hasSave();

    static void removeSave();

private:
    static char tileToChar(TileType tile);
    static TileType charToTile(char symbol);
};