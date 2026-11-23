#include "controllers/HumanController.hpp"

#include <SFML/Window/Keyboard.hpp>

Action HumanController::getAction() const
{
    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::Up))
    {
        return Action::MoveUp;
    }

    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::Down))
    {
        return Action::MoveDown;
    }

    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::Left))
    {
        return Action::MoveLeft;
    }

    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::Right))
    {
        return Action::MoveRight;
    }

    return Action::None;
}