#include "game/Player.hpp"

Player::Player(sf::Vector2i position)
    : position_(position)
{
}

const sf::Vector2i& Player::getPosition() const
{
    return position_;
}

void Player::setPosition(sf::Vector2i position)
{
    position_ = position;
}