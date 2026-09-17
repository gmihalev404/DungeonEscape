#pragma once

#include <SFML/Graphics.hpp>

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};