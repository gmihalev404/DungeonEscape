#include "states/MainMenuState.hpp"

#include "core/StateManager.hpp"
#include "states/LevelSelectState.hpp"

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
    const auto titleBounds = title_.getLocalBounds();

    title_.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.f,
                      titleBounds.position.y + titleBounds.size.y / 2.f});

    title_.setPosition({640.f, 100.f});

    const float buttonX = 480.f;

    playButton_.setPosition({buttonX, 200.f});
    continueButton_.setPosition({buttonX, 285.f});
    leaderboardButton_.setPosition({buttonX, 370.f});
    settingsButton_.setPosition({buttonX, 455.f});
    exitButton_.setPosition({buttonX, 540.f});

    playButton_.setOnClick([this]()
                           { stateManager_.changeState(
                                 std::make_unique<LevelSelectState>(
                                     window_,
                                     stateManager_)); });

    exitButton_.setOnClick([this]()
                           { window_.close(); });
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