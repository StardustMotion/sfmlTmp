#include "smSonicScene.hpp"


SonicScene::SonicScene(const ImageManager& img, const InputVirtual& inputs, AudioManager& audio):
	img{ img },
	inputs{ inputs },
	audio{ audio },
	bg{ img, image::BG_MAIN } {

	if (font.loadFromFile("res/font/sonic.ttf")) {
		Logger::info("font loaded");
	}
}
SonicScene::~SonicScene() { ; }

void SonicScene::onDraw(sf::RenderTexture& canvas) {
	bg.fill(canvas);
	if (canvas.getView().getCenter() != camera)
		canvas.setView({ camera, canvas.getView().getSize() });
	
	sf::Text hud{ "[" + tos((int)camera.x) + ", " + tos((int)camera.y) + "]", font, 24 };
	hud.setFillColor(sf::Color::White);
	sf::Vector2f center{ canvas.getView().getCenter() };
	hud.setPosition(center.x + (canvas.getView().getSize().x/2) - 192.f, center.y + (canvas.getView().getSize().y/2) - 80.f);
	canvas.draw(hud);
}

void SonicScene::onUpdate() {
	if (inputs.check(InputVirtual::B)) {
		audio.sound(audio::SFX::DASH);
	}
	else if (inputs.check(InputVirtual::C)) {
		audio.sound(audio::SFX::MET);
	}
	else if (inputs.check(InputVirtual::START)) {
		audio.music(audio::BGM::MAIN);
	}
	else if (inputs.check(InputVirtual::A)) {
		audio.noMusic();
	}

	if (inputs.check(InputVirtual::LEFT)) {
		moveView(camSpeed, 0);
	}
	else if (inputs.check(InputVirtual::RIGHT)) {
		moveView(-camSpeed, 0);
	}
	if (inputs.check(InputVirtual::UP)) {
		moveView(0, camSpeed);
	}
	else if (inputs.check(InputVirtual::DOWN)) {
		moveView(0, -camSpeed);
	}

}

void SonicScene::moveView(float x, float y) {
	camera += {x, y};
	Logger::info("Camera is now (" + tos(camera.x) + "," + tos(camera.y) + ")");
}
