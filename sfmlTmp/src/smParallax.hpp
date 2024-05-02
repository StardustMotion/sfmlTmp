#pragma once

#include <iostream>
#include <cassert>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "smTextureManager.hpp"
#include "smLogger.hpp"


namespace Parallaxes {
	struct ParallaxEntry {
		int left, top, width, height;
		float xScale, yScale; // screen percent occupied (0.5f = fits on a half screen, 2.0f = fits on 2 screens)
		float speed; // [0,1.f]
	};

	enum Parallax {
		WW_FIRE,
		WW_ICE,
		WW_HARD,
		WW_TOP,
		PARALLAX_SIZE
	};

	/*constexpr std::array<std::pair<ParallaxEntry, image::Files>, PARALLAX_SIZE> entries{{
		{ { 0,	0,	256,256,	1.f,1.f,	1.f }, image::Files::WILYWARS_PARALLAX },
		{ { 256,0,	256,256,	1.f,1.f,	0.25f }, image::Files::WILYWARS_PARALLAX },
		{ { 0,	256,256,256,	1.f,1.f,	0.5f }, image::Files::WILYWARS_PARALLAX },
		{ { 256,256,256,256,	1.f,1.f,	1.0f }, image::Files::WILYWARS_PARALLAX }
	} };*/
}

// non-interactive plan to fill canvas with
class Parallax
{
	sf::Sprite bg;
	sf::Vector2f bgSize, offset{ 0,0 };
	const sf::Vector2f& win;
	float speed{ 1.f };
public:
	Parallax(const sf::Vector2f& win, const TextureManager& img, const std::string_view file);
	~Parallax();

	/**
	* @brief fill/draw on canvas with parallax content
	*/
	void draw(sf::RenderTexture& canvas);
	void shift(const float x, const float y);
	void update(double deltaT);
};