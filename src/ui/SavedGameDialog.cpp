#include "ui/SavedGameDialog.hpp"

#include <utility>

SavedGameDialog::SavedGameDialog()
    : font_("assets/fonts/Cinzel-Regular.ttf"),
      title_(font_, "SAVED PROGRESS FOUND", 34),
      message_(font_, "Continue your previous game?", 22),
      continueButton_(font_, "CONTINUE", {300.f, 55.f}),
      startOverButton_(font_, "START OVER", {300.f, 55.f}),
      cancelButton_(font_, "CANCEL", {300.f, 55.f})
{
    overlay_.setFillColor(
        sf::Color(0, 0, 0, 160)
    );

    panel_.setSize({460.f, 380.f});
    panel_.setFillColor(
        sf::Color(20, 20, 28)
    );

    panel_.setOutlineColor(
        sf::Color(160, 120, 60)
    );

    panel_.setOutlineThickness(2.f);

    title_.setFillColor(sf::Color::White);
    message_.setFillColor(sf::Color::White);
}

void SavedGameDialog::setOnContinue(Callback callback)
{
    continueButton_.setOnClick(
        std::move(callback)
    );
}

void SavedGameDialog::setOnStartOver(Callback callback)
{
    startOverButton_.setOnClick(
        std::move(callback)
    );
}

void SavedGameDialog::setOnCancel(Callback callback)
{
    cancelButton_.setOnClick(
        std::move(callback)
    );
}

void SavedGameDialog::updateLayout(
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

    centerText(title_, panelY + 55.f);
    centerText(message_, panelY + 105.f);

    const float buttonX =
        width / 2.f - 150.f;

    continueButton_.setPosition({
        buttonX,
        panelY + 145.f
    });

    startOverButton_.setPosition({
        buttonX,
        panelY + 215.f
    });

    cancelButton_.setPosition({
        buttonX,
        panelY + 285.f
    });
}

void SavedGameDialog::handleEvent(
    const sf::Event& event)
{
    
    continueButton_.handleEvent(event);
    startOverButton_.handleEvent(event);
    cancelButton_.handleEvent(event);
}

void SavedGameDialog::render(
    sf::RenderWindow& window) const
{
    window.draw(overlay_);
    window.draw(panel_);
    window.draw(title_);
    window.draw(message_);

    continueButton_.render(window);
    startOverButton_.render(window);
    cancelButton_.render(window);
}