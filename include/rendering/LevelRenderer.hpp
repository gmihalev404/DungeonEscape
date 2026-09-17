#pragma once

#include "game/Level.hpp"
#include "game/Player.hpp"

#include <SFML/Graphics.hpp>

class LevelRenderer
{
public:
    explicit LevelRenderer(float tileSize = 32.f);

    float getTileSize() const;

    void render(
        sf::RenderWindow &window,
        const Level &level,
        const Player &player) const;

private:
    sf::Color getTileColor(TileType tile) const;

private:
    float tileSize_;
};