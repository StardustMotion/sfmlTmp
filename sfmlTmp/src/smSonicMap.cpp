#include "smSonicMap.hpp"


SonicMap::SonicMap() {
	static_assert(!((row | col) & 0x1) && "Map must have row/column as multiple of 2");
	map.resize(static_cast<std::size_t>(row * col), {}); // reserve
	tile.setScale(tileScale, tileScale);
	tile.setTextureRect({ 0, 0, 16, 16 });
	tile.setTexture(*img().getTexture(".\\res\\texture\\map\\test").get());
}

// == getTile[x][y] (tile at row x, column y)
Tile* SonicMap::getTile(std::int32_t tmpRow, std::int32_t tmpCol) {
	std::int32_t index = (col * tmpRow) + tmpCol;
	assert((index < (row * col)) && "Tried to get tile with index out of range");
	return &map[index];
}


sf::Vector2i SonicMap::toIndex(sf::Vector2f pos) {
	int tmpRow = static_cast<int>(std::floorf(pos.y / tileSize)) + (row >> 1);
	int tmpCol = static_cast<int>(std::floorf(pos.x / tileSize)) + (col >> 1);
	//Logger::info("return " + tos(tmpRow) + " and " + tos(tmpCol));

	return { tmpRow, tmpCol };
}

sf::Vector2f SonicMap::toWorld(int tmpRow, int tmpCol) {
	return { static_cast<float>(tmpCol - (col >> 1)) * tileSize,
			static_cast<float>(tmpRow - (row >> 1)) * tileSize };
}


void SonicMap::draw(sf::RenderTexture& canvas) {
	const sf::View& view = canvas.getView();
	sf::Vector2i sides = toIndex({
		view.getCenter().x - (view.getSize().x / 2.f),
		view.getCenter().y - (view.getSize().y / 2.f)
		});

	for (int tmpRow{ sides.x }; tmpRow < 1 + sides.x + static_cast<int>((view.getSize().y / tileSize)); ++tmpRow) {

		for (int tmpCol{ sides.y }; tmpCol < 1 + sides.y + static_cast<int>((view.getSize().x / tileSize)); ++tmpCol) {
			if (getTile(tmpRow, tmpCol)->visible) {
				tile.setPosition(toWorld(tmpRow, tmpCol));
				canvas.draw(tile);
			}
		}
	}


}

void SonicMap::toggleTile(const sf::View& view, const sf::Vector2i& position) {
	sf::Vector2i indexes = toIndex({
		view.getCenter().x - (view.getSize().x / 2.f) + position.x,
		view.getCenter().y - (view.getSize().y / 2.f) + position.y
		});
	
	getTile(indexes.x, indexes.y)->visible ^= 0x1;
	

}