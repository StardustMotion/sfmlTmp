#include "smParallax.hpp"

Parallax::Parallax(std::string&& texture, float scrollFactor, float scale)
	: scrollFactor(scrollFactor) {

	assert((scrollFactor >= 0 && scrollFactor <= 1.f) && "parallax scrollFactor must be within [0.f, 1.f]");
	sf::Texture* tex = img().getTexture(".\\res\\texture\\parallax\\" + texture).get();
	if (tex) {
		tex->setRepeated(true);
		sprite.setTexture(*tex);
		sf::Vector2i texSize = static_cast<sf::Vector2i>(tex->getSize());
		sprite.setTextureRect({ 0,0, 960, 720 });
		sprite.setScale(scale, scale);
		sprite.setPosition(0, 0);
	}
	else {
		Logger::warn("Could not load texture <" + texture + "> for Parallax");
	}
}


void Parallax::draw(sf::RenderTarget& canvas, sf::RenderStates states) const {
	canvas.draw(sprite);
}

void Parallax::update(const sf::View& view) {
	if (sprite.getTexture()) {
		sprite.setTextureRect({
			{ static_cast<sf::Vector2i>(view.getCenter()*scrollFactor) },
			{ static_cast<sf::Vector2i>(view.getSize()) }
		});
		sprite.setPosition({ view.getCenter() - (view.getSize()/2.f)});
	}
}