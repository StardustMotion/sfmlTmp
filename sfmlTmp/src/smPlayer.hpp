#pragma once
#include <SFML/Graphics.hpp>
#include "smInputVirtual.hpp"
#include "smImageManager.hpp"
#include "smSpriteManager.hpp"

class Player : public sf::Transformable
{
	const InputVirtual& inputs;
	const ImageManager& img;
	SpriteManager sprite;
public:
	Player(const InputVirtual& inputs, const ImageManager& img);
	~Player();
	void update(double deltaT);
	const SpriteManager& getSprite() const;
};

