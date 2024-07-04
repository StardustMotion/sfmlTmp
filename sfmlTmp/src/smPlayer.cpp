#include "smPlayer.hpp"

Player::Player() {
	sprite.setTexture(*img().getTexture(std::string(texture)).get());
	sprite.setTextureRect({ 0,0, static_cast<int>(initWidth), static_cast<int>(initHeight) });
	sprite.setOrigin(initWidth / 2.f, initHeight / 2.f);
	sprite.setScale(initScale, initScale);

	boundingBox.setFillColor(sf::Color(255, 0, 0, 128));
	boundingBox.setSize({ initWidth * initScale, initHeight * initScale });
	boundingBox.setOrigin(initWidth * initScale / 2.f, initHeight * initScale / 2.f);
}


void Player::update(double deltaT) {
	
	float maxSpd = 8.f;
	float sped = 0.35f;
	if (VInput::isHeld(VInput::LEFT))		
		setVel(std::max(getVelX() - sped, -maxSpd), getVelY());
	else if (VInput::isHeld(VInput::RIGHT))
		setVel(std::min(getVelX() + sped, maxSpd), getVelY());
	else if (std::abs(getVelX()) < sped * 4.f)
		setVel(0, getVelY());

	
	if (VInput::isHeld(VInput::UP)) {
		setVel(getVelX(), std::max(getVelY() - sped, -maxSpd));
	}
	else if (VInput::isHeld(VInput::DOWN)) {
		setVel(getVelX(), std::min(getVelY() + sped, +maxSpd));
	}


	if (VInput::isPressed(VInput::C))
		setVel(getVelX(), -18.f);


	if (VInput::isHeld(VInput::A))
		setAngle(2.f);
	if (VInput::isHeld(VInput::B))
		setAngle(-2.f);

	//if (VInput::isHeld(VInput::VInputType::C))
	//	print();
}

void Player::onDraw() {
	canvas().draw(sprite);
	canvas().draw(boundingBox);
}

void Player::setVel(float velx, float vely, bool replace) {
	if (replace) velocity = { velx,vely };
	else velocity += { velx, vely };
}

float Player::getWidth() const { return boundingBox.getSize().x; }
float Player::getHeight() const { return boundingBox.getSize().y; }
float Player::getX() const { return boundingBox.getPosition().x ; }
float Player::getY() const { return boundingBox.getPosition().y; }
float Player::getVelX() const { return velocity.x; }
float Player::getVelY() const { return velocity.y; }
float Player::getAngle() { return boundingBox.getRotation(); }



void Player::move() {
	boundingBox.move(velocity);
	sprite.setPosition(boundingBox.getPosition());
}

void Player::setPosition(sf::Vector2f position) {
	boundingBox.setPosition(position);
	sprite.setPosition(boundingBox.getPosition());
}

void Player::setAngle(float angle, bool replace) {
	if (replace)
		boundingBox.setRotation(angle);
	else
		boundingBox.setRotation(getAngle() + angle);
	sprite.setRotation(boundingBox.getRotation());
}

std::array<sf::Vector2f,4> Player::getShape() const {
	return {
		boundingBox.getTransform() * boundingBox.getPoint(0),
		boundingBox.getTransform() * boundingBox.getPoint(1),
		boundingBox.getTransform() * boundingBox.getPoint(2),
		boundingBox.getTransform() * boundingBox.getPoint(3),
	};
}



//void Player::print() {
//	auto pos = bBox.getPosition();
//	lo::debug("Player (" + 
//		tos((int) bBox.getSize().x) + "," + tos((int) bBox.getSize().y)
//		+ ") [pos " + tos(pos.x) + ", " + tos(pos.y) + "] "
//		+ ") <spd " + tos(vel.x) + ", " + tos(vel.y) + "> ");
//}
//
//
//