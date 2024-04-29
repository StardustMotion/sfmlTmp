#pragma once
#include <array>
#include <SFML/Window.hpp>
#include "smLogger.hpp"


enum VInput : uint8_t {
	//UNKNOWN,
	UP, DOWN, LEFT, RIGHT, 
	A, B, C, START,
	SIZE
};

/**
* @brief 1P megadrive controller for now
*/
class VirtualInput {
public:
	enum State : uint8_t {
		RELEASED = 0,
		PRESSED,
		HELD
	};
	std::array<State, VInput::SIZE> virtualInputState{};
	static constexpr std::array<std::string_view, SIZE> descriptions{
		//"???",
		"[UP] Move up", "[DOWN] Move down", "[LEFT] Move left", "[RIGHT] Move right",
		"[A] Select", "[B] Alternative", "[C] Cancel",
		"[START] Start"
	};

	// until they can be configured
	static constexpr std::array<sf::Keyboard::Key, SIZE> preBindings{
		//sf::Keyboard::Key::Unknown,
		sf::Keyboard::Key::Z,		sf::Keyboard::Key::S,		sf::Keyboard::Key::Q,		sf::Keyboard::Key::D,
		sf::Keyboard::Key::H,		sf::Keyboard::Key::J,		sf::Keyboard::Key::K,
		sf::Keyboard::Key::Enter
	};

	bool isPressed(VInput type) const; // only the press frame
	bool isHeld(VInput type) const; // held frames OR press frame
	void event(VInput type, bool state);
};

