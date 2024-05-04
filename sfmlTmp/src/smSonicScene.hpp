#pragma once
#include <SFML/Graphics.hpp>
#include "smAudioManager.hpp"
#include "smParallax.hpp"
#include "smRandom.hpp"
#include "smActor.hpp"
#include "smVInputHandler.hpp"


class SonicScene : public VInputHandler
{
	//std::vector<Parallax> backgrounds;

	std::vector<Actor> actors;
	uint8_t camSpeed{ 8 };
	sf::Vector2f camera{ 0.f,0.f };
	sf::Font font;
public:
	SonicScene();
	~SonicScene();
	void onUpdate(double deltaT);
	void onDraw(sf::RenderTexture& canvas);
	void moveView(float x, float y);
};

