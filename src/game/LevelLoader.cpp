#include "game/LevelLoader.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

Level LevelLoader::loadFromFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Failed to open level file: " + path
        );
    }

    int expectedSize = 0;

    if (!(file >> expectedSize))
    {
        throw std::runtime_error(
            "Invalid level size in: " + path
        );
    }

    std::string line;
    std::getline(file, line); // consume remaining '\n'

    std::vector<std::vector<TileType>> tiles;

    sf::Vector2i playerSpawn;
    bool playerFound = false;

    for (int y = 0; y < expectedSize; ++y)
    {
        if (!std::getline(file, line))
        {
            throw std::runtime_error(
                "Level contains fewer rows than expected: " + path
            );
        }

        if (static_cast<int>(line.size()) != expectedSize)
        {
            throw std::runtime_error(
                "Invalid row size in level: " + path
            );
        }

        std::vector<TileType> row;

        row.reserve(expectedSize);

        for (int x = 0; x < expectedSize; ++x)
        {
            const char symbol = line[x];

            if (symbol == '@')
            {
                if (playerFound)
                {
                    throw std::runtime_error(
                        "Level contains multiple player spawns: " + path
                    );
                }

                playerSpawn = {x, y};
                playerFound = true;

                row.push_back(TileType::Empty);
            }
            else
            {
                row.push_back(charToTile(symbol));
            }
        }

        tiles.push_back(std::move(row));
    }

    if (!playerFound)
    {
        throw std::runtime_error(
            "Level does not contain a player spawn: " + path
        );
    }

    return Level(
        std::move(tiles),
        playerSpawn
    );
}

TileType LevelLoader::charToTile(char symbol)
{
    switch (symbol)
    {
        case ' ':
            return TileType::Empty;

        case '#':
            return TileType::Wall;

        case 'C':
            return TileType::Coin;

        case '&':
            return TileType::Key;

        case 'X':
            return TileType::Treasure;

        case '%':
            return TileType::Portal;

        default:
            throw std::runtime_error(
                std::string("Unknown tile symbol: ") + symbol
            );
    }
}