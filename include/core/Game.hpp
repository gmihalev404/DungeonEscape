#pragma once

#include "core/StateManager.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow window_;
    StateManager stateManager_;
    sf::Clock clock_;
};