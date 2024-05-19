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

	tileCollision.setFillColor(sf::Color::Transparent);
	tileCollision.setOutlineColor(sf::Color::Cyan);
	tileCollision.setOutlineThickness(map.getTileSize() / 12.f);

	//actors.emplace_back(ActorEmerl());
	

}
SonicScene::~SonicScene() { ; }

void SonicScene::onUpdate(double deltaT) {

	player.update(deltaT);

	// gravity
	//player.setVel(0, 0.5f, false);

	// t -> t+1
	player.move();

	//////////////////////////////////// COLLISIONS

	tileScan();

	


	//std::vector<sf::Vector2f> tileShape(4);
	//std::vector<sf::Vector2f> playerShape(4);
	//tileScanners.clear();




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

	// draw backgrounds
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
	for (int i{ 0 }; i < rasterMap.size(); ++i) {
		for (int j{ rasterMap[i].first }; j <= rasterMap[i].second; ++j) {
			rect.setFillColor(sf::Color(0, 255, 0, 128));
			rect.setPosition(map.toWorld({ j, i+ collisionPos.y }));

			canvas().draw(rect);
		}
	}

	canvas().draw(tileCollision);

}



void SonicScene::tileScan() {



	const std::array<sf::Vector2f, 4> shape = player.getShape();
	std::array<sf::Vector2i, 4> grid{
		map.toIndex(shape[0]),
		map.toIndex(shape[1]),
		map.toIndex(shape[2]),
	};

	grid[3] = grid[2] - (grid[1] - grid[0]); // consistant rectangle
	Logger::info("scan " + tos(player.getAngle()) 
		+ tos(grid[0].x) + ", " + tos(grid[0].y) + " ||| "
		+ tos(grid[1].x) + ", " + tos(grid[1].y) + " ||| "
		+ tos(grid[2].x) + ", " + tos(grid[2].y) + " ||| "
		+ tos(grid[3].x) + ", " + tos(grid[3].y));


	char angle = static_cast<int>(player.getAngle()) / 90.f;
	bool deg90 = angle & 0x1;

	// tile scan top/left most position
	collisionPos.x = grid[(3 - angle) & 0b11].x;
	collisionPos.y = grid[(4 - angle) & 0b11].y;

	if (deg90) {
		collisionSize.y = std::abs(grid[3].y - grid[1].y);
		collisionSize.x = std::abs(grid[2].x - grid[0].x);
	}
	else {
		collisionSize.x = std::abs(grid[3].x - grid[1].x);
		collisionSize.y = std::abs(grid[2].y - grid[0].y);
	}


	// -----------------------------------------------
	//					AABB
	// -----------------------------------------------
	if (((grid[0].x == grid[1].x) && (grid[1].y == grid[2].y)) ||
		((grid[0].y == grid[1].y) && (grid[1].x == grid[2].x))) 
	{
		int low, high;
		if (grid[0].x < grid[2].x)	low = grid[0].x, high = grid[2].x;
		else						low = grid[2].x, high = grid[0].x;
		rasterMap = std::vector<std::pair<int, int>>(collisionSize.y+1, { low, high });
	}

	// -----------------------------------------------
	//					OBB
	// -----------------------------------------------
	else {

		std::array<std::vector<char>, 2> sides;

		// modulo 180°
		if (angle & 0x2)
			std::rotate(grid.begin(), grid.begin() + 2, grid.end());

		char flippedSide{ -1 };

		// https://www.youtube.com/watch?v=h3gDB89h0os
		auto rasterize{
			[&sides, &flippedSide](sf::Vector2i start, sf::Vector2i end, bool side) -> void {
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

				for (auto x{ start.x }; x < end.x; ++x)
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


		auto calcSides{
			[&](int index, int delta, bool side) -> void {
				sf::Vector2i y1{ grid[index].x, grid[index].y - collisionPos.y  };
				sf::Vector2i y2{ grid[delta].x, grid[delta].y - collisionPos.y  };
				index = 0; delta = 0;
				int* pIndex{ &index },* pDelta{ &delta };
				int shift = (side ? -1 : 1);
				if (flippedSide == side)
					std::swap(pIndex, pDelta);
				while (true) {
					rasterMap[y1.y + delta].second = std::max(y1.x + (shift * index), rasterMap[y1.y + delta].second);
					rasterMap[y2.y - delta].first = std::min(y2.x - (shift * index), rasterMap[y2.y - delta].first);
					if ((*pIndex) == sides[side].size())
						break;
					if (!sides[side][(*pIndex)])
						(*pDelta)++;
					(*pIndex)++;
				}
			}
		};

		rasterMap = std::vector<std::pair<int, int>>(collisionSize.y + 1, std::make_pair(INT_MAX, INT_MIN));
		if (deg90) {
			rasterize(grid[1], grid[2], 0);
			rasterize(grid[2], grid[3], 1);
			calcSides(3, 1, 0);
			calcSides(0, 2, 1);
		}
		else {
			rasterize(grid[0], grid[1], 0);
			rasterize(grid[1], grid[2], 1);
			calcSides(0, 2, 0);
			calcSides(1, 3, 1);
		}
	}






	//////////////////////////////////////////////////////////////////
	// Find the smallest rectangle (in tile size) containing all tiles the actor connects with
	//////////////////////////////////////////////////////////////////

	// if (rasterMap.size == 1 && rasterMap[0].first == rasterMap[1].second)...

	bool collision{ false };
	sf::Vector2i top, bottom;

	auto findY{
		[&]() -> void {
			auto tileCheck {
				[&](int y, bool direction) -> bool {
					for (int _x{ 0 }; _x <= rasterMap[y].second - rasterMap[y].first; ++_x) {
						const int x = (deg90 ^ direction ? rasterMap[y].first + _x : rasterMap[y].second - _x);
						if (map.getTile(x, y + collisionPos.y)->type) {
							if (direction)	bottom = { x, y };
							else			top = { x, y };
							return true;
						}
					}
					return false;
				}
			};

			// top -> bottom
			for (int y{ 0 }; y < rasterMap.size(); y++) {
				collision = tileCheck(y, false);
				if (collision)
					break;
			}

			if (!collision)
				return;

			// bottom -> top
			for (auto y{ rasterMap.size() - 1 }; y >= 0; y--)
				if (tileCheck(y, true))
					return;
			bottom = top;
		}
	};
	findY();

	if (collision) {
		int left, right;

		auto findX{
			[&]() -> void {
				auto xRanges = std::vector<std::pair<int,int>>(rasterMap.begin() + top.y, rasterMap.begin() + bottom.y + 1);

				std::vector<std::size_t> rightI(xRanges.size() - 1);
				auto leftI = rightI;

				std::iota(rightI.begin(), rightI.end(),		static_cast<std::size_t>(!deg90));
				std::iota(leftI.begin(), leftI.end(),		static_cast<std::size_t>(deg90));

				std::stable_sort(rightI.begin(), rightI.end(), [&xRanges](std::size_t a, std::size_t b) {
					return xRanges[a].second > xRanges[b].second; });
				std::stable_sort(leftI.begin(), leftI.end(), [&xRanges](std::size_t a, std::size_t b) {
					return xRanges[a].first < xRanges[b].first; });

				int* tileX;

				// right limit
				for (int i{ 0 }; ; ) {
					tileX = &xRanges[rightI[i]].second;
					if (*tileX <= right) break;
					if (map.getTile(*tileX, collisionPos.y + top.y + rightI[i])->type) {
						right = *tileX;
						break;
					}
					if ((i + 1) == rightI.size())
						i = 0;
					else
						if (xRanges[rightI[i + 1]].second < *tileX)		i = 0;
						else											i++;
					(*tileX)--;
				}

				// left limit
				for (int i{ 0 }; ; ) {
					tileX = &xRanges[leftI[i]].first;
					if (*tileX >= left) break;
					if (map.getTile(*tileX, collisionPos.y + top.y + leftI[i])->type) {
						left = *tileX;
						break;
					}
					if ((i + 1) == leftI.size())
						i = 0;
					else
						if (xRanges[leftI[i + 1]].first > *tileX)		i = 0;
						else											i++;
					(*tileX)++;
				}
			}
		};

		if (top.x < bottom.x)
			left = top.x, right = bottom.x;
		else
			left = bottom.x, right = top.x;

		if (top.y != bottom.y)
			findX();

		tileCollision.setPosition(map.toWorld({ left, top.y + collisionPos.y }));
		tileCollision.setSize({ (right - left + 1) * map.getTileSize(), (bottom.y - top.y + 1) * map.getTileSize() });
	}
	else {
		tileCollision.setSize({ 0,0 });
	}









}
