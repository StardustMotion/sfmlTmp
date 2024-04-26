#include "smSonicScene.hpp"


SonicScene::SonicScene(const sf::Vector2f& win, const ImageManager& img, const InputVirtual& inputs, AudioManager& audio)
	: img{ img }
	, inputs{ inputs }
	, audio{ audio }
	, backgrounds{
		{ win, img, static_cast<Parallaxes::Parallax>(Random::get(0,2)) },
		{ win, img, Parallaxes::WW_TOP } 
	}
		, actors{ {img} } {

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

	for (auto& actor : actors)
		actor.draw(canvas);
	
	sf::Text hud{ "[" + tos((int)camera.x) + ", " + tos((int)-camera.y) + "]", font, 24 };
	hud.setFillColor(sf::Color::White);
	sf::Vector2f center{ canvas.getView().getCenter() };
	hud.setPosition(center.x + (canvas.getView().getSize().x/2) - 192.f, center.y + (canvas.getView().getSize().y/2) - 80.f);
	canvas.draw(hud);
}

void SonicScene::onUpdate() {
	if (inputs.check(InputVirtual::LEFT)) {
		moveView(-camSpeed, 0);
	}
	else if (inputs.check(InputVirtual::RIGHT)) {
		moveView(camSpeed, 0);
	}
	if (inputs.check(InputVirtual::UP)) {
		moveView(0, -camSpeed);
	}
	else if (inputs.check(InputVirtual::DOWN)) {
		moveView(0, camSpeed);
	}

	for (auto& parallax : backgrounds)
		parallax.shift(-2.f, 0);
}

void SonicScene::moveView(float x, float y) {
	if (inputs.check(InputVirtual::A)) {
		x *= 3;
		y *= 3;
	}
	camera += {x, y};
}
