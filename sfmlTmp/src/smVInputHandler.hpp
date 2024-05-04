#pragma once

#pragma once
#include <cassert>
#include "smVInput.hpp"

class VInputHandler {
	friend class Game;

	static inline VInput* vInputs{ nullptr };
public:
	VInput& input() {
		assert(vInputs && "vInput was nullptr!");
		return *vInputs;
	}
};
