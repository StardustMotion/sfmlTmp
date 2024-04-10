#pragma once
#include <SFML/Graphics.hpp>
#include "smAudioManager.hpp"
#include "smResources.hpp"

class EventManager
{
private:
	sf::RenderWindow& window;
	AudioManager& audio;
	bool exit;
public:
	EventManager(sf::RenderWindow& window, AudioManager& audioManager);
	~EventManager();
	//void update();
	bool poll();
};