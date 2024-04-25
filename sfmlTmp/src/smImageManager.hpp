#pragma once
#include <string_view>
#include <memory>
#include <array>
#include <SFML/Graphics/Texture.hpp>


namespace image {
	constexpr std::string_view root = "res/img/parallax/";

	// In no particular order for now
	enum Files {
		FILES_START = -1,
		WILYWARS_PARALLAX,
		FILES_SIZE
	};
	constexpr std::array<std::string_view, FILES_SIZE> files{
		"wilywars_parallaxes.png"
	};

}

class ImageManager
{
	struct CachedTexture {
		image::Files id;
		std::shared_ptr<sf::Texture> texture;
	};

	std::vector<CachedTexture> cache;
public:
	ImageManager();
	~ImageManager();

	std::shared_ptr<sf::Texture> load(const image::Files imgId);
	std::shared_ptr<sf::Texture> get(image::Files imgId) const;
};

