#include "smSonicScene.hpp"


SonicScene::SonicScene(const sf::Vector2f& win, const ImageManager& img, const VirtualInput& inputs, AudioManager& audio)
	: img{ img }
	, inputs{ inputs }
	, audio{ audio }
	, backgrounds{
		{ win, img, static_cast<Parallaxes::Parallax>(Random::get(0,2)) },
		{ win, img, Parallaxes::WW_TOP } 
	}
	, player{ inputs, img } {


	if (font.loadFromFile("res/font/sonic.ttf")) {
		Logger::info("font loaded");
	}
}
SonicScene::~SonicScene() { ; }

void SonicScene::onDraw(sf::RenderTexture& canvas) {
	if (canvas.getView().getCenter() != camera)
		canvas.setView({ camera, canvas.getView().getSize() });

	for (auto& parallax : backgrounds)
		parallax.draw(canvas);

	canvas.draw(player.getSprite());
	
	sf::Text hud{ "[" + tos((int)camera.x) + ", " + tos((int)-camera.y) + "]", font, 24 };
	hud.setFillColor(sf::Color::White);
	sf::Vector2f center{ canvas.getView().getCenter() };
	hud.setPosition(center.x + (canvas.getView().getSize().x/2) - 192.f, center.y + (canvas.getView().getSize().y/2) - 80.f);
	canvas.draw(hud);
}

void SonicScene::onUpdate(double deltaT) {

	for (auto& parallax : backgrounds)
		parallax.update(deltaT);

	player.update(deltaT);
}

void SonicScene::moveView(float x, float y) {
	camera += {x, y};
}
