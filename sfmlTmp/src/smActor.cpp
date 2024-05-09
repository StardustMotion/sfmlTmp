#include "smActor.hpp"



Actor::Actor(std::string&& texture) {
	sf::Texture* tex = img().getTexture(".\\res\\texture\\actor\\" + texture).get();

	if (tex) {
		this->sprite.setTexture(*tex);
		float scaledTo = 2.f;
		this->sprite.setScale(scaledTo, scaledTo);
		this->anim = img().getAnim(texture);
		if (!this->anim)
			Logger::warn("Could not load animation <" + texture + "> for Actor");
		else {
			setAnimSequence(0);
			bbox = { scaledTo*static_cast<float>(this->anim->size.x), scaledTo*static_cast<float>(this->anim->size.y) };
			this->sprite.setOrigin(bbox.x / 2.f / scaledTo, bbox.y / 2.f / scaledTo);
		}
	}
	else {
		Logger::warn("Could not load texture <" + texture + "> for Actor");
	}

	bboxSprite.setSize(bbox);
	bboxSprite.setFillColor(sf::Color(255, 0, 0, 128));
	bboxSprite.setOrigin(bbox.x / 2.f, bbox.y / 2.f);

	this->setPosition(0, 0);
}

Actor::~Actor() { ; }


void Actor::draw(sf::RenderTarget& canvas, sf::RenderStates states) const {
	canvas.draw(sprite);
	canvas.draw(bboxSprite);

	sf::CircleShape dot;
	dot.setRadius(4);
	dot.setOutlineColor(sf::Color::Red);
	dot.setOutlineThickness(2);
	dot.setPosition(this->getPosition());
	dot.setOrigin(dot.getRadius(), dot.getRadius());

	canvas.draw(dot);

	unsigned int fontSize = 12;

	sf::Text poato;
	poato.setCharacterSize(fontSize);
	//poato.setFont(getGameFont());
	poato.setString(tos((int)sprite.getPosition().x) + "," + tos((int)sprite.getPosition().y));
	poato.setPosition(sprite.getPosition() + sprite.getOrigin());
	poato.setOrigin(static_cast<float>(poato.getString().getSize() * fontSize / 2.f), 6);
	poato.setFillColor(sf::Color::Yellow);
	canvas.draw(poato);
}



void Actor::flipSprite(bool side) {
	if ((side && (sprite.getScale().x<0)) || (!side && (sprite.getScale().x>0)))
		sprite.setScale(sprite.getScale().x * -1.f, sprite.getScale().y);
}

void Actor::update(double deltaT) {
	sprite.setPosition(this->getPosition());
	bboxSprite.setPosition(this->getPosition());
	
	

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

void Actor::setAirbone(bool status) {
	//this->airbone = status;
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