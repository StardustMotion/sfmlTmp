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
	std::vector<Parallax> parallaxes;
	std::vector<Actor> actors;

	float camSpeed{ 4.f };
	sf::Vector2f offset{ 0.f,0.f };
	sf::Font font;

public:
	SonicScene();
	~SonicScene();
	void onUpdate(double deltaT, sf::RenderTexture& canvas);
	void onDraw(sf::RenderTexture& canvas);
};

