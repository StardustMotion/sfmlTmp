#pragma once
#include <SFML/Graphics.hpp>
#include "smVirtualInput.hpp"
#include "smImageManager.hpp"
#include "smSpriteManager.hpp"

class Player : public sf::Transformable
{
	const VirtualInput& inputs;
	const ImageManager& img;
	SpriteManager sprite;
public:
	Player(const VirtualInput& inputs, const ImageManager& img);
	~Player();
	void update(double deltaT);
	const SpriteManager& getSprite() const;
};

