#pragma once
#include <cassert>
#include "smAudioManager.hpp"
#include "smTextureManager.hpp"

class ResourceHandler {
	friend class Game;

	static inline AudioManager* audioManager{ nullptr };
	static inline TextureManager* textureManager{ nullptr };
public:
	AudioManager& audio() {
		assert(audioManager && "audioManager was nullptr!");
		return *audioManager;
	}
	TextureManager& img() {
		assert(textureManager && "textureManager was nullptr!");
		return *textureManager;
	}
};