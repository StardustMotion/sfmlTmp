#pragma once
#include <vector>
#include "smTile.hpp"
#include "smResourceHandler.hpp"

class SonicMap : public ResourceHandler
{
	static constexpr int32_t row{ 32 }, col{ 64 };
	std::vector<Tile> map;
	sf::Sprite tile;
	float tileSize = 64.f;
	float tileScale = tileSize / 16.f;
	Tile* getTile(std::int32_t tmpRow, std::int32_t tmpCol);
	sf::Vector2i toIndex(sf::Vector2f pos);
	sf::Vector2f toWorld(int tmpRow, int tmpCol);
public:
	SonicMap();
	void draw(sf::RenderTexture& canvas);
	void toggleTile(const sf::View& view, const sf::Vector2i& position);
};

