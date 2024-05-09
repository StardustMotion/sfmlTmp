#pragma once
#include <vector>
#include "tileson/tileson.h"
#include "smTile.hpp"
#include "smResourceHandler.hpp"

class SonicMap : public ResourceHandler
{
private:
	std::vector<Tile> map;
	sf::Vector2i mapSize;
	int tileBaseSize;
	float tileSize, halfTileSize;
	int tilesetColumns{ 2 };
	bool debug{ true };
	sf::Sprite tileSprite;

	// debug grid
	sf::RectangleShape gridLine;
	sf::Text coordinate;
public:
	SonicMap();

	void drawOn(sf::RenderTarget& canvas);

	// Return { x (columns), y (rows) } vector of map size
	const sf::Vector2i& getMapSize() const;

	// Get tile's real world (after scaling) size (a.k.a length of one of its sides)
	float getTileSize() const;

	// Convert floating world position to tile grid position 
	sf::Vector2i toIndex(const sf::Vector2f worldPosition) const;

	// Convert tile grid position to floating world position
	sf::Vector2f toWorld(sf::Vector2i indexPosition) const;

	// Get x/y tile on the grid / toss runtime error if out of bounds
	Tile* getTile(uint32_t x, uint32_t y);

	// Set x/y tile on the grid / toss runtime error if out of bounds
	void setTile(uint32_t x, uint32_t y, Tile&& newTile);

	// Check if tile index is out of bounds
	Tile* checkTileIndex(uint32_t x, uint32_t y);

	// Debug displays map grid/coordinates
	void toggleDebug();
};

