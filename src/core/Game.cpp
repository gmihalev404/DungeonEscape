#include "core/Game.hpp"
#include "states/MainMenuState.hpp"

#include <memory>

Game::Game()
    : window_(
          sf::VideoMode({1280, 720}),
          "Dungeon Escape")
{
    window_.setFramerateLimit(60);

    stateManager_.changeState(
        std::make_unique<MainMenuState>(
            window_,
            stateManager_));

    stateManager_.applyPendingChange();
}

void Game::run()
{
    while (window_.isOpen())
    {
        sf::Time deltaTime = clock_.restart();

        processEvents();
        stateManager_.applyPendingChange();
        update(deltaTime);
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
            continue;
        }

        if (GameState *state = stateManager_.getCurrentState())
        {
            state->handleEvent(*event);
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    if (GameState *state = stateManager_.getCurrentState())
    {
        state->update(deltaTime);
    }
}

void Game::render()
{
    window_.clear();

    if (GameState *state = stateManager_.getCurrentState())
    {
        state->render(window_);
    }

    window_.display();
}