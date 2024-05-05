#pragma once
#include "smVInput.hpp"


std::array<VInput::State, VInput::VInputType::SIZE> VInput::virtualInputState{};
std::optional<sf::Vector2i> VInput::pointerPosition{};

bool VInput::isPressed(VInputType type) {
	return virtualInputState[type] == State::PRESSED;
}
bool VInput::isHeld(VInputType type) {
	return virtualInputState[type] != State::RELEASED;
}

void VInput::event(VInputType type, bool state) {
	if (state)
		if (virtualInputState[type] == State::PRESSED) {
			virtualInputState[type] = State::HELD;
			return;
		}
		else if (virtualInputState[type] == State::RELEASED) virtualInputState[type] = State::PRESSED;
		else return;
	else
		virtualInputState[type] = State::RELEASED;
	Logger::debug(std::string((virtualInputState[type] != State::RELEASED) ? "--> " : "<-- ")
		+ std::string(VInput::descriptions[type])
		+ (pointerPosition ? " at [" + tos(pointerPosition->x) + "," + tos(pointerPosition->y) + "]" : ""));
}

void VInput::event(VInputType type, sf::Vector2i position, bool state) {
	pointerPosition = (state ? std::optional<sf::Vector2i>(position) : std::nullopt);
	event(type, state);
}

std::optional<sf::Vector2i> VInput::pointer() {
	return pointerPosition;
}
