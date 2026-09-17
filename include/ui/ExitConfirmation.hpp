#pragma once

#include "ui/Button.hpp"

#include <SFML/Graphics.hpp>

#include <functional>

class ExitConfirmation
{
public:
    using Callback = std::function<void()>;

    ExitConfirmation();

    void setOnSaveAndExit(Callback callback);
    void setOnExitWithoutSaving(Callback callback);
    void setOnCancel(Callback callback);

    void updateLayout(sf::Vector2u windowSize);

    void handleEvent(const sf::Event& event);

    void render(
        sf::RenderWindow& window
    ) const;

private:
    sf::Font font_;

    sf::Text title_;
    sf::Text question_;

    sf::RectangleShape overlay_;
    sf::RectangleShape panel_;

    Button saveButton_;
    Button exitButton_;
    Button cancelButton_;
};