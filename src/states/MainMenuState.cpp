#include "states/MainMenuState.hpp"
#include "states/LevelSelectState.hpp"
#include "states/GameplayState.hpp"

#include "core/StateManager.hpp"

#include "persistence/SaveManager.hpp"

#include <memory>

MainMenuState::MainMenuState(
    sf::RenderWindow &window,
    StateManager &stateManager)
    : window_(window),
      stateManager_(stateManager),
      font_("assets/fonts/Cinzel-Regular.ttf"),
      title_(font_, "DUNGEON ESCAPE", 56),

      playButton_(font_, "PLAY", {320.f, 65.f}),
      continueButton_(font_, "CONTINUE", {320.f, 65.f}),
      leaderboardButton_(font_, "LEADERBOARD", {320.f, 65.f}),
      settingsButton_(font_, "SETTINGS", {320.f, 65.f}),
      exitButton_(font_, "EXIT", {320.f, 65.f})
{
    title_.setFillColor(sf::Color::White);

    playButton_.setOnClick([this]()
                           { stateManager_.changeState(
                                 std::make_unique<LevelSelectState>(
                                     window_,
                                     stateManager_)); });

    continueButton_.setOnClick([this]()
                               {
    if (!SaveManager::hasSave())
    {
        return;
    }

    const SaveData saveData =
        SaveManager::load();

    stateManager_.changeState(
        std::make_unique<GameplayState>(
            window_,
            stateManager_,
            saveData
        )
    ); });

    exitButton_.setOnClick([this]()
                           { window_.close(); });

    updateLayout();
}

void MainMenuState::handleEvent(const sf::Event &event)
{
    playButton_.handleEvent(event);
    continueButton_.handleEvent(event);
    leaderboardButton_.handleEvent(event);
    settingsButton_.handleEvent(event);
    exitButton_.handleEvent(event);
}

void MainMenuState::update(sf::Time)
{
    updateLayout();
}

void MainMenuState::render(sf::RenderWindow &window)
{
    window.draw(title_);

    playButton_.render(window);
    continueButton_.render(window);
    leaderboardButton_.render(window);
    settingsButton_.render(window);
    exitButton_.render(window);
}

void MainMenuState::updateLayout()
{
    const sf::Vector2u windowSize =
        window_.getSize();

    const float width =
        static_cast<float>(windowSize.x);

    const float buttonWidth = 320.f;
    const float buttonHeight = 65.f;
    const float gap = 18.f;

    const float totalButtonsHeight =
        5.f * buttonHeight + 4.f * gap;

    const float titleY = 120.f;
    const float buttonsStartY = 230.f;

    const float buttonX =
        (width - buttonWidth) / 2.f;

    const sf::FloatRect titleBounds =
        title_.getLocalBounds();

    title_.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.f,
                      titleBounds.position.y + titleBounds.size.y / 2.f});

    title_.setPosition({width / 2.f,
                        titleY});

    playButton_.setPosition({buttonX,
                             buttonsStartY});

    continueButton_.setPosition({buttonX,
                                 buttonsStartY + (buttonHeight + gap) * 1.f});

    leaderboardButton_.setPosition({buttonX,
                                    buttonsStartY + (buttonHeight + gap) * 2.f});

    settingsButton_.setPosition({buttonX,
                                 buttonsStartY + (buttonHeight + gap) * 3.f});

    exitButton_.setPosition({buttonX,
                             buttonsStartY + (buttonHeight + gap) * 4.f});
}