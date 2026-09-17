#include "game/GameSession.hpp"

GameSession::GameSession(int levelNumber)
    : levelNumber_(levelNumber)
{
}

GameSession::GameSession(
    int levelNumber,
    int coins,
    bool hasKey,
    sf::Time elapsedTime)
    : levelNumber_(levelNumber),
      coins_(coins),
      hasKey_(hasKey),
      elapsedTime_(elapsedTime)
{
}

void GameSession::update(sf::Time deltaTime)
{
    elapsedTime_ += deltaTime;
}

void GameSession::collectCoin()
{
    ++coins_;
}

void GameSession::collectKey()
{
    hasKey_ = true;
}

int GameSession::getLevelNumber() const
{
    return levelNumber_;
}

int GameSession::getCoins() const
{
    return coins_;
}

bool GameSession::hasKey() const
{
    return hasKey_;
}

sf::Time GameSession::getElapsedTime() const
{
    return elapsedTime_;
}