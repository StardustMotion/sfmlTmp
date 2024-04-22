#include "smBackground.hpp"


Background::Background(const ImageManager& img, image::Id imgId) {
	bg.setTexture(*img.get(imgId));
	bg.setTextureRect(sf::IntRect(0, 0, 256, 256));
}
Background::~Background() { ; }


void Background::fill(sf::RenderTexture& canvas) {

	sf::Vector2f size{ canvas.getView().getSize() };
	sf::Vector2f center{ canvas.getView().getCenter() };

	for (float x{ center.x-size.x - ((int)(center.x-size.x) % 256)}; x < center.x + size.x; x += 256.f) {
		for (float y{ center.y - size.y - ((int)(center.y-size.y) % 256) }; y < center.y + size.y; y += 256.f) {
			bg.setPosition(x, y);
			canvas.draw(bg);
		}
	}

}

