#include "smPlayer.hpp"

Player::Player(const VirtualInput& inputs, const ImageManager& img):
	inputs(inputs),
	img(img),
	sprite(img) {
}
Player::~Player() { ; }

void Player::update(double deltaT) {
	sf::Vector2f pos = this->getPosition();
	if (inputs.isHeld(VInput::LEFT)) {
		pos.x -= 2.f;
		sprite.setAnimation(PlayerAnimation::FIRE);
	}
	if (inputs.isHeld(VInput::RIGHT)) {
		pos.x += 2.f;
		sprite.setAnimation(PlayerAnimation::FIRE);
	}
	if (inputs.isHeld(VInput::UP)) {
		pos.y -= 2.f;
		sprite.setAnimation(PlayerAnimation::JUMP);
	}
	if (inputs.isHeld(VInput::DOWN)) {
		pos.y += 2.f;
		sprite.setAnimation(PlayerAnimation::STAND);
	}
	if (inputs.isPressed(VInput::A)) {
		sprite.flip();
	}

	this->setPosition(pos);
	sprite.update(deltaT, this->getPosition());
	// -------------------------


}


const SpriteManager& Player::getSprite() const {
	return this->sprite;
}