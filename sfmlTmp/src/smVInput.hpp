#pragma once
#include <array>
#include <SFML/Window.hpp>
#include "smLogger.hpp"



/**
* VInput (virtual input)
* @brief 1P megadrive controller for now
*/
class VInput {
public:
	enum VInputType : uint8_t {
		//UNKNOWN,
		UP, DOWN, LEFT, RIGHT,
		A, B, C, START,
		SIZE
	};
	enum State : uint8_t {
		RELEASED = 0,
		PRESSED,
		HELD
	};
	static std::array<State, VInputType::SIZE> virtualInputState;
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

	static bool isPressed(VInputType type); // only the press frame
	static bool isHeld(VInputType type); // held frames OR press frame
	void event(VInputType type, bool state);
};

