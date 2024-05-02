#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct AnimationFrame {
	float t;
	sf::Vector2i crop;
};

struct Animation {
	sf::Vector2i size; // all frames have same height/width
	std::vector<std::vector<AnimationFrame>> frames; // [x][y] = animation x frame y
};
