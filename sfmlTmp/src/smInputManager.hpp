#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "smResources.hpp"
#include "smWindow.hpp"
#include "smInputVirtual.hpp"
#include <array>

enum class InputDevice : bool {
	KEYBOARD, MOUSE
};

struct InputEvent {
	const InputDevice device;
	const uint8_t id;
	const bool state;
	// payload; // mouse position i.e
	InputEvent(InputDevice device, uint8_t id, bool state);
	~InputEvent();
};

class InputManager
{
private:
	sf::RenderWindow& window;
	//AudioManager& audio;
	bool isFocus{ true };

	// hardware status
	std::array<bool, sf::Keyboard::Key::KeyCount> keyboard;
	std::array<bool, sf::Mouse::Button::ButtonCount> mouse;

	//    index = game/virtual key(InputVirtual::)     |||      value = hardware key
	std::array<sf::Keyboard::Key, InputVirtual::SIZE> bindings;

public:
	InputManager(Window& window);
	~InputManager();
	void poll();
	void setupBindings();
};