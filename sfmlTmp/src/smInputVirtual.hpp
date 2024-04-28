#pragma once
#include <array>
#include <SFML/Window.hpp>
#include "smLogger.hpp"

/**
* @brief 1P megadrive controller for now
*/
struct InputVirtual {
	enum Event : unsigned char {
		//UNKNOWN,
		UP, DOWN, LEFT, RIGHT,
		A, B, C,
		START,
		SIZE
	};
	std::array<bool, Event::SIZE> state{};

	static constexpr std::array<std::string_view, SIZE> descriptions{ // pair<Event,string>
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

	void print() const {
		Logger::info("State " + state[0] + state[1] + state[2] + state[3] + state[4] + state[5] + state[6] + state[7]);
	}
	bool check(const Event event) const { 
		return state[event]; 
	}
	void event(const Event event, bool status) { 
		state[event] = status; 
	};
};

