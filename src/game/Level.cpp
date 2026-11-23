#include "game/Level.hpp"

#include <utility>

Level::Level(
    std::vector<std::vector<TileType>> tiles,
    sf::Vector2i playerSpawn)
    : tiles_(std::move(tiles)),
      playerSpawn_(playerSpawn)
{
}

const std::vector<std::vector<TileType>> &Level::getTiles() const
{
    return tiles_;
}

TileType Level::getTile(sf::Vector2i position) const
{
    return tiles_[position.y][position.x];
}

void Level::setTile(sf::Vector2i position, TileType tile)
{
    tiles_[position.y][position.x] = tile;
}

const sf::Vector2i &Level::getPlayerSpawn() const
{
    return playerSpawn_;
}

std::optional<sf::Vector2i>
Level::getOtherPortal(
    sf::Vector2i currentPortal) const
{
    for (int y = 0; y < getHeight(); ++y)
    {
        for (int x = 0; x < getWidth(); ++x)
        {
            const sf::Vector2i position{x, y};

            if (position == currentPortal)
            {
                continue;
            }

            if (getTile(position) ==
                TileType::Portal)
            {
                return position;
            }
        }
    }

    return std::nullopt;
}

int Level::getWidth() const
{
    if (tiles_.empty())
    {
        return 0;
    }

    return static_cast<int>(tiles_[0].size());
}

int Level::getHeight() const
{
    return static_cast<int>(tiles_.size());
}

bool Level::isInside(sf::Vector2i position) const
{
    return position.x >= 0 &&
           position.y >= 0 &&
           position.x < getWidth() &&
           position.y < getHeight();
}