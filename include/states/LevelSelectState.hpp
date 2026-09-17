#pragma once

#include "core/GameState.hpp"
#include "ui/Button.hpp"

#include <SFML/Graphics.hpp>

class StateManager;

class LevelSelectState : public GameState
{
public:
    LevelSelectState(
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

    Button level1Button_;
    Button level2Button_;
    Button level3Button_;
    Button level4Button_;
    Button level5Button_;
    Button backButton_;
};