#include "game/Player.hpp"

#include <cmath>

Player::Player(
    sf::Vector2i position,
    float speed
)
    : position_(position),
      targetPosition_(position),
      worldPosition_(
          static_cast<float>(position.x) + 0.5f,
          static_cast<float>(position.y) + 0.5f
      ),
      targetWorldPosition_(worldPosition_),
      speed_(speed)
{
}

const sf::Vector2i& Player::getPosition() const
{
    return position_;
}

const sf::Vector2f& Player::getWorldPosition() const
{
    return worldPosition_;
}

void Player::setPosition(sf::Vector2i position)
{
    position_ = position;
    targetPosition_ = position;

    worldPosition_ = {
        static_cast<float>(position.x) + 0.5f,
        static_cast<float>(position.y) + 0.5f
    };

    targetWorldPosition_ = worldPosition_;

    moving_ = false;
}

void Player::startMove(
    sf::Vector2i targetPosition,
    Action direction
)
{
    if (moving_)
    {
        return;
    }

    targetPosition_ = targetPosition;

    targetWorldPosition_ = {
        static_cast<float>(targetPosition.x) + 0.5f,
        static_cast<float>(targetPosition.y) + 0.5f
    };

    direction_ = direction;
    moving_ = true;
}

void Player::update(sf::Time deltaTime)
{
    if (!moving_)
    {
        return;
    }

    const float step =
        speed_ * deltaTime.asSeconds();

    const float dx =
        targetWorldPosition_.x -
        worldPosition_.x;

    const float dy =
        targetWorldPosition_.y -
        worldPosition_.y;

    if (std::abs(dx) <= step &&
        std::abs(dy) <= step)
    {
        worldPosition_ =
            targetWorldPosition_;

        position_ =
            targetPosition_;

        moving_ = false;

        return;
    }

    if (dx > 0.f)
    {
        worldPosition_.x += step;
    }
    else if (dx < 0.f)
    {
        worldPosition_.x -= step;
    }
    else if (dy > 0.f)
    {
        worldPosition_.y += step;
    }
    else if (dy < 0.f)
    {
        worldPosition_.y -= step;
    }
}

bool Player::isMoving() const
{
    return moving_;
}

Action Player::getDirection() const
{
    return direction_;
}