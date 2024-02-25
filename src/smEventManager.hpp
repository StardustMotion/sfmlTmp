#pragma once
#include <SFML/Graphics.hpp>

class EventManager
{
private:
	sf::RenderWindow& window;
	bool exit;
public:
	EventManager(sf::RenderWindow& window);
	~EventManager();
	//void update();
	bool poll();
};