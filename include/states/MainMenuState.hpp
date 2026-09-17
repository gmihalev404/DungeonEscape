#pragma once

#include "core/GameState.hpp"
#include "ui/Button.hpp"

#include <SFML/Graphics.hpp>

class StateManager;

class MainMenuState : public GameState
{
public:
    MainMenuState(
        sf::RenderWindow& window,
        StateManager& stateManager
    );

    void handleEvent(const sf::Event& event) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::RenderWindow& window_;
    StateManager& stateManager_;

    sf::Font font_;
    sf::Text title_;

    Button playButton_;
    Button continueButton_;
    Button leaderboardButton_;
    Button settingsButton_;
    Button exitButton_;
};