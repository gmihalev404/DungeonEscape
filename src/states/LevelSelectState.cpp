#include "core/StateManager.hpp"

#include "states/LevelSelectState.hpp"
#include "states/MainMenuState.hpp"
#include "states/GameplayState.hpp"

#include "persistence/SaveManager.hpp"
#include "persistence/ProgressManager.hpp"

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
    title_.setFillColor(sf::Color::White);

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

    backButton_.setOnClick([this]()
                           { stateManager_.changeState(
                                 std::make_unique<MainMenuState>(
                                     window_,
                                     stateManager_)); });

    savedGameDialog_.setOnContinue([this]()
                                   {
    const SaveData saveData =
        SaveManager::load();

    stateManager_.changeState(
        std::make_unique<GameplayState>(
            window_,
            stateManager_,
            saveData
        )
    ); });

    savedGameDialog_.setOnStartOver([this]()
                                    {
    SaveManager::removeSave();

    startNewLevel(selectedLevel_); });

    savedGameDialog_.setOnCancel([this]()
                                 { savedGameDialogOpen_ = false; });
    level1Button_.setEnabled(
        ProgressManager::isLevelUnlocked(1));

    level2Button_.setEnabled(
        ProgressManager::isLevelUnlocked(2));

    level3Button_.setEnabled(
        ProgressManager::isLevelUnlocked(3));

    level4Button_.setEnabled(
        ProgressManager::isLevelUnlocked(4));

    level5Button_.setEnabled(
        ProgressManager::isLevelUnlocked(5));

    savedGameDialog_.updateLayout(
        window_.getSize());

    updateLayout();
}

void LevelSelectState::startLevel(
    int levelNumber)
{
    if (!ProgressManager::isLevelUnlocked(
            levelNumber))
    {
        return;
    }
    if (SaveManager::hasSave())
    {
        const SaveData saveData =
            SaveManager::load();

        if (saveData.levelNumber == levelNumber)
        {
            selectedLevel_ = levelNumber;
            savedGameDialogOpen_ = true;
            return;
        }
    }

    startNewLevel(levelNumber);
}

void LevelSelectState::handleEvent(const sf::Event &event)
{
    if (savedGameDialogOpen_)
    {
        savedGameDialog_.handleEvent(event);

        if (const auto *keyPressed =
                event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code ==
                sf::Keyboard::Key::Escape)
            {
                savedGameDialogOpen_ = false;
            }
        }

        return;
    }

    level1Button_.handleEvent(event);
    level2Button_.handleEvent(event);
    level3Button_.handleEvent(event);
    level4Button_.handleEvent(event);
    level5Button_.handleEvent(event);
    backButton_.handleEvent(event);
}

void LevelSelectState::update(sf::Time)
{
    savedGameDialog_.updateLayout(
        window_.getSize());

    updateLayout();
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

    if (savedGameDialogOpen_)
    {
        savedGameDialog_.render(window);
    }
}

void LevelSelectState::updateLayout()
{
    const sf::Vector2u windowSize =
        window_.getSize();

    const float width =
        static_cast<float>(windowSize.x);

    const float buttonWidth = 260.f;
    const float buttonHeight = 60.f;
    const float gap = 14.f;

    const float titleY = 95.f;
    const float buttonsStartY = 180.f;

    const float buttonX =
        (width - buttonWidth) / 2.f;

    const sf::FloatRect titleBounds =
        title_.getLocalBounds();

    title_.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.f,
                      titleBounds.position.y + titleBounds.size.y / 2.f});

    title_.setPosition({width / 2.f,
                        titleY});

    level1Button_.setPosition({buttonX, buttonsStartY});
    level2Button_.setPosition({buttonX, buttonsStartY + (buttonHeight + gap) * 1.f});
    level3Button_.setPosition({buttonX, buttonsStartY + (buttonHeight + gap) * 2.f});
    level4Button_.setPosition({buttonX, buttonsStartY + (buttonHeight + gap) * 3.f});
    level5Button_.setPosition({buttonX, buttonsStartY + (buttonHeight + gap) * 4.f});

    backButton_.setPosition({buttonX,
                             buttonsStartY + (buttonHeight + gap) * 5.f + 35.f});
}

void LevelSelectState::startNewLevel(
    int levelNumber)
{
    stateManager_.changeState(
        std::make_unique<GameplayState>(
            window_,
            stateManager_,
            levelNumber));
}