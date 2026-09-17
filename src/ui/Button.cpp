#include "ui/Button.hpp"

#include <utility>

Button::Button(
    const sf::Font &font,
    const std::string &label,
    sf::Vector2f size)
    : background_(size),
      text_(font, label, 28)
{
    background_.setFillColor(sf::Color(35, 35, 45));
    background_.setOutlineColor(sf::Color(160, 120, 60));
    background_.setOutlineThickness(2.f);

    text_.setFillColor(sf::Color::White);

    updateTextPosition();
}

void Button::setPosition(sf::Vector2f position)
{
    background_.setPosition(position);
    updateTextPosition();
}

void Button::setOnClick(Callback callback)
{
    onClick_ = std::move(callback);
}

void Button::handleEvent(const sf::Event &event)
{
    if (const auto *mouseMoved =
            event.getIf<sf::Event::MouseMoved>())
    {
        setHovered(contains(mouseMoved->position));
    }

    if (const auto *mouseReleased =
            event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button == sf::Mouse::Button::Left &&
            contains(mouseReleased->position) &&
            onClick_)
        {
            onClick_();
        }
    }
}

void Button::render(sf::RenderWindow &window) const
{
    window.draw(background_);
    window.draw(text_);
}

bool Button::contains(sf::Vector2i point) const
{
    const sf::Vector2f mousePosition(
        static_cast<float>(point.x),
        static_cast<float>(point.y));

    return background_.getGlobalBounds().contains(mousePosition);
}

void Button::updateTextPosition()
{
    const sf::FloatRect bounds = text_.getLocalBounds();

    text_.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                     bounds.position.y + bounds.size.y / 2.f});

    const sf::Vector2f buttonPosition = background_.getPosition();
    const sf::Vector2f buttonSize = background_.getSize();

    text_.setPosition({buttonPosition.x + buttonSize.x / 2.f,
                       buttonPosition.y + buttonSize.y / 2.f});
}

void Button::setHovered(bool hovered)
{
    if (hovered_ == hovered)
    {
        return;
    }

    hovered_ = hovered;

    if (hovered_)
    {
        background_.setFillColor(sf::Color(60, 50, 45));
        background_.setOutlineColor(sf::Color(220, 170, 80));
    }
    else
    {
        background_.setFillColor(sf::Color(35, 35, 45));
        background_.setOutlineColor(sf::Color(160, 120, 60));
    }
}