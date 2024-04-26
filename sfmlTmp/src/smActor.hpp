#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "smImageManager.hpp"

struct AnimationFrame {
	int time; //float
	sf::IntRect crop;
};

// smallest game logic object ; alternative names "entity" / "unit"
//  "Actor" comes from Doom modding
class Actor
{
	sf::Vector2f pos{ 0,0 };
	sf::Texture* texture;
	sf::Sprite sprite;
	std::size_t animationFrame{ 0 };
	int animationTic{ 0 };
	std::vector<AnimationFrame> animations { 
		{ 20, { 32, 0, 32, 32 } },
		{ 10, { 32, 32, 32, 32 } },
		{ 20, { 32, 64, 32, 32 } },
		{ 10, { 32, 96, 32, 32 } }
	};
public:
	Actor(const ImageManager& img);
	~Actor();
	void draw(sf::RenderTarget& canvas);
};

