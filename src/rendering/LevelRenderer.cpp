#include "rendering/LevelRenderer.hpp"

LevelRenderer::LevelRenderer(float tileSize)
    : tileSize_(tileSize)
{
}

float LevelRenderer::getTileSize() const
{
    return tileSize_;
}

void LevelRenderer::render(
    sf::RenderWindow& window,
    const Level& level,
    const Player& player
) const
{
    sf::RectangleShape tileShape({
        tileSize_,
        tileSize_
    });

    tileShape.setOutlineThickness(-1.f);
    tileShape.setOutlineColor(
        sf::Color(20, 20, 25)
    );

    for (int y = 0; y < level.getHeight(); ++y)
    {
        for (int x = 0; x < level.getWidth(); ++x)
        {
            const TileType tile =
                level.getTile({x, y});

            tileShape.setFillColor(
                getTileColor(tile)
            );

            tileShape.setPosition({
                x * tileSize_,
                y * tileSize_
            });

            window.draw(tileShape);
        }
    }

    const float playerRadius =
        tileSize_ * 0.32f;

    sf::CircleShape playerShape(
        playerRadius
    );

    playerShape.setOrigin({
        playerRadius,
        playerRadius
    });

    playerShape.setFillColor(
        sf::Color(220, 70, 70)
    );

    const sf::Vector2i position =
        player.getPosition();

    playerShape.setPosition({
        (static_cast<float>(position.x) + 0.5f)
            * tileSize_,

        (static_cast<float>(position.y) + 0.5f)
            * tileSize_
    });

    window.draw(playerShape);
}

sf::Color LevelRenderer::getTileColor(
    TileType tile
) const
{
    switch (tile)
    {
        case TileType::Empty:
            return sf::Color(35, 35, 42);

        case TileType::Wall:
            return sf::Color(95, 90, 100);

        case TileType::Coin:
            return sf::Color(220, 180, 50);

        case TileType::Key:
            return sf::Color(70, 170, 220);

        case TileType::Treasure:
            return sf::Color(170, 100, 45);

        case TileType::Portal:
            return sf::Color(145, 70, 190);
    }

    return sf::Color::Magenta;
}