#include "persistence/SaveManager.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <limits>

void SaveManager::save(
    const GameSession &session,
    const Level &level,
    const Player &player)
{
    std::filesystem::create_directories("saves");

    std::ofstream file("saves/save.txt");

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Failed to create save file");
    }

    const sf::Vector2i position =
        player.getPosition();

    file << "DUNGEON_ESCAPE_SAVE_V1\n";

    file << session.getLevelNumber() << '\n';
    file << session.getCoins() << '\n';
    file << session.hasKey() << '\n';

    file << session.getElapsedTime().asMilliseconds()
         << '\n';

    file << position.x
         << ' '
         << position.y
         << '\n';

    file << level.getWidth()
         << ' '
         << level.getHeight()
         << '\n';

    for (int y = 0; y < level.getHeight(); ++y)
    {
        for (int x = 0; x < level.getWidth(); ++x)
        {
            file << tileToChar(
                level.getTile({x, y}));
        }

        file << '\n';
    }
}

bool SaveManager::hasSave()
{
    return std::filesystem::exists(
        "saves/save.txt");
}

char SaveManager::tileToChar(TileType tile)
{
    switch (tile)
    {
    case TileType::Empty:
        return ' ';

    case TileType::Wall:
        return '#';

    case TileType::Coin:
        return 'C';

    case TileType::Key:
        return '&';

    case TileType::Treasure:
        return 'X';

    case TileType::Portal:
        return '%';
    }

    return ' ';
}

SaveData SaveManager::load()
{
    std::ifstream file("saves/save.txt");

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Save file does not exist");
    }

    std::string header;

    std::getline(file, header);

    if (header != "DUNGEON_ESCAPE_SAVE_V1")
    {
        throw std::runtime_error(
            "Unsupported or corrupted save file");
    }

    SaveData data;

    std::int32_t elapsedMilliseconds = 0;

    if (!(file >> data.levelNumber >>
          data.coins >>
          data.hasKey >>
          elapsedMilliseconds >>
          data.playerPosition.x >>
          data.playerPosition.y))
    {
        throw std::runtime_error(
            "Invalid save data");
    }

    data.elapsedTime =
        sf::milliseconds(elapsedMilliseconds);

    int width = 0;
    int height = 0;

    if (!(file >> width >> height))
    {
        throw std::runtime_error(
            "Invalid saved level size");
    }

    if (width <= 0 || height <= 0)
    {
        throw std::runtime_error(
            "Invalid saved level dimensions");
    }

    file.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');

    data.tiles.reserve(height);

    for (int y = 0; y < height; ++y)
    {
        std::string line;

        if (!std::getline(file, line))
        {
            throw std::runtime_error(
                "Save contains missing level rows");
        }

        if (static_cast<int>(line.size()) != width)
        {
            throw std::runtime_error(
                "Invalid saved level row");
        }

        std::vector<TileType> row;

        row.reserve(width);

        for (char symbol : line)
        {
            row.push_back(
                charToTile(symbol));
        }

        data.tiles.push_back(
            std::move(row));
    }

    if (data.playerPosition.x < 0 ||
        data.playerPosition.y < 0 ||
        data.playerPosition.x >= width ||
        data.playerPosition.y >= height)
    {
        throw std::runtime_error(
            "Invalid saved player position");
    }

    return data;
}

TileType SaveManager::charToTile(char symbol)
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
            "Unknown tile in save file");
    }
}

void SaveManager::removeSave()
{
    if (std::filesystem::exists("saves/save.txt"))
    {
        std::filesystem::remove("saves/save.txt");
    }
}