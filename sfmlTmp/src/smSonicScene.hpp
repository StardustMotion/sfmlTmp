#pragma once
#include <SFML/Graphics.hpp>
#include "smTextureManager.hpp"
#include "smVirtualInput.hpp"
#include "smAudioManager.hpp"
#include "smParallax.hpp"
#include "smRandom.hpp"
#include "smActor.hpp"


class SonicScene
{
	const TextureManager& img;
	const VirtualInput& inputs;
	AudioManager& audio;

	//std::vector<Parallax> backgrounds;
	std::vector<Actor> actors;
	uint8_t camSpeed{ 8 };
	sf::Vector2f camera{ 0.f,0.f };
	sf::Font font;
public:
	SonicScene(const sf::Vector2f& win, TextureManager& img, const VirtualInput& inputs, AudioManager& audio);
	~SonicScene();
	void onUpdate(double deltaT);
	void onDraw(sf::RenderTexture& canvas);
	void moveView(float x, float y);

};

