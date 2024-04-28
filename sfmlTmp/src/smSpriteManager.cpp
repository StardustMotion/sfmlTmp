#include "smSpriteManager.hpp"


SpriteManager::SpriteManager(const ImageManager& img):
	animations({ {0.2f,0.15f,1.5f}, {0.2f,0.12f,0.2f,0.12f}, {0.15f,0.1f,1.f} }) {
	sprite.setTexture(*img.get(image::Files::WILYWARS_CRASHMAN));
	sprite.setScale(3.f, 3.f);
	
	//sprite.setTextureRect({ 0,0,32,32, });
}
SpriteManager::~SpriteManager() { ; }

void SpriteManager::update(double deltaT, const sf::Vector2f& position) {
	sprite.setPosition(position);
	animDelta += static_cast<float>(deltaT);
	float time = animDelta;
	int index = 0;
	for (float i : animations[animId]) {
		time -= i;
		if (time <= 0.f) {
			break;
		}
		index++;
	}
	if (animDelta >= maxAnimationTime) {
		animDelta = std::fmod(animDelta, maxAnimationTime);
		index--;
	}
	sprite.setTextureRect({ 32 * index,32 * animId,32,32 });
}

void SpriteManager::setAnimation(std::uint8_t val) {
	this->animId = val;
	this->maxAnimationTime = 0.f;
	for (float i : animations[animId]) {
		maxAnimationTime += i;
	}
}

void SpriteManager::draw(sf::RenderTarget& canvas, sf::RenderStates states) const {

	canvas.draw(sprite);
}

//
//namespace AnimationDB {
//	std::vector<Animation> crashman {
//		{ AnimType::IDLE, {
//			{ 30, Frame(sf::IntRect(0,0,32,32)) },
//			{ 15, Frame(sf::IntRect(0,32,32,32)) },
//			{ 10, Frame(sf::IntRect(0,64,32,32)) }
//		} },
//
//		{ AnimType::RUN, {
//			{ 10, Frame(sf::IntRect(32,0,32,32)) },
//			{ 20, Frame(sf::IntRect(32,32,32,32)) },
//			{ 10, Frame(sf::IntRect(32,64,32,32)) },
//			{ 20, Frame(sf::IntRect(32,96,32,32)) }
//		} },
//
//		{ AnimType::JUMP, {
//			{ 10, Frame(sf::IntRect(64,0,32,32)) },
//			{ 20, Frame(sf::IntRect(64,32,32,32)) },
//			{ 10, Frame(sf::IntRect(64,64,32,32)) }
//		} },
//	};
//
//	std::vector<Animation> metalman{
//		{ AnimType::IDLE, {
//			{ 30, Frame(sf::IntRect(0,0,32,40)) },
//			{ 15, Frame(sf::IntRect(0,40,32,40)) },
//			{ 10, Frame(sf::IntRect(0,80,32,40)) }
//		} },
//
//		{ AnimType::RUN, {
//			{ 10, Frame(sf::IntRect(32,0,32,40)) },
//			{ 20, Frame(sf::IntRect(32,40,32,40)) },
//			{ 10, Frame(sf::IntRect(32,80,32,40)) },
//			{ 20, Frame(sf::IntRect(32,120,32,40)) }
//		} },
//
//		{ AnimType::JUMP, {
//			{ 10, Frame(sf::IntRect(64,0,32,40)) },
//			{ 20, Frame(sf::IntRect(64,40,32,40)) },
//			{ 10, Frame(sf::IntRect(64,80,32,40)) }
//		} },
//	};
//}
//
//SpriteManager::SpriteManager(const ImageManager& img, image::Files file)
//	: texture(img.get(file).get())
//	, animationList(file == 1 ? AnimationDB::crashman : AnimationDB::metalman) {
//
//	// sprite = { new sprite };
//	sprite.setTexture(*texture);
//	sprite.setScale(3.f, 3.f);
//	sprite.setTextureRect(animationList[0].getFrames()[0].second.crop); // default frame
//}
//
//SpriteManager::~SpriteManager() {
//	;
//}
//
//
//void SpriteManager::onDraw(sf::RenderTarget& canvas) const {
//	canvas.draw(sprite);
//}
//
//void SpriteManager::update(double deltaT, const sf::Vector2f& position) {
//	sprite.setPosition(position);
//}