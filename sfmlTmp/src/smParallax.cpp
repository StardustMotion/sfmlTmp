#include "smParallax.hpp"

Parallax::Parallax(const sf::Vector2f& win, const ImageManager& img, const Parallaxes::Parallax id)
	: win(win)
	, speed(Parallaxes::entries[id].first.speed) {
	assert((speed >= 0 && speed <= 1.f) && "parallax speed must be within [0.f, 1.f]");
	bg.setTexture(*img.get(Parallaxes::entries[id].second));
	Parallaxes::ParallaxEntry entry = Parallaxes::entries[id].first;
	bg.setTextureRect({ entry.left, entry.top, entry.width, entry.height });
	bg.setScale({ (win.x / entry.width) * entry.xScale, (win.y / entry.width) * entry.yScale });
	bgSize = { bg.getScale().x * bg.getTextureRect().getSize().x, bg.getScale().y * bg.getTextureRect().getSize().y };
}
Parallax::~Parallax() { ; }


void Parallax::draw(sf::RenderTexture& canvas) {
	sf::Vector2f center { canvas.getView().getCenter() }, size{ canvas.getView().getSize()/2.f };

	// draw right to left, bottom to top
	float xBase, yBase;
	if (speed < 1.f) {
		xBase = (center.x + size.x) - std::fmod((center.x-offset.x) * speed, bgSize.x);
		xBase += std::ceilf(((center.x + size.x) - xBase) / bgSize.x) * bgSize.x;

		yBase = (center.y + size.y) - std::fmod((center.y-offset.y) * speed, bgSize.y);
		yBase += std::ceilf(((center.y + size.y) - yBase) / bgSize.y) * bgSize.y;
	}
	else {
		xBase = center.x + size.x + bgSize.x - std::fmod(center.x-offset.x, bgSize.x);
		yBase = center.y + size.y + bgSize.y - std::fmod(center.y-offset.y, bgSize.y);
	}

	for (float x{ xBase }; x > (center.x - size.x) - bgSize.x; x -= bgSize.x) {
		for (float y{ yBase }; y > (center.y - size.y) - bgSize.y; y -= bgSize.y) {
			bg.setPosition(x, y);
			canvas.draw(bg);
		}
	}
}

void Parallax::shift(float x, float y = 0) {
	offset += { x, y };
}

void Parallax::update(double deltaT) {
	//this->shift(-2.f, 0);
}

