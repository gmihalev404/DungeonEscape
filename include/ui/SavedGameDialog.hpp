#pragma once

#include "ui/Button.hpp"

#include <SFML/Graphics.hpp>

#include <functional>

class SavedGameDialog
{
public:
    using Callback = std::function<void()>;

    SavedGameDialog();

    void setOnContinue(Callback callback);
    void setOnStartOver(Callback callback);
    void setOnCancel(Callback callback);

    void updateLayout(sf::Vector2u windowSize);

    void handleEvent(const sf::Event& event);
    void render(sf::RenderWindow& window) const;

private:
    sf::Font font_;

    sf::Text title_;
    sf::Text message_;

    sf::RectangleShape overlay_;
    sf::RectangleShape panel_;

    Button continueButton_;
    Button startOverButton_;
    Button cancelButton_;
};