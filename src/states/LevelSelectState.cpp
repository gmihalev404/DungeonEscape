#include "states/LevelSelectState.hpp"

#include "core/StateManager.hpp"
#include "states/MainMenuState.hpp"
#include "states/GameplayState.hpp"

#include <memory>

LevelSelectState::LevelSelectState(
    sf::RenderWindow &window,
    StateManager &stateManager)
    : window_(window),
      stateManager_(stateManager),
      font_("assets/fonts/Cinzel-Regular.ttf"),
      title_(font_, "SELECT LEVEL", 52),

      level1Button_(font_, "LEVEL 1", {260.f, 60.f}),
      level2Button_(font_, "LEVEL 2", {260.f, 60.f}),
      level3Button_(font_, "LEVEL 3", {260.f, 60.f}),
      level4Button_(font_, "LEVEL 4", {260.f, 60.f}),
      level5Button_(font_, "LEVEL 5", {260.f, 60.f}),
      backButton_(font_, "BACK", {260.f, 60.f})
{
    const auto titleBounds = title_.getLocalBounds();

    title_.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.f,
                      titleBounds.position.y + titleBounds.size.y / 2.f});

    title_.setPosition({640.f, 85.f});

    const float buttonX = 510.f;

    level1Button_.setPosition({buttonX, 170.f});
    level2Button_.setPosition({buttonX, 245.f});
    level3Button_.setPosition({buttonX, 320.f});
    level4Button_.setPosition({buttonX, 395.f});
    level5Button_.setPosition({buttonX, 470.f});
    backButton_.setPosition({buttonX, 570.f});

    backButton_.setOnClick([this]()
                           { stateManager_.changeState(
                                 std::make_unique<MainMenuState>(
                                     window_,
                                     stateManager_)); });

    level1Button_.setOnClick([this]()
                             { startLevel(1); });

    level2Button_.setOnClick([this]()
                             { startLevel(2); });

    level3Button_.setOnClick([this]()
                             { startLevel(3); });

    level4Button_.setOnClick([this]()
                             { startLevel(4); });

    level5Button_.setOnClick([this]()
                             { startLevel(5); });
}

void LevelSelectState::startLevel(
    int levelNumber)
{
    stateManager_.changeState(
        std::make_unique<GameplayState>(
            window_,
            stateManager_,
            levelNumber));
}

void LevelSelectState::handleEvent(const sf::Event &event)
{
    level1Button_.handleEvent(event);
    level2Button_.handleEvent(event);
    level3Button_.handleEvent(event);
    level4Button_.handleEvent(event);
    level5Button_.handleEvent(event);
    backButton_.handleEvent(event);
}

void LevelSelectState::update(sf::Time)
{
}

void LevelSelectState::render(sf::RenderWindow &window)
{
    window.draw(title_);

    level1Button_.render(window);
    level2Button_.render(window);
    level3Button_.render(window);
    level4Button_.render(window);
    level5Button_.render(window);
    backButton_.render(window);
}