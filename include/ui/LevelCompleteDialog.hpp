#pragma once

#include "ui/Button.hpp"

#include <SFML/Graphics.hpp>

#include <functional>
#include <string>

class LevelCompleteDialog
{
public:
    using Callback = std::function<void()>;

    LevelCompleteDialog();

    void setOnNextLevel(Callback callback);
    void setOnLevelSelect(Callback callback);

    void setStats(
        int levelNumber,
        int coins,
        sf::Time time
    );

    void updateLayout(sf::Vector2u windowSize);

    void handleEvent(const sf::Event& event);

    void render(
        sf::RenderWindow& window
    ) const;

private:
    std::string formatTime(
        sf::Time time
    ) const;

private:
    sf::Font font_;

    sf::Text title_;
    sf::Text statsText_;

    sf::RectangleShape overlay_;
    sf::RectangleShape panel_;

    Button nextButton_;
    Button levelSelectButton_;

    bool finalLevel_ = false;
};