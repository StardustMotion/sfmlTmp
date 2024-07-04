#include "smSonicScene.hpp"


SonicScene::SonicScene()
	: map ()
	, parallaxes{ Parallax_Hardman() }
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
	//player.setVel(0, 0.8f, false);

	// t -> t+1
	player.move();

	//////////////////////////////////// COLLISIONS

	tileScan();



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
		map.toIndex(shape[3]),
	};

	char angle = static_cast<int>(player.getAngle()) / 90.f;
	// tile scan top/left most position
	collisionPos.x = grid[(3 - angle) & 0b11].x;
	collisionPos.y = grid[(4 - angle) & 0b11].y;
	bool deg90 = angle & 0x1;


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

	auto aabbMap{ 
		[&]() {
			return std::vector<std::pair<int,int>>(collisionSize.y + 1, 
				std::make_pair<>(collisionPos.x, collisionPos.x + collisionSize.x));
		} 
	};
	if ((grid[0].y == grid[1].y) && (grid[1].x == grid[2].x) && (grid[2].y == grid[3].y))
		rasterMap = aabbMap();

	else if ((grid[0].x == grid[1].x) && (grid[1].y == grid[2].y) && (grid[2].x == grid[3].x))
		rasterMap = aabbMap();



	// -----------------------------------------------
	//					OBB
	// -----------------------------------------------

	else {
		rasterMap = std::vector<std::pair<int, int>>(collisionSize.y + 1);

		// https://www.youtube.com/watch?v=h3gDB89h0os
		auto rasterize{
			[&](sf::Vector2i start, sf::Vector2i end)  -> void {
				bool side = (end.y > start.y);
				bool direction = (end.x > start.x);

				sf::Vector2i delta = {
					std::abs(end.x - start.x),
					std::abs(end.y - start.y),
				};
				start.y -= collisionPos.y;

				int increment{ 0 },* pIncrement{ &increment };
				int t{ 0 },* pt{ &t };
				if (delta.y > delta.x) {
					std::swap(delta.x, delta.y);
					std::swap(pt, pIncrement);
				}

				int parameter = 2 * delta.y - delta.x;
				for (; (*pt) <= delta.x; (*pt)++) {
					if (side)
						rasterMap[start.y + increment].second = start.x + (direction ? t : -t);
					else
						rasterMap[start.y - increment].first = start.x + (direction ? t : -t);

					if (parameter > 0) {
						(*pIncrement)++;
						parameter += (2 * delta.y - 2 * delta.x);
					}
					else
						parameter += (2 * delta.y);
				}
			}
		};

		rasterize(grid[0], grid[1]);
		rasterize(grid[1], grid[2]);
		rasterize(grid[2], grid[3]);
		rasterize(grid[3], grid[0]);

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

				std::vector<int> rightI(xRanges.size() - 1);
				std::vector<int> leftI = rightI;

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


		//////////////////////////////////////////////////////////////////
		// Resolve collision
		//////////////////////////////////////////////////////////////////
		//player.setPosition({ player.getX(), tileCollision.getPosition().y-player.getHeight()/2.f});
		//player.setVel(player.getVelX(), 0);
	}




	// no collision 
	else {
		tileCollision.setSize({ 0,0 });
	}









}
