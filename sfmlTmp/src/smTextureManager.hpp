#pragma once
#include <filesystem>
#include <fstream>
#include "smAnimation.hpp"

// loads textures and contain animation definitions
class TextureManager
{
	// !! Namespace common to all folders to fix todo
	std::map<std::string, Animation> animations;
	std::map<std::string, std::shared_ptr<sf::Texture>> cache;
public:
	// load all textures on init
	TextureManager();
	~TextureManager();
	void parseAnimation(std::filesystem::path path);

	// get a cached texture. Load it beforehand if not cached yet
	std::shared_ptr<sf::Texture> getTexture(const std::string name);
	Animation* getAnim(const std::string name);
};

