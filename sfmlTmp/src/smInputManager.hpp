#pragma once
#include <bitset>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "smResources.hpp"
#include "smWindow.hpp"
#include "smVirtualInput.hpp"




class InputManager
{
private:
	enum Device {
		KEYBOARD, MOUSE
	};
	sf::RenderWindow& window;
	bool isFocus{ true };

	std::bitset<VInput::SIZE> presses{}; // turns "pressed" to "held" in their n+1 frames

	//    index = game/virtual key(InputVirtual::)     |||      value = hardware key
	std::array<sf::Keyboard::Key, VInput::SIZE> keyboardBindings;


public:
	InputManager(sf::RenderWindow& window);
	~InputManager();
	
	VirtualInput inputs; // for now 1P

	void poll();
	void setupBindings();
	void processInput(sf::Keyboard::Key key, bool state);
};