#pragma once
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "smTextureManager.hpp"
#include "smAudioManager.hpp"
#include "smLogger.hpp"
#include "smResources.hpp"
#include "smWindow.hpp"
#include "smInputManager.hpp"

class Game final
{
private:
	Window& window;
	AudioManager audioManager;
	InputManager inputManager;

public:
	Game(Window& window);
	~Game();

	void run();



//
//private:
//	EventManager eventManager;
//	TextureManager textureManager;
//	bool stopGame = false;
//	char tailsRefresh = 0, tailsAnimation = 0;
//	float speed = 0;
//	enum TailsState
//	{
//		LEFT,
//		RIGHT,
//		STOP
//	};
//	void showTails(sf::Sprite& tails, TailsState state);
//
//public:
//	Game(Window& window);
//	~Game();
//	void run();
//	void onUpdate(sf::Text& text, sf::Sprite& tails);
};