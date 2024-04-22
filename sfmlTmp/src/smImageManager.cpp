#include "smImageManager.hpp"
#include "smLogger.hpp"

// maybe later defer texture loading (i.e on new scene load)
ImageManager::ImageManager() {
	for (int id{ 0 }; id < static_cast<std::size_t>(image::Id::IMG_SIZE); ++id) {
		load(static_cast<image::Id>(id));
	}
}

ImageManager::~ImageManager() { ; }


std::shared_ptr<sf::Texture> ImageManager::load(image::Id imgId) {
	for (CachedTexture& data : cache)
		if (data.id == imgId) {
			Logger::info("Image " + std::string(image::files[static_cast<std::size_t>(imgId)]) + " already loaded");
			return data.texture;
		}

	std::shared_ptr texture = std::make_shared<sf::Texture>();
	std::string filePath = std::string(image::root) + std::string(image::files[static_cast<std::size_t>(imgId)]);
	Logger::info((texture->loadFromFile(filePath) ? 
		"Loaded image " : "Failed to load image ") + filePath);

	texture->setRepeated(true);
	//texture->setSmooth(true);
	cache.push_back(CachedTexture{imgId, texture});

	Logger::debug("image buffer is now size " + std::to_string(cache.size()));

	return texture;
}

std::shared_ptr<sf::Texture> ImageManager::get(image::Id imgId) const {
	for (const CachedTexture& data : cache)
		if (data.id == imgId)
			return data.texture;

	Logger::warn("Could not find image " + std::to_string(static_cast<int>(imgId)) + " in image cache");
	return nullptr;

}