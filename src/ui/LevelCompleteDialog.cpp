#include "ui/LevelCompleteDialog.hpp"

#include <iomanip>
#include <sstream>
#include <utility>

LevelCompleteDialog::LevelCompleteDialog()
    : font_("assets/fonts/Cinzel-Regular.ttf"),
      title_(font_, "LEVEL COMPLETE!", 40),
      statsText_(font_, "", 24),
      nextButton_(font_, "NEXT LEVEL", {280.f, 60.f}),
      levelSelectButton_(font_, "LEVEL SELECT", {280.f, 60.f})
{
    overlay_.setFillColor(
        sf::Color(0, 0, 0, 165)
    );

    panel_.setSize({460.f, 360.f});

    panel_.setFillColor(
        sf::Color(20, 20, 28)
    );

    panel_.setOutlineColor(
        sf::Color(160, 120, 60)
    );

    panel_.setOutlineThickness(2.f);

    title_.setFillColor(sf::Color::White);
    statsText_.setFillColor(sf::Color::White);
}

void LevelCompleteDialog::setOnNextLevel(
    Callback callback)
{
    nextButton_.setOnClick(
        std::move(callback)
    );
}

void LevelCompleteDialog::setOnLevelSelect(
    Callback callback)
{
    levelSelectButton_.setOnClick(
        std::move(callback)
    );
}

void LevelCompleteDialog::setStats(
    int levelNumber,
    int coins,
    sf::Time time)
{
    finalLevel_ = levelNumber >= 5;

    if (finalLevel_)
    {
        title_.setString(
            "DUNGEON ESCAPED!"
        );
    }
    else
    {
        title_.setString(
            "LEVEL " +
            std::to_string(levelNumber) +
            " COMPLETE!"
        );
    }

    statsText_.setString(
        "COINS: " +
        std::to_string(coins) +
        "\nTIME: " +
        formatTime(time)
    );
}

void LevelCompleteDialog::updateLayout(
    sf::Vector2u windowSize)
{
    const float width =
        static_cast<float>(windowSize.x);

    const float height =
        static_cast<float>(windowSize.y);

    overlay_.setSize({width, height});

    const sf::Vector2f panelSize =
        panel_.getSize();

    const float panelX =
        (width - panelSize.x) / 2.f;

    const float panelY =
        (height - panelSize.y) / 2.f;

    panel_.setPosition({
        panelX,
        panelY
    });

    auto centerText =
        [width](sf::Text& text, float y)
    {
        const sf::FloatRect bounds =
            text.getLocalBounds();

        text.setOrigin({
            bounds.position.x +
                bounds.size.x / 2.f,

            bounds.position.y +
                bounds.size.y / 2.f
        });

        text.setPosition({
            width / 2.f,
            y
        });
    };

    centerText(
        title_,
        panelY + 60.f
    );

    centerText(
        statsText_,
        panelY + 135.f
    );

    const float buttonX =
        width / 2.f - 140.f;

    if (!finalLevel_)
    {
        nextButton_.setPosition({
            buttonX,
            panelY + 215.f
        });

        levelSelectButton_.setPosition({
            buttonX,
            panelY + 290.f
        });
    }
    else
    {
        levelSelectButton_.setPosition({
            buttonX,
            panelY + 245.f
        });
    }
}

void LevelCompleteDialog::handleEvent(
    const sf::Event& event)
{
    if (!finalLevel_)
    {
        nextButton_.handleEvent(event);
    }

    levelSelectButton_.handleEvent(event);
}

void LevelCompleteDialog::render(
    sf::RenderWindow& window) const
{
    window.draw(overlay_);
    window.draw(panel_);
    window.draw(title_);
    window.draw(statsText_);

    if (!finalLevel_)
    {
        nextButton_.render(window);
    }

    levelSelectButton_.render(window);
}

std::string LevelCompleteDialog::formatTime(
    sf::Time time) const
{
    const int totalSeconds =
        static_cast<int>(
            time.asSeconds()
        );

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