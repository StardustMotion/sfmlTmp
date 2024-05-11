#pragma once
#include <SFML/Graphics.hpp>
#include "smResourceHandler.hpp"
#include "smParallax.hpp"
#include "smRandom.hpp"
#include "smActor.hpp"
#include "smVInputHandler.hpp"
#include "smTile.hpp"
#include "smSonicMap.hpp"
#include "smPlayer.hpp"



class SonicScene : public ResourceHandler
{
	SonicMap map;
	std::vector<Parallax> parallaxes;
	Player player;
	constexpr static float gravity{ 0.05f }; // ?
	sf::Vector2f offset{ 0.f,0.f };
	sf::Vector2f mapLimits{ 2048.f, 1024.f }; // +/-
	void camera(float x, float y);

	sf::RectangleShape zone;
	std::vector<sf::RectangleShape> tileScanners;
	sf::CircleShape pd;

public:
	SonicScene();
	~SonicScene();
	void onUpdate(double deltaT);
	void onDraw();


	/**
	* checks if shapeA intersects with shapeB using separating axis theorem algorithm
	* @param shapeA list of vertex in the order to draw the shape. Add the 1st index at the end another time (as to close the polygon)
	* @return true if they collide
	*/
	bool isColliding(std::vector<sf::Vector2f>& shapeA, std::vector<sf::Vector2f>& shapeB);
};

