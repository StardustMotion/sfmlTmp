#include "smSonicScene.hpp"


SonicScene::SonicScene()
	: map ()
	, parallaxes{ Parallax_Heatman() }
	, player() {

	// camera CENTER cant exceed those
	mapLimits = {
		(((map.getMapSize().x * map.getTileSize()) - canvas().getSize().x) / 2.f) - 1.f,
		(((map.getMapSize().y * map.getTileSize()) - canvas().getSize().y) / 2.f) - 1.f,
	};

	//actors.emplace_back(ActorEmerl());


}
SonicScene::~SonicScene() { ; }



void SonicScene::onUpdate(double deltaT) {

	// alter player velocity based on their input
	player.update(deltaT);

	// alter further velocity with gravity
	//player.setVel(0, 1.25f, false);

	// apply velocity to change player position
	player.move(); // only accessible to SonicScene?

	//////////////////////////////////// COLLISIONS

	pd.setFillColor(sf::Color::Red);
	pd.setRadius(256.f);
	pd.setPosition(0, 0);

	std::vector<sf::Vector2f> tileShape(4);
	std::vector<sf::Vector2f> playerShape(4);
	tileScanners.clear();

	int retry = 3;
	do {
		playerShape = player.getShape();

		for (int i{ 0 }; i < 4; ++i) {
			sf::RectangleShape tmp;
			tmp.setSize({ 96, 96 });
			sf::Vector2i gridIndex(map.toIndex(playerShape[i]));
			if (map.getTile(gridIndex.x, gridIndex.y)->type)
				tmp.setFillColor(sf::Color(255, 0, 0, 190));
			else
				tmp.setFillColor(sf::Color(0, 255, 0, 190));

			tmp.setPosition(map.toWorld(gridIndex));
			tileScanners.push_back(tmp);

		}



		sf::Vector2i gridIndex(map.toIndex({ player.getX(), player.getY() }));
		if (!map.getTile(gridIndex.x, gridIndex.y)->type)
			break;
		sf::Vector2f tilePosition{ map.toWorld(gridIndex) };

		tileShape[0] = tilePosition;
		tileShape[1] = tilePosition + sf::Vector2f({ map.getTileSize(), 0 });
		tileShape[2] = tilePosition + sf::Vector2f({ map.getTileSize(), map.getTileSize() });
		tileShape[3] = tilePosition + sf::Vector2f({ 0, map.getTileSize() });

		if (isColliding(tileShape, playerShape)) {
			player.setPosition({ player.getX(), tilePosition.y - player.getHeight()/2.f });
			player.setVel(player.getVelX(), 0.f);
			retry--;
		}
		else
			break;

	} while (retry);




	//	sf::Vector2i scanTitle = map.toIndex(player.getPosition() + sf::Vector2f(0.f, player.bBox.getSize().y / 2.f));
	//	auto worldTilePos = map.toWorld(scanTitle);
	//	
	//	z

	//	if (map.getTile(scanTitle.x, scanTitle.y)->type && isColliding(zonehitbox, playerhitbox)) {
	//		player.bBox.setPosition(
	//			player.bBox.getPosition().x,
	//			worldTilePos.y - (player.bBox.getSize().y / 2.f));// map.getTileSize());
	//		player.setVel({ player.getVel().x, 0 }, true);

	//	}
	//}



	////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


	if (true) {

		/////////////////////// View alteration
		sf::View view{ canvas().getView() };

		view.setCenter({ player.getX(), player.getY() });

		// prevents camera from exceeding map limits
		////////////////////////////////////
		if (std::abs(view.getCenter().x) > mapLimits.x)
			view.setCenter(mapLimits.x * (view.getCenter().x > 0 ? 1 : -1), view.getCenter().y);

		if (std::abs(view.getCenter().y) > mapLimits.y)
			view.setCenter(view.getCenter().x, mapLimits.y * (view.getCenter().y > 0 ? 1 : -1));
		//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		canvas().setView(view);

		//\\\\\\\\\\\\\\\\\\\\\ View alteration ends


		for (auto& parallax : parallaxes)
			parallax.update(view);

	}


}


// rectangle /2 redundant check optimization?
bool SonicScene::isColliding(std::vector<sf::Vector2f>& shapeA, std::vector<sf::Vector2f>& shapeB) {
	std::vector<sf::Vector2f> normals;
	auto calcNormals{
		[&normals](std::vector<sf::Vector2f>& shape) {
			for (int vertex{ 0 }; vertex < shape.size() - 1; ++vertex) {
				sf::Vector2f normal = shape[vertex + 1] - shape[vertex];
				normals.emplace_back(-normal.y, normal.x);
			}
		}
	};

	// close the shape
	shapeA.push_back(shapeA[0]);
	shapeB.push_back(shapeB[0]);
	calcNormals(shapeA);
	calcNormals(shapeB);

	// Checks if the [axis] line can be drawn between both shapes without intersecting with any of them
	auto isSeperatingShapes {
		[](const sf::Vector2f& axis, const std::vector<sf::Vector2f>& shape1, const std::vector<sf::Vector2f>& shape2) -> bool {
			auto dotProduct{
				[](const sf::Vector2f& vec1, const sf::Vector2f& vec2) -> float {
					return vec1.x * vec2.x + vec1.y * vec2.y;
				}
			};
			float aMin = std::numeric_limits<float>::max();

			for (const auto& vertex : shape1) {
				float scalar = dotProduct(axis, vertex);
				aMin = std::min(aMin, scalar);
			}

			float bMax = std::numeric_limits<float>::lowest();
			for (const auto& vertex : shape2) {
				float scalar = dotProduct(axis, vertex);
				bMax = std::max(bMax, scalar);
			}
			return aMin > bMax;
		}
	};
	for (const sf::Vector2f& normal : normals) {
		if (isSeperatingShapes(normal, shapeA, shapeB))
			return false;
	}
	return true;
}

void SonicScene::onDraw() {


	// draw backgrounds/foregrounds
	for (auto& parallax : parallaxes)
		parallax.onDraw();

	// draw the tileset
	map.onDraw();

	// draw game objects
	player.onDraw();

	sf::Text hud{ "[" + tos((int)canvas().getView().getCenter().x) + ", " + tos((int)-canvas().getView().getCenter().y) + "]",
		getGameFont(), 48};
	hud.setFillColor(sf::Color::Cyan);
	hud.setOutlineColor(sf::Color::Black);
	hud.setOutlineThickness(6.f);
	sf::Vector2f center{ canvas().getView().getCenter() };
	hud.setPosition(center.x + (canvas().getView().getSize().x / 2) -
			hud.getString().getSize()*36.f, center.y - (canvas().getView().getSize().y / 2) + 32.f);
	canvas().draw(hud);

	for (auto scanner : tileScanners)
		canvas().draw(scanner);

}