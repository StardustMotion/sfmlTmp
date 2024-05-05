#include "smSonicScene.hpp"


SonicScene::SonicScene()
	: map () {
	/*, backgrounds{
		{ win, img, static_cast<Parallaxes::Parallax>(Random::get(0,2)) },
		{ win, img, Parallaxes::WW_TOP } 	}*/

	if (font.loadFromFile("res/font/sonic.ttf")) {
		Logger::info("font loaded");
	}

}
SonicScene::~SonicScene() { ; }



void SonicScene::onUpdate(double deltaT, const sf::View& view) {
	//for (auto& parallax : backgrounds)
	//	parallax.update(deltaT);

	if (input().isHeld(VInput::VInputType::LEFT)) { offset.x -= camSpeed; }
	else if (input().isHeld(VInput::VInputType::RIGHT)) { offset.x += camSpeed; }
	if (input().isHeld(VInput::VInputType::DOWN)) { offset.y += camSpeed; }
	else if (input().isHeld(VInput::VInputType::UP)) { offset.y -= camSpeed; }


	if (input().isPressed(VInput::VInputType::A)) {
		actors.emplace_back(ActorEmerl());
	}

	for (Actor& actor : actors)
		actor.update(deltaT);
}


void SonicScene::onDraw(sf::RenderTexture& canvas) {
	if (canvas.getView().getCenter() != offset)
		canvas.setView({ offset, canvas.getView().getSize() });


	//for (auto& parallax : backgrounds)
	//	parallax.draw(canvas);

	// draw the tileset
	map.draw(canvas);

	// draw game objects
	for (Actor& actor : actors)
		canvas.draw(actor);

	sf::Text hud{ "[" + tos((int)offset.x) + ", " + tos((int)-offset.y) + "]", font, 24 };
	hud.setFillColor(sf::Color::Red);
	sf::Vector2f center{ canvas.getView().getCenter() };
	hud.setPosition(center.x + (canvas.getView().getSize().x / 2) - 192.f, center.y + (canvas.getView().getSize().y / 2) - 80.f);
	canvas.draw(hud);
}
