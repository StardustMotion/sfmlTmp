#pragma once
//#include <string>
#include <filesystem>
//#include <memory>
//#include <array>
#include <fstream>
//#include <ranges>
//#include <map>
//#include <SFML/Graphics/Texture.hpp>
#include "smAnimation.hpp"

// loads textures and contain animation definitions
class TextureManager
{

	// !! Namespace common to all folders to fix todo
	static std::map<std::string, Animation> animations;
	static std::map<std::string, std::shared_ptr<sf::Texture>> cache;
public:
	// load all textures on init
	TextureManager();
	~TextureManager();
	void parseAnimation(std::filesystem::path path);

	// get a cached texture, or load it beforehand if not cached yet
	static std::shared_ptr<sf::Texture> getTexture(const std::string name);
	static Animation* getAnim(const std::string name);
};

