#include "smSonicScene.hpp"


SonicScene::SonicScene(const sf::Vector2f& canvasSize)
	: map ()
	, parallaxes{ Parallax_Heatman() } {

	// camera CENTER cant exceed those
	mapLimits = {
		(((map.getMapSize().x * map.getTileSize()) - canvasSize.x) / 2.f) - 1.f,
		(((map.getMapSize().y * map.getTileSize()) - canvasSize.y) / 2.f) - 1.f,
	};

	actors.emplace_back(ActorEmerl());

}
SonicScene::~SonicScene() { ; }



void SonicScene::onUpdate(double deltaT, sf::RenderTexture& canvas) {

	float camSpeed = (input().isHeld(VInput::VInputType::C)) ? 72.f : 24.f;

	/////////////////////// View alteration
	sf::View view{ canvas.getView() };

	view.setCenter(actors.back().getPosition());

	sf::Vector2f pos = actors.back().getPosition();
	view.setCenter(pos.x, pos.y);

	// prevents camera from exceeding map limits
	////////////////////////////////////
	if (std::abs(view.getCenter().x) > mapLimits.x)
		view.setCenter(mapLimits.x * (view.getCenter().x > 0 ? 1 : -1), view.getCenter().y);

	if (std::abs(view.getCenter().y) > mapLimits.y)
		view.setCenter(view.getCenter().x, mapLimits.y * (view.getCenter().y > 0 ? 1 : -1));
	//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	canvas.setView(view);
	
	//\\\\\\\\\\\\\\\\\\\\\ View alteration ends



	if (input().pointer().has_value()) {
		if (input().isPressed(VInput::VInputType::A)) {
			//map.toggleTile(view, input().pointer().value());
		}
	}

	Actor& player = actors.back();
	player.update(deltaT);

	for (auto& parallax : parallaxes)
		parallax.update(view);

	if (VInput::isPressed(VInput::VInputType::C)) {
		player.vel.y = -20.f;
	}

	float tmpSpd{ 0.75f };
	if (VInput::isHeld(VInput::LEFT)) {
		player.vel.x = std::max(-10.f, player.vel.x - tmpSpd);
		player.setAnimSequence(EmerlState::RUN);
		player.flipSprite(0);
	}
	else if (VInput::isHeld(VInput::RIGHT)) {
		player.vel.x = std::min(10.f, player.vel.x + tmpSpd);
		player.setAnimSequence(EmerlState::RUN);
		player.flipSprite(1);
	}
	if (VInput::isHeld(VInput::UP)) {
		player.vel.y = std::max(-10.f, player.vel.y - tmpSpd);
	}
	else if (VInput::isHeld(VInput::DOWN)) {
		player.vel.y = std::min(10.f, player.vel.y + tmpSpd);
	}

	// collision resolution
	mapCollision(player);

}

void SonicScene::mapCollision(Actor& actor) {
	actor.move(actor.vel);
	//auto index = map.toIndex({ actor.getPosition().x, actor.getPosition().y + (actor.bbox.y + map.tileSize) / 2.f });
	//	if (map.getTile(index.x, index.y)->type) {
	//		actor.vel.y = 0;
	//		auto tmp = map.toWorld(0, index.y);
	//		actor.setPosition(actor.getPosition().x, tmp.y);
	//	}
	//	else {
	//		actor.vel.y += 0;// 0.25f;
	//	}
	//}

}


void SonicScene::onDraw(sf::RenderTexture& canvas) {


	// draw backgrounds/foregrounds
	for (auto& parallax : parallaxes)
		canvas.draw(parallax);

	// draw the tileset
	map.drawOn(canvas);

	// draw game objects
	for (Actor& actor : actors)
		canvas.draw(actor);

	sf::Text hud{ "[" + tos((int)canvas.getView().getCenter().x) + ", " + tos((int)-canvas.getView().getCenter().y) + "]", 
		getGameFont(), 48};
	hud.setFillColor(sf::Color::Cyan);
	hud.setOutlineColor(sf::Color::Black);
	hud.setOutlineThickness(6.f);
	sf::Vector2f center{ canvas.getView().getCenter() };
	hud.setPosition(center.x + (canvas.getView().getSize().x / 2) - 
			hud.getString().getSize()*36.f, center.y - (canvas.getView().getSize().y / 2) + 32.f);
	canvas.draw(hud);
}