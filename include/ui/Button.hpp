#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <string>

class Button
{
public:
    using Callback = std::function<void()>;

    Button(
        const sf::Font& font,
        const std::string& label,
        sf::Vector2f size
    );

    void setPosition(sf::Vector2f position);
    void setOnClick(Callback callback);

    void handleEvent(const sf::Event& event);
    void render(sf::RenderWindow& window) const;

private:
    bool contains(sf::Vector2i point) const;
    void updateTextPosition();
    void setHovered(bool hovered);

private:
    sf::RectangleShape background_;
    sf::Text text_;

    Callback onClick_;

    bool hovered_ = false;
};