#pragma once
#include <SFML/Graphics.hpp>
#include "smImageManager.hpp"
#include "smVirtualInput.hpp"
#include "smAudioManager.hpp"
#include "smParallax.hpp"
#include "smRandom.hpp"
#include "smActor.hpp"
#include "smPlayer.hpp"


class SonicScene
{
	const ImageManager& img;
	const VirtualInput& inputs;
	AudioManager& audio;

	std::vector<Parallax> backgrounds;
	//std::vector<Actor> actors{};
	uint8_t camSpeed{ 8 };
	sf::Vector2f camera{ 0.f,0.f };
	sf::Font font;
	Player player;
public:
	SonicScene(const sf::Vector2f& win, const ImageManager& img, const VirtualInput& inputs, AudioManager& audio);
	~SonicScene();
	void onUpdate(double deltaT);
	void onDraw(sf::RenderTexture& canvas);
	void moveView(float x, float y);

};

