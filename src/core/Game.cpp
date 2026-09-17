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

        if (const auto *resized =
                event->getIf<sf::Event::Resized>())
        {
            const sf::Vector2f newSize(
                static_cast<float>(resized->size.x),
                static_cast<float>(resized->size.y));

            sf::View view = window_.getView();

            view.setSize(newSize);

            view.setCenter({newSize.x / 2.f,
                            newSize.y / 2.f});

            window_.setView(view);
        }

        if (GameState *state =
                stateManager_.getCurrentState())
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