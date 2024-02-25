#pragma once
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "smEventManager.hpp"
#include "smLogger.hpp"

class Game final
{
private:
	EventManager eventManager;
	sf::RenderWindow& window;
	bool stopGame = false;
	sf::Sprite tails;
	char tailsRefresh = 0, tailsAnimation = 0;
	float speed = 0;
	enum TailsState 
	{
		LEFT,
		RIGHT,
		STOP
	};
	void showTails(TailsState state);
	
public:
	Game(sf::RenderWindow& window);
	~Game();
	void run();
};