#include "smSonicMap.hpp"


SonicMap::SonicMap(std::string&& name) {
	tson::Tileson tileson;

	std::unique_ptr<tson::Map> jsonData = tileson.parse(".\\res\\texture\\map\\" + name + ".tmj");
	
	tileBase.setTexture(*img().getTexture(".\\res\\texture\\map\\" + name).get());

	if (jsonData->getStatus() == tson::ParseStatus::OK) {
		row = jsonData->getSize().y, col = jsonData->getSize().x;
		map.resize(static_cast<std::size_t>(row * col), Tile()); // reserve

		tilesetColumns = jsonData->getTileset(name)->getColumns();
		tileSize = jsonData->getTileSize().x; // ,y
		tileScale = { 4.f }; // get cusotm property?
		tileWorldSize = static_cast<float>(tileSize * tileScale);
		tileBase.setScale(tileScale, tileScale);

		auto& tileData = jsonData->getLayer("heatman_test")->getTileData();
		for (const auto& [id, tile] : tileData)
			setTile(std::get<1>(id), std::get<0>(id), Tile(tile->getId()));
	}
	else {
		Logger::warn("Error while loading SonicMap");
	}

}


// == getTile[x][y] (tile at row x, column y)
Tile* SonicMap::getTile(std::int32_t tmpRow, std::int32_t tmpCol) {
	std::int32_t index = (col * tmpRow) + tmpCol;
	assert((index < (row * col)) && "Tried to GET tile with index out of range");
	return &map[index];
}

void SonicMap::setTile(std::int32_t tmpRow, std::int32_t tmpCol, const Tile&& tile) {
	std::int32_t index = (col * tmpRow) + tmpCol;
	assert((index < (row * col)) && "Tried to SET tile with index out of range");
	map[index] = tile;
}


sf::Vector2i SonicMap::toIndex(const sf::Vector2f pos) {
	int tmpRow = static_cast<int>(std::floorf(pos.y / tileWorldSize)) + (row >> 1);
	int tmpCol = static_cast<int>(std::floorf(pos.x / tileWorldSize)) + (col >> 1);
	return { tmpRow, tmpCol };
}

sf::Vector2f SonicMap::toWorld(int tmpRow, int tmpCol) const {
	return { static_cast<float>(tmpCol - (col >> 1)) * tileWorldSize,
			static_cast<float>(tmpRow - (row >> 1)) * tileWorldSize };
}


void SonicMap::draw(sf::RenderTexture& canvas) {
	const sf::View& view = canvas.getView();
	sf::Vector2i sides = toIndex({
		view.getCenter().x - (view.getSize().x / 2.f),
		view.getCenter().y - (view.getSize().y / 2.f)
	});

	for (int tmpRow{ sides.x }; tmpRow < 1 + sides.x + static_cast<int>((view.getSize().y / tileWorldSize)); ++tmpRow) {
		for (int tmpCol{ sides.y }; tmpCol < 1 + sides.y + static_cast<int>((view.getSize().x / tileWorldSize)); ++tmpCol) {
			uint16_t tile = getTile(tmpRow, tmpCol)->type;
			if (tile) {
				tileBase.setTextureRect({
					((tile-1) % tilesetColumns)* tileSize, ((tile-1) / tilesetColumns)*tileSize, 
					tileSize, tileSize 
				});
				tileBase.setPosition(toWorld(tmpRow, tmpCol));
				canvas.draw(tileBase);
			}
		}
	}
}

void SonicMap::toggleTile(const sf::View& view, const sf::Vector2i& position) {
	sf::Vector2i indexes = toIndex({
		view.getCenter().x - (view.getSize().x / 2.f) + position.x,
		view.getCenter().y - (view.getSize().y / 2.f) + position.y
		});
	
	getTile(indexes.x, indexes.y)->type ^= 0x1;
	

}


sf::Vector2f SonicMap::getMapLimits(const sf::Vector2f& canvasSize) const {
	sf::Vector2f limits = -toWorld(0, 0);
										// some extra padding due to rounding 
	limits.x -= ((canvasSize.x / 2.f) + (tileWorldSize/4.f));
	limits.y -= ((canvasSize.y / 2.f) + (tileWorldSize/4.f));
	return limits;
}