#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "smLogger.hpp"
#include "smResources.hpp"

using std::string;
using sf::Texture;

class TextureManager
{
	private:
		sf::Sprite background;
public:
	TextureManager();
	~TextureManager();

	std::shared_ptr<Texture> loadFromFile(string _path);

	//sf::Sprite& getBG();
	void setBG(std::string bg);
};

