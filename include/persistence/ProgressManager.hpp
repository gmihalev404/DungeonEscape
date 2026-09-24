#pragma once

class ProgressManager
{
public:
    static int getHighestUnlockedLevel();

    static bool isLevelUnlocked(int levelNumber);

    static void unlockLevel(int levelNumber);

private:
    static constexpr int MAX_LEVEL = 5;
};