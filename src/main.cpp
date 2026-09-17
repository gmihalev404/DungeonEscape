#include "core/Game.hpp"

#include <exception>
#include <iostream>

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Fatal error: "
                  << exception.what()
                  << '\n';

        return 1;
    }

    return 0;
}