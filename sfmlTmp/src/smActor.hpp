#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "smImageManager.hpp"
#include "smSpriteManager.hpp"
#include "smInputVirtual.hpp"

//
//class Actor : public sf::Drawable, public sf::Transformable {
//
//public:
//	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
//};
//
//Actor::Actor() {
//	//this->setpo
//}


//// game logic atom ("object"); alternative names "entity" / "unit"
////  "Actor" comes from Doom modding
//class Actor : public sf::Drawable, public sf::Transformable
//{
//	SpriteManager spriteManager;
//public:
//	Actor(const ImageManager& img, image::Files file);
//	~Actor();
//	void update(double deltaT, const InputVirtual& inputs);
//	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
//};

