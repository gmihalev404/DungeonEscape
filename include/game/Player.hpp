#pragma once

#include "game/Action.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Player
{
public:
    explicit Player(
        sf::Vector2i position,
        float speed = 5.f
    );

    const sf::Vector2i& getPosition() const;
    const sf::Vector2f& getWorldPosition() const;

    void setPosition(sf::Vector2i position);

    void startMove(
        sf::Vector2i targetPosition,
        Action direction
    );

    void update(sf::Time deltaTime);

    bool isMoving() const;

    Action getDirection() const;

private:
    sf::Vector2i position_;
    sf::Vector2i targetPosition_;

    sf::Vector2f worldPosition_;
    sf::Vector2f targetWorldPosition_;

    float speed_;
    bool moving_ = false;

    Action direction_ = Action::MoveDown;
};