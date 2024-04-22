#pragma once
#include <SFML/Graphics.hpp>
#include "smImageManager.hpp"
#include "smInputVirtual.hpp"
#include "smAudioManager.hpp"
#include "smBackground.hpp"
#

class SonicScene
{
	const ImageManager& img;
	const InputVirtual& inputs;
	AudioManager& audio;

	Background bg;
	uint8_t camSpeed{ 4 };
	sf::Vector2f camera{ 0.f,0.f };
	sf::Font font;
public:
	SonicScene(const ImageManager& img, const InputVirtual& inputs, AudioManager& audio);
	~SonicScene();
	void onUpdate();
	void onDraw(sf::RenderTexture& canvas);
	void moveView(float x, float y);
};

