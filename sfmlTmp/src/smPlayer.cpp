#include "smPlayer.hpp"

Player::Player(const InputVirtual& inputs, const ImageManager& img):
	inputs(inputs),
	img(img),
	sprite(img) {
}
Player::~Player() { ; }

void Player::update(double deltaT) {
	sf::Vector2f pos = this->getPosition();
	if (inputs.check(InputVirtual::LEFT)) {
		pos.x -= 2.f;
		sprite.setAnimation(PlayerAnimation::FIRE);
	}
	else if (inputs.check(InputVirtual::RIGHT)) {
		pos.x += 2.f;
		sprite.setAnimation(PlayerAnimation::FIRE);
	}
	if (inputs.check(InputVirtual::UP)) {
		pos.y -= 2.f;
		sprite.setAnimation(PlayerAnimation::JUMP);

	}
	else if (inputs.check(InputVirtual::DOWN)) {
		pos.y += 2.f;
		sprite.setAnimation(PlayerAnimation::STAND);
	}

	this->setPosition(pos);
	sprite.update(deltaT, this->getPosition());
	// -------------------------


}


const SpriteManager& Player::getSprite() const {
	return this->sprite;
}