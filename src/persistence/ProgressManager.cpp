#include "persistence/ProgressManager.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>

int ProgressManager::getHighestUnlockedLevel()
{
    std::ifstream file("saves/progress.txt");

    if (!file.is_open())
    {
        return 1;
    }

    int level = 1;

    if (!(file >> level))
    {
        return 1;
    }

    return std::clamp(
        level,
        1,
        MAX_LEVEL
    );
}

bool ProgressManager::isLevelUnlocked(
    int levelNumber)
{
    return levelNumber <=
           getHighestUnlockedLevel();
}

void ProgressManager::unlockLevel(
    int levelNumber)
{
    levelNumber = std::clamp(
        levelNumber,
        1,
        MAX_LEVEL
    );

    const int current =
        getHighestUnlockedLevel();

    if (levelNumber <= current)
    {
        return;
    }

    std::filesystem::create_directories(
        "saves"
    );

    std::ofstream file(
        "saves/progress.txt"
    );

    file << levelNumber << '\n';
}