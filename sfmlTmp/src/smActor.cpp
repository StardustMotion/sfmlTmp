#include "smActor.hpp"

//Actor::Actor(const ImageManager& img, image::Files file):
//	spriteManager(img, file) {
//	this->setPosition((float)Random::get(-120, 120),0);
//}
//
//Actor::~Actor() { ; }
//
//void Actor::update(double deltaT, const InputVirtual& inputs) {
//	if (inputs.check(InputVirtual::A)) {
//		this->move(-2.f, 0.f);
//	}	else if (inputs.check(InputVirtual::B)) {
//		this->move(2.f, 0.f);
//	}
//	spriteManager.update(deltaT, this->getPosition());
//}
//
//void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//	spriteManager.onDraw(target);
//}