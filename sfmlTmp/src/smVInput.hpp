#pragma once
#include <array>
#include <SFML/Window.hpp>
#include <optional>
#include "smLogger.hpp"



/**
* VInput (virtual input)
* @brief 1P megadrive controller for now
*/
class VInput {
	friend class InputManager;
public:
	enum VInputType : uint8_t {
		//UNKNOWN,
		UP, DOWN, LEFT, RIGHT,
		A, B, C, START,
		SIZE
	};
private:
	enum State : uint8_t {
		RELEASED = 0,
		PRESSED,
		HELD
	};
	static std::array<State, VInputType::SIZE> virtualInputState;

	// keyboard
	void event(VInputType type, bool state);

	// mouse/pointer
	void event(VInputType type, sf::Vector2i position, bool state);

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
	static std::optional<sf::Vector2i> pointerPosition;

public:
	static bool isPressed(VInputType type); // only the press frame
	static bool isHeld(VInputType type); // held frames OR press frame
	static std::optional<sf::Vector2i> pointer(); // return pointer's position
};

