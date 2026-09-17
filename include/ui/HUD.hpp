#pragma once

#include "game/GameSession.hpp"
#include "ui/Button.hpp"

#include <SFML/Graphics.hpp>

#include <functional>
#include <string>

class HUD
{
public:
    using Callback = std::function<void()>;

    HUD();

    void update(const GameSession &session);
    void updateLayout(sf::Vector2u windowSize);

    void setOnPause(Callback callback);
    void handleEvent(const sf::Event &event);

    void render(sf::RenderWindow &window) const;

    void setOnBack(Callback callback);

private:
    std::string formatTime(sf::Time time) const;

private:
    sf::Font font_;

    sf::Text levelText_;
    sf::Text coinsText_;
    sf::Text keyText_;
    sf::Text timeText_;

    Button backButton_;
    Button pauseButton_;
};