#pragma once
#include <SFML/Graphics.hpp>
#include "smResourceHandler.hpp"
#include "smVInputHandler.hpp"


class Player : public ResourceHandler, public VInputHandler
{
	// default unscaled bounding box / scaled factors
	static constexpr float initWidth{ 32 }, initHeight{ 64 }, initScale{ 4.0f };
	static constexpr std::string_view texture{ ".\\res\\texture\\actor\\ww_metal" };

	// position/size stored here, not in Player itself
	sf::Sprite sprite;

	sf::Vector2f velocity{ 0.f,0.f };
	sf::RectangleShape boundingBox;


public:
	Player();
	void onDraw();
	void update(double deltaT);

	// replace=false to add velocity instead of setting it
	void setVel(float x, float y, bool replace = true);

	float getHeight() const;
	float getWidth() const;
	float getX() const;
	float getY() const;
	float getVelX() const;
	float getVelY() const;
	float getAngle();

	// applies my current velocity to my position
	void move();

	void setPosition(sf::Vector2f position);
	void setAngle(float angle, bool replace = false);
	std::array<sf::Vector2f, 4> getShape() const;


};
