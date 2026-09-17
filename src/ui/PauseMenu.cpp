#include "ui/PauseMenu.hpp"

#include <utility>

PauseMenu::PauseMenu()
    : font_("assets/fonts/Cinzel-Regular.ttf"),
      title_(font_, "PAUSED", 42),
      resumeButton_(font_, "RESUME", {260.f, 60.f}),
      restartButton_(font_, "RESTART", {260.f, 60.f})
{
    overlay_.setFillColor(
        sf::Color(0, 0, 0, 150)
    );

    panel_.setSize({380.f, 300.f});
    panel_.setFillColor(
        sf::Color(20, 20, 28)
    );

    panel_.setOutlineColor(
        sf::Color(160, 120, 60)
    );

    panel_.setOutlineThickness(2.f);

    title_.setFillColor(sf::Color::White);
}

void PauseMenu::setOnResume(Callback callback)
{
    resumeButton_.setOnClick(
        std::move(callback)
    );
}

void PauseMenu::setOnRestart(Callback callback)
{
    restartButton_.setOnClick(
        std::move(callback)
    );
}

void PauseMenu::updateLayout(
    sf::Vector2u windowSize
)
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

    const sf::FloatRect titleBounds =
        title_.getLocalBounds();

    title_.setOrigin({
        titleBounds.position.x +
            titleBounds.size.x / 2.f,

        titleBounds.position.y +
            titleBounds.size.y / 2.f
    });

    title_.setPosition({
        width / 2.f,
        panelY + 55.f
    });

    resumeButton_.setPosition({
        width / 2.f - 130.f,
        panelY + 110.f
    });

    restartButton_.setPosition({
        width / 2.f - 130.f,
        panelY + 190.f
    });
}

void PauseMenu::handleEvent(
    const sf::Event& event
)
{
    resumeButton_.handleEvent(event);
    restartButton_.handleEvent(event);
}

void PauseMenu::render(
    sf::RenderWindow& window
) const
{
    window.draw(overlay_);
    window.draw(panel_);
    window.draw(title_);

    resumeButton_.render(window);
    restartButton_.render(window);
}