#pragma once

#include "ui/Button.hpp"

#include <SFML/Graphics.hpp>

#include <functional>

class PauseMenu
{
public:
    using Callback = std::function<void()>;

    PauseMenu();

    void setOnResume(Callback callback);
    void setOnRestart(Callback callback);

    void updateLayout(sf::Vector2u windowSize);

    void handleEvent(const sf::Event& event);
    void render(sf::RenderWindow& window) const;

private:
    sf::Font font_;
    sf::Text title_;

    sf::RectangleShape overlay_;
    sf::RectangleShape panel_;

    Button resumeButton_;
    Button restartButton_;
};