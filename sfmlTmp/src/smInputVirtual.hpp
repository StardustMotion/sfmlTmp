#pragma once
#include <array>

/**
* @brief megadrive controller for now
*/
namespace InputVirtual {
	enum : unsigned char {
		//UNKNOWN,
		UP, DOWN, LEFT, RIGHT,
		A, B, C,
		START,
		SIZE
	};
	constexpr std::array<std::string_view, SIZE> descriptions{
		//"???",
		"Move up", "Move down", "Move left", "Move right",
		"Select", "Alternative", "Cancel",
		"Start"
	};

	// until they can be configured
	constexpr std::array<sf::Keyboard::Key, SIZE> preBindings{
		//sf::Keyboard::Key::Unknown,
		sf::Keyboard::Key::Z,		sf::Keyboard::Key::S,		sf::Keyboard::Key::Q,		sf::Keyboard::Key::D,
		sf::Keyboard::Key::H,		sf::Keyboard::Key::J,		sf::Keyboard::Key::K,
		sf::Keyboard::Key::Enter
	};

	// Static as 1P only for now
	static std::array<bool, SIZE> state{};
};

