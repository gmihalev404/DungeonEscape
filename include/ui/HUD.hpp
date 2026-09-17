#pragma once

#include "game/GameSession.hpp"

#include <SFML/Graphics.hpp>

#include <string>

class HUD
{
public:
    HUD();

    void update(const GameSession& session);

    void render(
        sf::RenderWindow& window
    ) const;

private:
    std::string formatTime(
        sf::Time time
    ) const;

private:
    sf::Font font_;

    sf::Text levelText_;
    sf::Text coinsText_;
    sf::Text keyText_;
    sf::Text timeText_;
};