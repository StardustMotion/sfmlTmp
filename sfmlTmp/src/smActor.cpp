#include "smActor.hpp"



Actor::Actor(std::string&& texture) {
	sf::Texture* tex = img().getTexture(".\\res\\texture\\actor\\" + texture).get();
	if (tex) {
		this->sprite.setTexture(*tex);
		this->sprite.setScale(3.f, 3.f);
		this->anim = img().getAnim(texture);
		if (!this->anim)
			Logger::warn("Could not load animation <" + texture + "> for Actor");
		else {
			this->sprite.setOrigin(	static_cast<float>(this->anim->size.x) / 2.f, 
									static_cast<float>(this->anim->size.y) / 2.f);
			setAnimSequence(0);
		}
	}
	else {
		Logger::warn("Could not load texture <" + texture + "> for Actor");
	}
}

Actor::~Actor() { ; }


void Actor::draw(sf::RenderTarget& canvas, sf::RenderStates states) const {
	canvas.draw(sprite);
}



void Actor::flipSprite(bool side) {
	if ((side && (sprite.getScale().x<0)) || (!side && (sprite.getScale().x>0)))
		sprite.setScale(sprite.getScale().x * -1.f, sprite.getScale().y);
}

void Actor::update(double deltaT) {
	float tmpSpd{ 0.15f };
	if (VInput::isPressed(VInput::C) && getPosition().y == 0.f) {
		vel.y = 20.f;
		setAnimSequence(EmerlState::JUMP, false);
	}
	else if (getPosition().y == 0.f) {
		if (VInput::isHeld(VInput::LEFT)) {
			vel.x -= tmpSpd;
			setAnimSequence(EmerlState::RUN);
			flipSprite(0);
		}
		else if (VInput::isHeld(VInput::RIGHT)) {
			vel.x += tmpSpd;
			setAnimSequence(EmerlState::RUN);
			flipSprite(1);
		}
		else if (abs(vel.x) < 0.2f) {
			setAnimSequence(EmerlState::STAND);
			setAnimSequence(0);
		}
	}
	else {
		vel.y -= 1.f;
	}

	if (anim) {
		animDelta += static_cast<float>(deltaT);
		float time = animDelta;
		int index = 0;

		for (const AnimationFrame& frame : anim->frames[animSequence]) {
			time -= frame.t;
			if (time <= 0.f)
				break;
			index++;
		}
		index %= anim->frames[animSequence].size();
		if (animMaxTime && (animDelta >= animMaxTime)) // <-- for looping animations
			animDelta = std::fmod(animDelta, animMaxTime);
		sf::Vector2i crop = anim->frames[animSequence][index].crop;
		sprite.setTextureRect({ crop.x, crop.y, anim->size.x, anim->size.y });
	}

	// collision resolution
	move(vel.x, (getPosition().y+vel.y) < 0 ? -(getPosition().y) : vel.y);

	sprite.setPosition(getPosition().x, -getPosition().y);
}

void Actor::setAnimSequence(std::uint8_t val, bool loop) {
	if (animSequence == val) 
		return;
	animSequence = val;
	animMaxTime = 0.f; // to cache
	animDelta = 0.f;
	if (!loop) return;
	for (AnimationFrame frame : anim->frames[val])
		animMaxTime += frame.t;
}



ActorCrashman::ActorCrashman():
	Actor{ "ww_crash" } {

}
ActorMetalman::ActorMetalman() :
	Actor{ "ww_metal" } {

}
ActorEmerl::ActorEmerl() :
	Actor{ "emerl" } {

}