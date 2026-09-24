#pragma once

#include "core/GameState.hpp"

#include "game/Level.hpp"
#include "game/Player.hpp"
#include "game/GameSession.hpp"

#include "rendering/LevelRenderer.hpp"

#include "ui/HUD.hpp"
#include "ui/PauseMenu.hpp"
#include "ui/ExitConfirmation.hpp"

#include "persistence/SaveData.hpp"

#include <SFML/Graphics.hpp>

#include <string>

class StateManager;

class GameplayState : public GameState
{
public:
    GameplayState(
        sf::RenderWindow &window,
        StateManager &stateManager,
        int levelNumber);

    GameplayState(
        sf::RenderWindow &window,
        StateManager &stateManager,
        const SaveData &saveData);

    void handleEvent(
        const sf::Event &event) override;

    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow &window) override;

private:
    sf::RenderWindow &window_;
    StateManager &stateManager_;

    GameSession session_;

    Level level_;
    Player player_;

    LevelRenderer levelRenderer_;
    HUD hud_;

    sf::View gameView_;
    sf::View uiView_;

    sf::Font notificationFont_;
    sf::Text notificationText_;

    sf::Time notificationRemaining_{};

    PauseMenu pauseMenu_;
    ExitConfirmation exitConfirmation_;

    bool paused_ = false;
    bool exitConfirmationOpen_ = false;

    void updateViews();

    void tryMove(sf::Vector2i direction);

    void initializeUi();

    void showNotification(
        const std::string &message);

    void completeLevel();
};