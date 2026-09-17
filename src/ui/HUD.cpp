#include "ui/HUD.hpp"

#include <iomanip>
#include <sstream>
#include <utility>

HUD::HUD()
    : font_("assets/fonts/Cinzel-Regular.ttf"),
      levelText_(font_, "", 24),
      coinsText_(font_, "", 24),
      keyText_(font_, "", 24),
      timeText_(font_, "", 24),
      pauseButton_(font_, "PAUSE", {130.f, 45.f})
{
    levelText_.setPosition({30.f, 20.f});
    coinsText_.setPosition({260.f, 20.f});
    keyText_.setPosition({520.f, 20.f});
    timeText_.setPosition({800.f, 20.f});

    levelText_.setFillColor(sf::Color::White);
    coinsText_.setFillColor(sf::Color::White);
    keyText_.setFillColor(sf::Color::White);
    timeText_.setFillColor(sf::Color::White);
}

void HUD::update(
    const GameSession &session)
{
    levelText_.setString(
        "LEVEL " +
        std::to_string(session.getLevelNumber()));

    coinsText_.setString(
        "COINS: " +
        std::to_string(session.getCoins()));

    keyText_.setString(
        session.hasKey()
            ? "KEY: YES"
            : "KEY: NO");

    timeText_.setString(
        "TIME: " +
        formatTime(session.getElapsedTime()));
}

void HUD::render(
    sf::RenderWindow &window) const
{
    sf::RectangleShape background({static_cast<float>(window.getSize().x),
                                   70.f});

    background.setFillColor(
        sf::Color(10, 10, 15, 230));

    window.draw(background);

    window.draw(levelText_);
    window.draw(coinsText_);
    window.draw(keyText_);
    window.draw(timeText_);

    pauseButton_.render(window);
}

std::string HUD::formatTime(
    sf::Time time) const

{
    const int totalSeconds =
        static_cast<int>(time.asSeconds());

    const int minutes =
        totalSeconds / 60;

    const int seconds =
        totalSeconds % 60;

    std::ostringstream stream;

    stream
        << std::setfill('0')
        << std::setw(2)
        << minutes
        << ":"
        << std::setw(2)
        << seconds;

    return stream.str();
}

void HUD::setOnPause(Callback callback)
{
    pauseButton_.setOnClick(
        std::move(callback));
}

void HUD::updateLayout(
    sf::Vector2u windowSize)
{
    const float width =
        static_cast<float>(windowSize.x);

    pauseButton_.setPosition({width - 150.f,
                              12.f});
}

void HUD::handleEvent(
    const sf::Event &event)
{
    pauseButton_.handleEvent(event);
}