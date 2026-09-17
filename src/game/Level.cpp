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