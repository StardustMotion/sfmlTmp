#pragma once
#include <SFML/Graphics.hpp>
#include "smImageManager.hpp"
#include "smInputVirtual.hpp"
#include "smAudioManager.hpp"
#include "smParallax.hpp"
#include "smRandom.hpp"
#include "smActor.hpp"


class SonicScene
{
	const ImageManager& img;
	const InputVirtual& inputs;
	AudioManager& audio;

	std::vector<Parallax> backgrounds;
	std::vector<Actor> actors;
	uint8_t camSpeed{ 8 };
	sf::Vector2f camera{ 0.f,0.f };
	sf::Font font;
public:
	SonicScene(const sf::Vector2f& win, const ImageManager& img, const InputVirtual& inputs, AudioManager& audio);
	~SonicScene();
	void onUpdate();
	void onDraw(sf::RenderTexture& canvas);
	void moveView(float x, float y);
};

