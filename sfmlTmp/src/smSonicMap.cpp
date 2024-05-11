#include "smSonicMap.hpp"


SonicMap::SonicMap() {

	mapCanvas.create(canvas().getSize().x, canvas().getSize().y);
	slopeMask.setPointCount(3);
	slopeMask.setPoint(0, { 0,0 });
	slopeMask.setFillColor(sf::Color(0, 255, 255, 0));

	// parse map file data / parsing worlds maybe for current year+10
	tson::Tileson tileson;
	std::unique_ptr<tson::Map> jsonData = tileson.parse(".\\res\\texture\\map\\wilywars_heat.tmj");
	if (jsonData->getStatus() == tson::ParseStatus::OK) {
		mapSize.x = jsonData->getSize().x;
		mapSize.y = jsonData->getSize().y;
		map.resize(static_cast<std::size_t>(mapSize.x * mapSize.y), Tile());

		

		tileSprite.setTexture(*img().getTexture(".\\res\\texture\\map\\wilywars_heat").get());
		float gameScale = jsonData->get<float>("gameScale");
		if (!gameScale)
			gameScale = 4.f;
		tileBaseSize = jsonData->getTileSize().x;
		tileSize = tileBaseSize * gameScale; // tile.width==tile.height
		halfTileSize = tileSize / 2.f;
		tileSprite.setScale(gameScale, gameScale);
		tileSprite.setOrigin(tileBaseSize / 2.f, tileBaseSize / 2.f);
		tilesetColumns = jsonData->getTileset("tileset")->getColumns();

		auto& tileData = jsonData->getLayer("tiles")->getTileData();
		for (const auto& [id, tile] : tileData)
			setTile(std::get<0>(id), std::get<1>(id), Tile(tile->getId()));

		auto slopeData = jsonData->getLayer("slopes");
		for (const auto& slope : slopeData->getObjectsByName("ab")) {
			SonicSlope obj;

			obj.pos = toWorld({
				slope.getPosition().x / tileBaseSize,
				slope.getPosition().y / tileBaseSize 
			});

			int angle = static_cast<int>(slope.getRotation()) / 90; // 0 
			obj.direction = {
				static_cast<float>((angle % 2 ? slope.getSize().y : slope.getSize().x)) 
					* gameScale * (angle/2 ? -1 : 1),
				static_cast<float>((angle % 2 ? slope.getSize().x : slope.getSize().y))
					* gameScale * (!((angle - 1) & 0x2) ? 1 : -1)
			};			
			slopes.push_back({ obj });
		}
	}
	else
		Logger::error("Couldn't load SonicMap");

	// Debug grid
	gridLine.setFillColor(sf::Color(255, 255, 255, 96));
	coordinate.setFont(getGameFont());
	coordinate.setFillColor(sf::Color(255, 255, 255, 200));
	coordinate.setOutlineColor(sf::Color(0, 0, 0, 200));
	coordinate.setOutlineThickness(2.f);
	coordinate.setCharacterSize(static_cast<unsigned int>(tileSize/4.f));	

}

const sf::Vector2i& SonicMap::getMapSize() const {
	return this->mapSize;

}
float SonicMap::getTileSize() const {
	return this->tileSize;
}

sf::Vector2i SonicMap::toIndex(const sf::Vector2f worldPosition) const {
	return {
		(mapSize.x >> 1) + static_cast<int>(std::floorf(worldPosition.x / tileSize)),
		(mapSize.y >> 1) + static_cast<int>(std::floorf(worldPosition.y / tileSize))
	};
}

sf::Vector2f SonicMap::toWorld(sf::Vector2i indexPosition) const {
	return {
		tileSize * static_cast<float>(indexPosition.x - (mapSize.x >> 1)),
		tileSize * static_cast<float>(indexPosition.y - (mapSize.y >> 1)),
	};
}


Tile* SonicMap::getTile(uint32_t x, uint32_t y) {
	Tile* tile = checkTileIndex(x,y);
	assert(tile && "SonicMap::getTile returned nullptr");
	return tile;
}

void SonicMap::setTile(uint32_t x, uint32_t y, Tile&& newTile) {
	Tile* tile = checkTileIndex(x,y);
	assert(tile && "SonicMap::setTile returned nullptr");
	*tile = newTile;
}

Tile* SonicMap::checkTileIndex(uint32_t x, uint32_t y) {
	int index = (mapSize.x * y) + x;
	if (index >= mapSize.x * mapSize.y) {
		Logger::error("Tried to access index " + std::to_string(x) + "*" + std::to_string(y) +
			" >= " + std::to_string(mapSize.x) + "*" + std::to_string(mapSize.y));
		return nullptr;
	}
	return &map[index];
}

void SonicMap::toggleDebug() {
	this->debug ^= 1;
}



void SonicMap::onDraw() {
	mapCanvas.clear({ 0,0,0,0 });
	const sf::View& view = canvas().getView();
	mapCanvas.setView(view);

	sf::Vector2i startIndex{ toIndex({
		view.getCenter().x - (view.getSize().x / 2.f),
		view.getCenter().y - (view.getSize().y / 2.f)
	}) };
	sf::Vector2i endIndex{
		std::min((startIndex.x + 2) + static_cast<int>(view.getSize().x / tileSize),mapSize.x),
		std::min((startIndex.y + 2) + static_cast<int>(view.getSize().y / tileSize),mapSize.y)
	};



	for (auto x{ startIndex.x }; x < endIndex.x; ++x)
		for (auto y{ startIndex.y }; y < endIndex.y; ++y) {
			uint16_t type{ getTile(x,y)->type };
			if (type) {
				tileSprite.setPosition(toWorld({ x,y }) + sf::Vector2f(halfTileSize, halfTileSize));
				tileSprite.setTextureRect({
					(((type - 1) % tilesetColumns) * tileBaseSize),
					(((type - 1) / tilesetColumns) * tileBaseSize),
					tileBaseSize, tileBaseSize
				});
				mapCanvas.draw(tileSprite);
			}
		}

	// Draw a mask on tiles to shape the slopes
	for (const auto& slope : slopes) {
		slopeMask.setPosition(slope.pos);
		slopeMask.setPoint(1, { slope.direction });
		if (slope.direction.x < 0)
			if (slope.direction.y < 0) slopeMask.setPoint(2, { +slope.direction.x, 0 });
			else slopeMask.setPoint(2, { 0, +slope.direction.y });
		else
			if (slope.direction.y < 0) slopeMask.setPoint(2, { 0, +slope.direction.y });
			else slopeMask.setPoint(2, { +slope.direction.x, 0 });
		mapCanvas.draw(slopeMask, sf::BlendNone);
	}

	mapCanvas.display();
	sf::Sprite mapCanvasTexture { mapCanvas.getTexture() };
	mapCanvasTexture.setPosition(view.getCenter()-(view.getSize()/2.f));
	canvas().draw(mapCanvasTexture);

	if (debug) {
		auto drawGrid { 
			[&]  (bool axis, int index) {
				coordinate.setString("[" + std::to_string(index) + "]\n"
					+std::to_string(static_cast<int>(axis ? coordinate.getPosition().y : coordinate.getPosition().x)));
				canvas().draw(gridLine);
				canvas().draw(coordinate);
				if (axis) {
					coordinate.move(0.f, tileSize);
					gridLine.move(0.f, tileSize);
				}
				else {
					coordinate.move(tileSize, 0.f);
					gridLine.move(tileSize, 0.f);
				}
			}
		};

		coordinate.setPosition(toWorld({ startIndex.x, 0 }).x, view.getCenter().y);
		gridLine.setSize({ tileSize / 32.f, view.getSize().y });
		gridLine.setPosition(coordinate.getPosition().x, view.getCenter().y - (view.getSize().y / 2.f));
		for (auto x{ startIndex.x }; x < endIndex.x; ++x)
			drawGrid(false, x);

		coordinate.setPosition(view.getCenter().x, toWorld({ 0, startIndex.y }).y);
		gridLine.setSize({ view.getSize().x, tileSize / 32.f });
		gridLine.setPosition(view.getCenter().x - (view.getSize().x / 2.f), coordinate.getPosition().y);
		for (auto y{ startIndex.y }; y < endIndex.y; ++y) 
			drawGrid(true, y);
	}
}