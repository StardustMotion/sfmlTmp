#pragma once
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "smEventManager.hpp"
#include "smTextureManager.hpp"
#include "smAudioManager.hpp"
#include "smLogger.hpp"
#include "smResources.hpp"

class Game final
{
private:
	EventManager eventManager;
	TextureManager textureManager;
	AudioManager audio;
	sf::RenderWindow& window;
	bool stopGame = false;
	char tailsRefresh = 0, tailsAnimation = 0;
	float speed = 0;
	enum TailsState
	{
		LEFT,
		RIGHT,
		STOP
	};
	void showTails(sf::Sprite& tails, TailsState state);

public:
	Game(sf::RenderWindow& window);
	~Game();
	void run();
	void onUpdate(sf::Text& text, sf::Sprite& tails);
};