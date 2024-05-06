#pragma once
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "smLogger.hpp"
#include "smInputManager.hpp"
#include "smSonicScene.hpp"
#include "smResourceHandler.hpp"
#include "smVInputHandler.hpp"

class Game final
{
private:
	sf::RenderWindow& window;
	sf::RenderTexture canvas;

	TextureManager textureManager;
	AudioManager audioManager;
	InputManager inputManager;

public:
	Game(sf::RenderWindow& window);
	~Game();

	void run();

	/**
	* @brief proceed next tic of game state/logic
	**/
	void update(double deltaT, SonicScene& scene);

	/**
	* @brief transfer a lent a blank canvas to the scene to draw everything on into final window
	**/
	void render(SonicScene& scene);
};