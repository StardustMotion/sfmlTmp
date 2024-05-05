#pragma once
#include <SFML/Graphics.hpp>
#include "smVInput.hpp"
#include "smAnimation.hpp"
#include "smResourceHandler.hpp"

// game logic atom ("object"); alternative names "entity" / "unit"
//  "Actor" comes from Doom modding

// For some other mass producted object like particles or map tile we will use another class than actor
enum EmerlState : uint8_t {
	STAND = 0,
	RUN,
	JUMP
};

class Actor : 
	public sf::Transformable, 
	public sf::Drawable, 
	public ResourceHandler {

	sf::Sprite sprite;
	Animation* anim{ nullptr };
	std::uint8_t animSequence{ 0 };
	float animDelta{ 0.f }; // frame at that time of the animation
	float animMaxTime{ 0.f }; // how much time this animation takes
	bool resetAnim{ false };

	sf::Vector2f vel{ 0, 0 };

public:
	Actor(std::string&& texture);
	~Actor();
	void draw(sf::RenderTarget& canvas, sf::RenderStates states) const override;
	void flipSprite(bool side);
	void update(double deltaT);
	void setAnimSequence(std::uint8_t val,bool loop = true);
};

class ActorCrashman : public Actor {
public:
	ActorCrashman();
};

class ActorMetalman : public Actor {
public:
	ActorMetalman();
};

class ActorEmerl : public Actor {
public:
	ActorEmerl();
};