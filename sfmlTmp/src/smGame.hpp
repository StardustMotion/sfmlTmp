#pragma once
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "smAudioManager.hpp"
#include "smLogger.hpp"
#include "smResources.hpp"
#include "smWindow.hpp"
#include "smInputManager.hpp"
#include "smImageManager.hpp"
#include "smSonicScene.hpp"

class Game final
{
private:
	sf::Vector2f& win;
	sf::RenderWindow& renderWindow;
	std::unique_ptr<sf::RenderTexture> canvas;
	AudioManager audio;
	InputManager inputManager; // "inputs" for virtual inputs
	ImageManager img;
	SonicScene scene;

public:
	Game(Window& window);
	~Game();

	void run();

	/**
	* @brief update game state/logic
	**/
	void update();

	/**
	* @brief lend a blank canvas to the scene to draw everything on, then transplant canvas to the final window
	**/
	void render();
};