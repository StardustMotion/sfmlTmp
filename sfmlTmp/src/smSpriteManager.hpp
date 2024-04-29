#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "smAnimation.hpp"
#include "smImageManager.hpp"
#include "smRandom.hpp"
#include "smLogger.hpp"

enum PlayerAnimation : std::uint8_t {
	STAND,
	FIRE,
	JUMP
};


class SpriteManager : public sf::Drawable {
	sf::Sprite sprite;

	std::uint8_t animId{ 0 }; // animation sequence index to play
	float animDelta{ 0.f }; // frame at that time of the animation
	float maxAnimationTime{ 1.f }; // how much time this animation takes
	bool flipFlag{ false };

	const std::vector<std::vector<float>> animations;
public:
	SpriteManager(const ImageManager& img);
	~SpriteManager();

	void draw(sf::RenderTarget& canvas, sf::RenderStates states) const override;
	void update(double deltaT, const sf::Vector2f& position);
	void setAnimation(std::uint8_t val);
	void flip();
};

//// orchestrates sprite display
//class SpriteManager
//{
//	sf::Sprite						sprite; // sf::Sprite* { new }
//	sf::Texture*					texture; // shared_ptr
//
//	const std::vector<Animation>	animationList;
//	std::size_t						animation{ 0 }; // which Animation sequence use
//	int								time{ 0 }; // which Frame (delta) of that animation to use 
//
//public:
//	SpriteManager(const ImageManager& img, image::Files file);
//	~SpriteManager();
//	/**
//	@brief switch animation sequence to the [type] one
//	**/
//
//	void onDraw(sf::RenderTarget& canvas) const;
//	void update(double deltaT, const sf::Vector2f& position);
//};

