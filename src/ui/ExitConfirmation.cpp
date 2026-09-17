#include "ui/ExitConfirmation.hpp"

#include <utility>

ExitConfirmation::ExitConfirmation()
    : font_("assets/fonts/Cinzel-Regular.ttf"),
      title_(font_, "LEAVE CURRENT GAME?", 36),
      question_(
          font_,
          "Save progress before leaving?",
          22),
      saveButton_(
          font_,
          "SAVE & EXIT",
          {360.f, 55.f}),
      exitButton_(
          font_,
          "EXIT WITHOUT SAVING",
          {360.f, 55.f}),
      cancelButton_(
          font_,
          "CANCEL",
          {360.f, 55.f})
{
    overlay_.setFillColor(
        sf::Color(0, 0, 0, 160));

    panel_.setSize({520.f, 390.f});

    panel_.setFillColor(
        sf::Color(20, 20, 28));

    panel_.setOutlineColor(
        sf::Color(160, 120, 60));

    panel_.setOutlineThickness(2.f);

    title_.setFillColor(sf::Color::White);
    question_.setFillColor(sf::Color::White);
}

void ExitConfirmation::setOnSaveAndExit(
    Callback callback)
{
    saveButton_.setOnClick(
        std::move(callback));
}

void ExitConfirmation::setOnExitWithoutSaving(
    Callback callback)
{
    exitButton_.setOnClick(
        std::move(callback));
}

void ExitConfirmation::setOnCancel(
    Callback callback)
{
    cancelButton_.setOnClick(
        std::move(callback));
}

void ExitConfirmation::updateLayout(
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

    panel_.setPosition({panelX,
                        panelY});

    auto centerText =
        [width](sf::Text &text, float y)
    {
        const sf::FloatRect bounds =
            text.getLocalBounds();

        text.setOrigin({bounds.position.x +
                            bounds.size.x / 2.f,

                        bounds.position.y +
                            bounds.size.y / 2.f});

        text.setPosition({width / 2.f,
                          y});
    };

    centerText(
        title_,
        panelY + 55.f);

    centerText(
        question_,
        panelY + 105.f);

    const float buttonX =
        width / 2.f - 180.f;

    saveButton_.setPosition({buttonX,
                             panelY + 145.f});

    exitButton_.setPosition({buttonX,
                             panelY + 215.f});

    cancelButton_.setPosition({buttonX,
                               panelY + 285.f});
}

void ExitConfirmation::handleEvent(
    const sf::Event &event)
{
    saveButton_.handleEvent(event);
    exitButton_.handleEvent(event);
    cancelButton_.handleEvent(event);
}

void ExitConfirmation::render(
    sf::RenderWindow &window) const
{
    window.draw(overlay_);
    window.draw(panel_);

    window.draw(title_);
    window.draw(question_);

    saveButton_.render(window);
    exitButton_.render(window);
    cancelButton_.render(window);
}