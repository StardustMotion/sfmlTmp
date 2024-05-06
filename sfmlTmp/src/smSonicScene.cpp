#include "smSonicScene.hpp"


SonicScene::SonicScene()
	: map ()
	, parallaxes{ Parallax_Heatman(), Parallax_Topman() } {

	if (font.loadFromFile("res/font/sonic.ttf")) {
		Logger::info("font loaded");
	}

}
SonicScene::~SonicScene() { ; }



void SonicScene::onUpdate(double deltaT, sf::RenderTexture& canvas) {

	/////////////////////// View alteration
	sf::View view{ canvas.getView() };

	if (input().isHeld(VInput::VInputType::LEFT)) { view.move(-camSpeed, 0); }
	else if (input().isHeld(VInput::VInputType::RIGHT)) { view.move(+camSpeed, 0); }
	if (input().isHeld(VInput::VInputType::DOWN)) { view.move(0, +camSpeed); }
	else if (input().isHeld(VInput::VInputType::UP)) { view.move(0, -camSpeed); }

	canvas.setView(view);
	//\\\\\\\\\\\\\\\\\\\\\ View alteration ends



	if (input().pointer().has_value()) {
		if (input().isPressed(VInput::VInputType::A)) {
			map.toggleTile(view, input().pointer().value());
		}
	}


	if (input().isPressed(VInput::VInputType::A)) {
		actors.emplace_back(ActorEmerl());
	}

	for (Actor& actor : actors)
		actor.update(deltaT);

	for (auto& parallax : parallaxes)
		parallax.update(view);
}


void SonicScene::onDraw(sf::RenderTexture& canvas) {


	// draw backgrounds/foregrounds
	for (auto& parallax : parallaxes)
		canvas.draw(parallax);

	// draw the tileset
	map.draw(canvas);

	// draw game objects
	for (Actor& actor : actors)
		canvas.draw(actor);

	sf::Text hud{ "[" + tos((int)canvas.getView().getCenter().x) + ", " + tos((int)-canvas.getView().getCenter().y) + "]", font, 24 };
	hud.setFillColor(sf::Color::White);
	sf::Vector2f center{ canvas.getView().getCenter() };
	hud.setPosition(center.x + (canvas.getView().getSize().x / 2) - 192.f, center.y + (canvas.getView().getSize().y / 2) - 80.f);
	canvas.draw(hud);
}
