#pragma once
#include <vector>
#include "tileson/tileson.h"
#include "smTile.hpp"
#include "smResourceHandler.hpp"

class SonicMap : public ResourceHandler
{
	int32_t row{ 32 }, col{ 64 };
	std::vector<Tile> map;
	sf::Sprite tileBase;
	uint8_t tileSize{ 16 }; // tile size (on the tileset/in pixels)
	float tileScale{ 4.f };
	float tileWorldSize{ static_cast<float>(tileSize*tileScale) };
	uint8_t tilesetColumns{ 4 };



	Tile* getTile(std::int32_t tmpRow, std::int32_t tmpCol);
	void setTile(std::int32_t tmpRow, std::int32_t tmpCol, const Tile&& tile);
	sf::Vector2i toIndex(const sf::Vector2f pos);
	sf::Vector2f toWorld(int tmpRow, int tmpCol) const;
public:
	// name of the map structure file (.tmj)
	SonicMap(std::string&& name);
	void draw(sf::RenderTexture& canvas);
	void toggleTile(const sf::View& view, const sf::Vector2i& position);
	
	// Return the maximum view center x,y position (+/-) to not exceed
	sf::Vector2f getMapLimits(const sf::Vector2f& canvasSize) const;
};

