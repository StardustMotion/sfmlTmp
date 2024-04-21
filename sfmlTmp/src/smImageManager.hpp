#pragma once
#include <string_view>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "smImage.hpp"

class ImageManager
{
	struct CachedTexture {
		image::Id id;
		std::shared_ptr<sf::Texture> texture;
	};

	std::vector<CachedTexture> cache;
public:
	ImageManager();
	~ImageManager();

	std::shared_ptr<sf::Texture> load(image::Id imgId);
	std::shared_ptr<sf::Texture> get(image::Id imgId) const;
};

