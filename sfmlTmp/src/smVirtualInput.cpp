#pragma once
#include "smVirtualInput.hpp"

bool VirtualInput::isPressed(VInput type) const {
	return this->virtualInputState[type] == State::PRESSED;
}
bool VirtualInput::isHeld(VInput type) const {
	return this->virtualInputState[type] != State::RELEASED;
}

void VirtualInput::event(VInput type, bool state) {
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
					+ std::string(VirtualInput::descriptions[type]));
}