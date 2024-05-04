
#include <iostream>
#include "smLogger.hpp"
#include "smGame.hpp"


int main()
{
    Logger::setLevel(LogLevel::all);
	Logger::debug("Init window...");
	// camera/view
	// ANDROID checks?
	//window->setIcon
    sf::RenderWindow window(sf::VideoMode(960,720), "allah kermesse pas de perdant c moi qui te le dit ' n')");
	window.setFramerateLimit(60);
    Game game{ window };

    return EXIT_SUCCESS;
}