#pragma once
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "smAudioManager.hpp"
#include "smLogger.hpp"
#include "smResources.hpp"
#include "smWindow.hpp"
#include "smInputManager.hpp"

class Game final
{
private:
	Window& window;
	AudioManager audio;
	InputManager inputManager;

public:
	Game(Window& window);
	~Game();

	void run();

};