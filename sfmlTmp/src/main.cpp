
#include <iostream>
#include "smLogger.hpp"
#include "smGame.hpp"
#include "smWindow.hpp"


int main()
{
    Logger::setLevel(LogLevel::all);
    Window window;
    window.init("allah kermesse pas de perdant c moi qui te le dit ' n')");
    Game game{ window };
    return EXIT_SUCCESS;
}