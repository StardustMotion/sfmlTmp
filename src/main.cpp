
#include <iostream>
#include "smLogger.hpp"
#include "smGame.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "gaming 7 the videogame");
    window.setFramerateLimit(24);
    Logger::log("exe started");
    Game game{ window };

    // blocking / game loop
    game.run();

    Logger::log("exe ends");

    return EXIT_SUCCESS;
}