#pragma once
#include <SFML/Graphics.hpp>
#include "smResourceHandler.hpp"
#include "smParallax.hpp"
#include "smRandom.hpp"
#include "smActor.hpp"
#include "smVInputHandler.hpp"
#include "smTile.hpp"
#include "smSonicMap.hpp"

class SonicScene : public VInputHandler, public ResourceHandler
{
	SonicMap map;
	//std::vector<Parallax> backgrounds;
	std::vector<Actor> actors;

	uint8_t camSpeed{ 8 };
	sf::Vector2f offset{ 0.f,0.f };
	sf::Font font;



public:
	SonicScene();
	~SonicScene();
	void onUpdate(double deltaT, const sf::View& view);
	void onDraw(sf::RenderTexture& canvas);
};

