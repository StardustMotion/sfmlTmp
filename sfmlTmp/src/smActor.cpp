#include "smActor.hpp"



Actor::Actor(std::string&& texture) {
	sf::Texture* tex = TextureManager::getTexture(".\\res\\texture\\actor\\" + texture).get();
	if (tex) {
		this->sprite.setTexture(*tex);
		this->sprite.setScale(4.f, 4.f);
		this->anim = TextureManager::getAnim(texture);
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



void Actor::flip() {
	flipFlag = true;
}

void Actor::update(double deltaT) {
	sprite.setPosition(this->getPosition());
	if (flipFlag) {
		flipFlag = false;
		sprite.setScale(sprite.getScale().x * -1.f, sprite.getScale().y);
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
}

void Actor::setAnimSequence(std::uint8_t val, bool loop) {
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