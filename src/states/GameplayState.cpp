#include "states/GameplayState.hpp"

#include "core/StateManager.hpp"
#include "game/LevelLoader.hpp"

#include <string>

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
      levelRenderer_(32.f)
{
    hud_.update(session_);
    updateViews();
}

void GameplayState::handleEvent(
    const sf::Event &event)
{
    if (const auto *keyPressed =
            event.getIf<sf::Event::KeyPressed>())
    {
        switch (keyPressed->code)
        {
        case sf::Keyboard::Key::W:
        case sf::Keyboard::Key::Up:
            tryMove({0, -1});
            break;

        case sf::Keyboard::Key::S:
        case sf::Keyboard::Key::Down:
            tryMove({0, 1});
            break;

        case sf::Keyboard::Key::A:
        case sf::Keyboard::Key::Left:
            tryMove({-1, 0});
            break;

        case sf::Keyboard::Key::D:
        case sf::Keyboard::Key::Right:
            tryMove({1, 0});
            break;

        default:
            break;
        }
    }
}

void GameplayState::tryMove(
    sf::Vector2i direction)
{
    const sf::Vector2i currentPosition =
        player_.getPosition();

    const sf::Vector2i targetPosition = {
        currentPosition.x + direction.x,
        currentPosition.y + direction.y};

    if (!level_.isInside(targetPosition))
    {
        return;
    }

    const TileType targetTile =
        level_.getTile(targetPosition);

    if (targetTile == TileType::Wall)
    {
        return;
    }

    player_.setPosition(targetPosition);

    if (targetTile == TileType::Coin)
    {
        session_.collectCoin();
        level_.setTile(
            targetPosition,
            TileType::Empty);
    }
    else if (targetTile == TileType::Key)
    {
        session_.collectKey();
        level_.setTile(
            targetPosition,
            TileType::Empty);
    }
}

void GameplayState::update(
    sf::Time deltaTime)
{
    session_.update(deltaTime);
    hud_.update(session_);

    updateViews();
}

void GameplayState::render(
    sf::RenderWindow &window)
{
    // World / camera
    window.setView(gameView_);

    levelRenderer_.render(
        window,
        level_,
        player_);

    window.setView(uiView_);

    hud_.render(window);
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

    const sf::Vector2i playerPosition =
        player_.getPosition();

    float centerX =
        (playerPosition.x + 0.5f) *
        tileSize;

    float centerY =
        (playerPosition.y + 0.5f) *
        tileSize;

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