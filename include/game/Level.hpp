#pragma once

#include "game/Tile.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <optional>

class Level
{
public:
    Level(
        std::vector<std::vector<TileType>> tiles,
        sf::Vector2i playerSpawn);

    const std::vector<std::vector<TileType>> &getTiles() const;

    TileType getTile(sf::Vector2i position) const;
    void setTile(sf::Vector2i position, TileType tile);

    const sf::Vector2i &getPlayerSpawn() const;

    std::optional<sf::Vector2i> getOtherPortal(
        sf::Vector2i currentPortal) const;

    int getWidth() const;
    int getHeight() const;

    bool isInside(sf::Vector2i position) const;

private:
    std::vector<std::vector<TileType>> tiles_;
    sf::Vector2i playerSpawn_;
};