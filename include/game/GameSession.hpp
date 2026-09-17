#pragma once

#include <SFML/System/Time.hpp>

class GameSession
{
public:
    explicit GameSession(int levelNumber);
    
    GameSession(
        int levelNumber,
        int coins,
        bool hasKey,
        sf::Time elapsedTime);

    void update(sf::Time deltaTime);

    void collectCoin();
    void collectKey();

    int getLevelNumber() const;
    int getCoins() const;
    bool hasKey() const;
    sf::Time getElapsedTime() const;

private:
    int levelNumber_;
    int coins_ = 0;
    bool hasKey_ = false;

    sf::Time elapsedTime_{};
};