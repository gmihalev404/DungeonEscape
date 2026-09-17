#pragma once

#include <SFML/System/Vector2.hpp>

class Player
{
public:
    explicit Player(sf::Vector2i position);

    const sf::Vector2i& getPosition() const;
    void setPosition(sf::Vector2i position);

private:
    sf::Vector2i position_;
};