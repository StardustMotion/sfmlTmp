
#include <iostream>
#include "smLogger.hpp"
#include "smGame.hpp"


int main()
{
    Logger::setLevel(LogLevel::all);
	// camera/view
	// ANDROID checks?
	//window->setIcon
    sf::RenderWindow window(sf::VideoMode(1024,512),
						"Sonic ~ Remembrance");
	Logger::debug("Init window... size " + tos(window.getSize().x) + "x" + tos(window.getSize().y));
	window.setFramerateLimit(60);
    Game game{ window };

    return EXIT_SUCCESS;
}