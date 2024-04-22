#pragma once

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "smImageManager.hpp"
#include "smLogger.hpp"


// a non-interactive background with several possible parallax layers
class Background
{
	sf::Sprite bg;
public:
	Background(const ImageManager& img, image::Id bg);
	~Background();

	/**
	* @brief fill/draw on canvas with parallax content
	*/
	void fill(sf::RenderTexture& canvas);
};