#pragma once
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "smEventManager.hpp";
#include "smLogger.hpp";

class Game final
{
	EventManager eventManager;
	sf::RenderWindow& window;
public:
	Game(sf::RenderWindow& window);
	~Game();
	void run();
};