#include "states/GameplayState.hpp"
#include "states/LevelSelectState.hpp"

#include "core/StateManager.hpp"

#include "game/LevelLoader.hpp"

#include "controllers/HumanController.hpp"

#include "persistence/SaveManager.hpp"
#include "persistence/ProgressManager.hpp"

#include <string>
#include <memory>

GameplayState::GameplayState(
    sf::RenderWindow &window,
    StateManager &stateManager,
    int levelNumber)
    : window_(window),
      stateManager_(stateManager),
      session_(levelNumber),
      level_(
          LevelLoader::loadFromFile(
              "assets/levels/level" +
              std::to_string(levelNumber) +
              ".txt")),
      player_(level_.getPlayerSpawn()),
      playerController_(
          std::make_unique<HumanController>()),
      levelRenderer_(32.f),
      notificationFont_(
          "assets/fonts/Cinzel-Regular.ttf"),
      notificationText_(
          notificationFont_,
          "",
          28)
{
    initializeUi();
}

GameplayState::GameplayState(
    sf::RenderWindow &window,
    StateManager &stateManager,
    const SaveData &saveData)
    : window_(window),
      stateManager_(stateManager),
      session_(
          saveData.levelNumber,
          saveData.coins,
          saveData.hasKey,
          saveData.elapsedTime),
      level_(
          saveData.tiles,
          saveData.playerPosition),
      player_(
          saveData.playerPosition),
      playerController_(
          std::make_unique<HumanController>()),
      levelRenderer_(32.f),
      notificationFont_(
          "assets/fonts/Cinzel-Regular.ttf"),
      notificationText_(
          notificationFont_,
          "",
          28)
{
    initializeUi();
}

void GameplayState::update(
    sf::Time deltaTime)
{
    if (notificationRemaining_ > sf::Time::Zero)
    {
        notificationRemaining_ -= deltaTime;

        if (notificationRemaining_ <
            sf::Time::Zero)
        {
            notificationRemaining_ =
                sf::Time::Zero;
        }
    }
    if (!paused_ &&
        !exitConfirmationOpen_ &&
        !levelComplete_)
    {
        if (!player_.isMoving())
        {
            tryStartMove(
                playerController_->getAction());
        }

        const bool wasMoving =
            player_.isMoving();

        player_.update(deltaTime);

        if (wasMoving &&
            !player_.isMoving())
        {
            handlePlayerArrival();
        }

        session_.update(deltaTime);
        hud_.update(session_);
    }

    updateViews();

    hud_.updateLayout(window_.getSize());
    pauseMenu_.updateLayout(window_.getSize());
    exitConfirmation_.updateLayout(
        window_.getSize());
    levelCompleteDialog_.updateLayout(
        window_.getSize());
}

void GameplayState::render(
    sf::RenderWindow &window)
{
    window.setView(gameView_);

    levelRenderer_.render(
        window,
        level_,
        player_);

    window.setView(uiView_);

    hud_.render(window);

    if (notificationRemaining_ >
        sf::Time::Zero)
    {
        window.draw(notificationText_);
    }

    if (paused_)
    {
        pauseMenu_.render(window);
    }

    if (exitConfirmationOpen_)
    {
        exitConfirmation_.render(window);
    }
    if (levelComplete_)
    {
        levelCompleteDialog_.render(window);
    }
}

void GameplayState::updateViews()

{
    const sf::Vector2u windowSize =
        window_.getSize();

    if (windowSize.x == 0 ||
        windowSize.y == 0)
    {
        return;
    }

    const float windowWidth =
        static_cast<float>(windowSize.x);

    const float windowHeight =
        static_cast<float>(windowSize.y);

    const float aspectRatio =
        windowWidth / windowHeight;

    const float cameraWidth = 640.f;
    const float cameraHeight =
        cameraWidth / aspectRatio;

    gameView_.setSize({cameraWidth,
                       cameraHeight});

    const float tileSize =
        levelRenderer_.getTileSize();

    const float levelWidth =
        level_.getWidth() * tileSize;

    const float levelHeight =
        level_.getHeight() * tileSize;

    const sf::Vector2f playerPosition =
        player_.getWorldPosition();

    float centerX =
        playerPosition.x * tileSize;

    float centerY =
        playerPosition.y * tileSize;

    const float halfWidth =
        cameraWidth / 2.f;

    const float halfHeight =
        cameraHeight / 2.f;

    if (levelWidth <= cameraWidth)
    {
        centerX = levelWidth / 2.f;
    }
    else
    {
        centerX = std::clamp(
            centerX,
            halfWidth,
            levelWidth - halfWidth);
    }

    if (levelHeight <= cameraHeight)
    {
        centerY = levelHeight / 2.f;
    }
    else
    {
        centerY = std::clamp(
            centerY,
            halfHeight,
            levelHeight - halfHeight);
    }

    gameView_.setCenter({centerX,
                         centerY});

    uiView_.setSize({windowWidth,
                     windowHeight});

    uiView_.setCenter({windowWidth / 2.f,
                       windowHeight / 2.f});
}

void GameplayState::initializeUi()
{
    hud_.update(session_);
    updateViews();

    hud_.setOnPause([this]()
                    { paused_ = true; });

    pauseMenu_.setOnResume([this]()
                           { paused_ = false; });

    pauseMenu_.setOnRestart([this]()
                            { stateManager_.changeState(
                                  std::make_unique<GameplayState>(
                                      window_,
                                      stateManager_,
                                      session_.getLevelNumber())); });

    hud_.setOnBack([this]()
                   { exitConfirmationOpen_ = true; });

    exitConfirmation_.setOnSaveAndExit([this]()
                                       {
        SaveManager::save(
            session_,
            level_,
            player_
        );

        stateManager_.changeState(
            std::make_unique<LevelSelectState>(
                window_,
                stateManager_
            )
        ); });

    exitConfirmation_.setOnExitWithoutSaving([this]()
                                             { stateManager_.changeState(
                                                   std::make_unique<LevelSelectState>(
                                                       window_,
                                                       stateManager_)); });

    exitConfirmation_.setOnCancel([this]()
                                  { exitConfirmationOpen_ = false; });

    hud_.updateLayout(window_.getSize());
    pauseMenu_.updateLayout(window_.getSize());
    exitConfirmation_.updateLayout(
        window_.getSize());

    levelCompleteDialog_.setOnNextLevel([this]()
                                        {const int nextLevel =
        session_.getLevelNumber() + 1;

    stateManager_.changeState(
        std::make_unique<GameplayState>(
            window_,
            stateManager_,
            nextLevel
        )
    ); });

    levelCompleteDialog_.setOnLevelSelect([this]()
                                          { stateManager_.changeState(
                                                std::make_unique<LevelSelectState>(
                                                    window_,
                                                    stateManager_)); });

    levelCompleteDialog_.updateLayout(
        window_.getSize());
}

void GameplayState::tryStartMove(
    Action action)
{
    if (action == Action::None ||
        player_.isMoving())
    {
        return;
    }

    sf::Vector2i direction{0, 0};

    switch (action)
    {
    case Action::MoveUp:
        direction = {0, -1};
        break;

    case Action::MoveDown:
        direction = {0, 1};
        break;

    case Action::MoveLeft:
        direction = {-1, 0};
        break;

    case Action::MoveRight:
        direction = {1, 0};
        break;

    default:
        return;
    }

    const sf::Vector2i current =
        player_.getPosition();

    const sf::Vector2i target = {
        current.x + direction.x,
        current.y + direction.y};

    if (!level_.isInside(target))
    {
        return;
    }

    const TileType tile =
        level_.getTile(target);

    if (tile == TileType::Wall)
    {
        return;
    }

    if (tile == TileType::Treasure &&
        !session_.hasKey())
    {
        showNotification(
            "YOU NEED THE KEY!");

        return;
    }

    player_.startMove(
        target,
        action);
}

void GameplayState::handlePlayerArrival()
{
    const sf::Vector2i position =
        player_.getPosition();

    const TileType tile =
        level_.getTile(position);

    if (tile == TileType::Coin)
    {
        session_.collectCoin();

        level_.setTile(
            position,
            TileType::Empty);
    }
    else if (tile == TileType::Key)
    {
        session_.collectKey();

        level_.setTile(
            position,
            TileType::Empty);
    }
    else if (tile == TileType::Treasure)
    {
        completeLevel();
    }
    else if (tile == TileType::Portal)
    {
        const auto destination =
            level_.getOtherPortal(position);

        if (destination.has_value())
        {
            player_.setPosition(
                destination.value());

            showNotification(
                "TELEPORTED!");
        }
    }
}

void GameplayState::showNotification(
    const std::string &message)
{
    notificationText_.setString(message);

    notificationText_.setFillColor(
        sf::Color(230, 190, 70));

    const sf::FloatRect bounds =
        notificationText_.getLocalBounds();

    notificationText_.setOrigin({bounds.position.x +
                                     bounds.size.x / 2.f,

                                 bounds.position.y +
                                     bounds.size.y / 2.f});

    const sf::Vector2u size =
        window_.getSize();

    notificationText_.setPosition({static_cast<float>(size.x) / 2.f,
                                   static_cast<float>(size.y) - 60.f});

    notificationRemaining_ =
        sf::seconds(2.f);
}

void GameplayState::completeLevel()
{
    const int currentLevel =
        session_.getLevelNumber();

    if (currentLevel < 5)
    {
        ProgressManager::unlockLevel(
            currentLevel + 1);
    }

    SaveManager::removeSave();

    levelCompleteDialog_.setStats(
        currentLevel,
        session_.getCoins(),
        session_.getElapsedTime());

    levelComplete_ = true;
}

void GameplayState::handleEvent(
    const sf::Event &event)
{
    if (levelComplete_)
    {
        levelCompleteDialog_.handleEvent(event);
        return;
    }

    if (exitConfirmationOpen_)
    {
        exitConfirmation_.handleEvent(event);

        if (const auto *keyPressed =
                event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code ==
                sf::Keyboard::Key::Escape)
            {
                exitConfirmationOpen_ = false;
            }
        }

        return;
    }

    if (paused_)
    {
        pauseMenu_.handleEvent(event);

        if (const auto *keyPressed =
                event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code ==
                sf::Keyboard::Key::Escape)
            {
                paused_ = false;
            }
        }

        return;
    }

    hud_.handleEvent(event);

    if (const auto *keyPressed =
            event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code ==
            sf::Keyboard::Key::Escape)
        {
            paused_ = true;
            return;
        }
    }
}