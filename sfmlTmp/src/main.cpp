
#include <iostream>
#include "smLogger.hpp"
#include "smGame.hpp"


int main()
{
    Logger::setLevel(LogLevel::all);
	// camera/view
	// ANDROID checks?
	//window->setIcon
    sf::RenderWindow window(sf::VideoMode(1024,768),
						"allah kermesse pas de perdant c moi qui te le dit ' n')");
	Logger::debug("Init window... size " + tos(window.getSize().x) + "x" + tos(window.getSize().y));
	window.setFramerateLimit(60);
    Game game{ window };

    return EXIT_SUCCESS;
}