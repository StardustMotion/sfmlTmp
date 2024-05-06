#include "smSonicScene.hpp"


SonicScene::SonicScene(const sf::Vector2f& canvasSize)
	: map ("wilywars_heat")
	, parallaxes{ Parallax_Heatman(), Parallax_Topman() } {

	mapLimits = map.getMapLimits(canvasSize);

	if (font.loadFromFile("res/font/sonic.ttf")) {
		Logger::info("font loaded");
	}

}
SonicScene::~SonicScene() { ; }



void SonicScene::onUpdate(double deltaT, sf::RenderTexture& canvas) {

	float camSpeed = (input().isHeld(VInput::VInputType::C)) ? 72.f : 24.f;

	/////////////////////// View alteration
	sf::View view{ canvas.getView() };

	if (input().isHeld(VInput::VInputType::LEFT)) { view.move(-camSpeed, 0); }
	else if (input().isHeld(VInput::VInputType::RIGHT)) { view.move(+camSpeed, 0); }
	if (input().isHeld(VInput::VInputType::DOWN)) { view.move(0, +camSpeed); }
	else if (input().isHeld(VInput::VInputType::UP)) { view.move(0, -camSpeed); }

	// prevents camera from exceeding map limits
	if (std::abs(view.getCenter().x) > mapLimits.x)
		view.move((std::abs(view.getCenter().x)-mapLimits.x)* (view.getCenter().x > 0 ? -1 : 1), 0);
	if (std::abs(view.getCenter().y) > mapLimits.y)
		view.move(0, (std::abs(view.getCenter().y) - mapLimits.y) * (view.getCenter().y > 0 ? -1 : 1));

	canvas.setView(view);
	//\\\\\\\\\\\\\\\\\\\\\ View alteration ends



	if (input().pointer().has_value()) {
		if (input().isPressed(VInput::VInputType::A)) {
			map.toggleTile(view, input().pointer().value());
		}
	}


	if (input().isPressed(VInput::VInputType::A))
		actors.emplace_back(ActorEmerl());

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