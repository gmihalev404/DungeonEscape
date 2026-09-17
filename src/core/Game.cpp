#include "core/Game.hpp"

Game::Game()
    : window_(
          sf::VideoMode({1280, 720}),
          "Dungeon Escape")
{
    window_.setFramerateLimit(60);
}

void Game::run()
{
    while (window_.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (const auto event = window_.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window_.close();
        }
    }
}

void Game::update()
{
}

void Game::render()
{
    window_.clear();

    window_.display();
}