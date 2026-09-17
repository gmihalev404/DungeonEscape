#include "game/GameSession.hpp"

GameSession::GameSession(int levelNumber)
    : levelNumber_(levelNumber)
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