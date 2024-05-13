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

	player.update(deltaT);

	// gravity
	player.setVel(0, 0.5f, false);

	// t -> t+1
	player.move();

	//////////////////////////////////// COLLISIONS

	tileScan();


	//std::vector<sf::Vector2f> tileShape(4);
	//std::vector<sf::Vector2f> playerShape(4);
	//tileScanners.clear();

	//int retry = 3;
	//do {
	//	playerShape = player.getShape();

	//	for (int i{ 0 }; i < 4; ++i) {
	//		sf::RectangleShape tmp;
	//		tmp.setSize({ 96, 96 });
	//		sf::Vector2i gridIndex(map.toIndex(playerShape[i]));
	//		if (map.getTile(gridIndex.x, gridIndex.y)->type)
	//			tmp.setFillColor(sf::Color(255, 0, 0, 190));
	//		else
	//			tmp.setFillColor(sf::Color(0, 255, 0, 190));

	//		tmp.setPosition(map.toWorld(gridIndex));
	//		tileScanners.push_back(tmp);

	//	}



	//	sf::Vector2i gridIndex(map.toIndex({ player.getX(), player.getY() }));
	//	if (!map.getTile(gridIndex.x, gridIndex.y)->type)
	//		break;
	//	sf::Vector2f tilePosition{ map.toWorld(gridIndex) };

	//	tileShape[0] = tilePosition;
	//	tileShape[1] = tilePosition + sf::Vector2f({ map.getTileSize(), 0 });
	//	tileShape[2] = tilePosition + sf::Vector2f({ map.getTileSize(), map.getTileSize() });
	//	tileShape[3] = tilePosition + sf::Vector2f({ 0, map.getTileSize() });

	//	if (isColliding(tileShape, playerShape)) {
	//		player.setPosition({ player.getX(), tilePosition.y - player.getHeight()/2.f });
	//		player.setVel(player.getVelX(), 0.f);
	//		retry--;
	//	}
	//	else
	//		break;

	//} while (retry);




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

	sf::CircleShape rect;
	rect.setRadius(map.getTileSize()/2.f);
	//rect.setSize({ map.getTileSize(), map.getTileSize() });
	for (int i{ 0 }; i < rasterMap.size(); ++i) {
		for (int j{ rasterMap[i].first }; j <= rasterMap[i].second; ++j) {
			if (map.getTile(j, i + rasterStart)->type) {
				rect.setFillColor(sf::Color(0, 255, 0, 128));
			}
			else {

				//rect.setFillColor(sf::Color(255, 0, 0, 128));
				rect.setFillColor(sf::Color(0, 255, 0, 128));
			}
			rect.setPosition(map.toWorld({ j, i+ rasterStart }));
			canvas().draw(rect);
		}
	}



}


void SonicScene::tileScan() {
	const std::array<sf::Vector2f, 4> shape = player.getShape();
	std::array<sf::Vector2i, 4> grid{
		map.toIndex(shape[0]),
		map.toIndex(shape[1]),
		map.toIndex(shape[2]),
		map.toIndex(shape[3]),
	};

	char angle = static_cast<int>(player.getAngle()) / 90.f;

	if (angle & 0x1)	rasterHeight = std::abs(grid[3].y - grid[1].y) + 1;
	else				rasterHeight = std::abs(grid[2].y - grid[0].y) + 1;

	rasterStart = grid[(4 - angle) & 0b11].y;

	// is AABB ?
	if (((grid[0].x == grid[1].x) && (grid[1].y == grid[2].y)) ||
		((grid[0].y == grid[1].y) && (grid[1].x == grid[2].x))) 
	{
		int low, high;
		if (grid[0].x < grid[2].x)	low = grid[0].x, high = grid[2].x;
		else						low = grid[2].x, high = grid[0].x;
		rasterMap = std::vector<std::pair<int, int>>(rasterHeight, { low, high });
		return;
	}


	// OBB
	std::array<std::vector<char>, 2> sides;

	// modulo 180°
	if (angle & 0x2)
		std::rotate(grid.begin(), grid.begin() + 2, grid.end());

	char flippedSide{ -1 };

	// https://www.youtube.com/watch?v=h3gDB89h0os
	auto rasterize{
		[&sides, &flippedSide] (sf::Vector2i start, sf::Vector2i end, bool side) -> void {
			if (std::abs(end.y - start.y) > std::abs(end.x - start.x)) {
				std::swap(start.x, start.y);
				std::swap(end.x, end.y);
				flippedSide = side;
			}		
			if (start.y > end.y)
				start.y -= 2 * (start.y - end.y);
			if (start.x > end.x)
				start.x -= 2 * (start.x - end.x);

			sf::Vector2i delta = end - start;
			int parameter = 2 * delta.y - delta.x;

			for (auto x{ start.x }; x <= end.x; ++x)
				if (parameter > 0) {
					parameter = parameter + 2 * delta.y - 2 * delta.x;
					sides[side].push_back(0);
				}
				else {
					parameter = parameter + 2 * delta.y;
					sides[side].push_back(1);
				}
		}
	};

	rasterize(grid[0], grid[1], 0);
	rasterize(grid[1], grid[2], 1);

	rasterMap = std::vector<std::pair<int, int>>(rasterHeight + 1, std::make_pair(INT_MAX, INT_MIN));

	auto drawSide{
		[&](int index, int delta, bool side) -> void {
			sf::Vector2i y1{ grid[index].x, grid[index].y - rasterStart };
			sf::Vector2i y2{ grid[delta].x, grid[delta].y - rasterStart };
			index = 0; delta = 0;
			int* pIndex{ &index };
			int* pDelta{ &delta };
			char xShift{ side ? -1 : 1 };
			if (flippedSide == side)
				std::swap(pIndex, pDelta);
			for (; (*pIndex) < sides[side].size(); (*pIndex)++) {
				rasterMap[y1.y + delta].second = std::max(rasterMap[y1.y + delta].second, y1.x + (xShift * index));
				rasterMap[y2.y + delta].first = std::min(rasterMap[y2.y + delta].first, y2.x + (xShift * index));
				if (!sides[side][(*pIndex)])
					(*pDelta)++;
			}
		}
	};
	
	// rotate >90 and >270 into >0 and >180
	if (angle & 0x1) {
		std::swap(sides[0], sides[1]);
		if (flippedSide >= 0)
			flippedSide = static_cast<bool>(!flippedSide);
		drawSide(3, 2, 0);
		drawSide(0, 3, 1);
	}
	else {
		drawSide(0, 3, 0);
		drawSide(1, 0, 1);
	}
}
