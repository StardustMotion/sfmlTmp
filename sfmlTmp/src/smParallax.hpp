#pragma once

#include <iostream>
#include <cassert>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "smResourceHandler.hpp"
#include "smLogger.hpp"

// non-interactive plan to fill canvas with
class Parallax : public ResourceHandler {
	sf::Sprite sprite;
	const float scrollFactor;
	sf::Vector2f size, offset{ 0,0 };
public:
	Parallax(std::string&& texture, float scrollFactor = 1.f, float scale = 2.f);
	void onDraw();
	void update(const sf::View& view);
	// update -> scroll
};


class Parallax_Heatman : public Parallax {
public:
	Parallax_Heatman() :
		Parallax("wilywars_heat", 0.125f, 2.f) {
		;
	}
};
class Parallax_Topman : public Parallax {
public:
	Parallax_Topman() :
		Parallax("wilywars_top", 0.25f, 4.f) {
		;
	}
};
class Parallax_Iceman : public Parallax {
public:
	Parallax_Iceman() :
		Parallax("wilywars_ice", 0.25f) {
		;
	}
};
class Parallax_Hardman : public Parallax {
public:
	Parallax_Hardman() :
		Parallax("wilywars_hard", 0.25f) {
		;
	}
};