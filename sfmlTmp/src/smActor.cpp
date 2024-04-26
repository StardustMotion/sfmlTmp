#include "smActor.hpp"


Actor::Actor(const ImageManager& img) {
	// sprite = { new sprite };
	sprite.setTexture(*img.get(image::WILYWARS_CRASHMAN));
	sprite.setTextureRect(animations[0].crop);
	sprite.setScale(3.f, 3.f);
}

Actor::~Actor() { ; }

void Actor::draw(sf::RenderTarget& canvas) { // sf::RenderStates
	if (animationTic > animations[animationFrame].time) {
		animationFrame = (animationFrame + 1) % animations.size();
		sprite.setTextureRect(animations[animationFrame].crop);
		animationTic = 0;
	}
	sprite.setPosition(pos);
	canvas.draw(sprite);
	animationTic++;
}