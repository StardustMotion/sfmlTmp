#include "smScene.hpp"


Scene::Scene(sf::RenderWindow& window, const ImageManager& img, const InputVirtual& inputs, AudioManager& audio):
	window{ window },
	img{ img },
	inputs{ inputs },
	audio{ audio },
	view{ sf::FloatRect(0.0f,0.0f,256.0f,256.0f) } {

	bg.setTexture(*img.get(image::BG_MAIN));
	window.setView(view);
	;
}
Scene::~Scene() { ;  }

void Scene::onDraw(sf::RenderTexture& canvas) {
	 // canvas.draw(sprite...)
	const sf::Vector2u offset = bg.getTexture()->getSize();

	int x = (state ? 0 : offset.y);
	bg.setTextureRect(sf::IntRect(x, 0, offset.y, offset.y));
	bg.setPosition(0, 0);
	canvas.draw(bg);

}

void Scene::onUpdate() {
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
	else if (inputs.check(InputVirtual::LEFT)) {
		state = true;
	}
	else if (inputs.check(InputVirtual::RIGHT)) {
		state = false;
	}
}