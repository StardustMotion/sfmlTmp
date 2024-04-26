#include "smImageManager.hpp"
#include "smLogger.hpp"

// maybe later defer texture loading (i.e on new scene load)
ImageManager::ImageManager() {
	for (std::size_t imgId{ 0 }; imgId < image::FILES_SIZE; ++imgId) {
		load(static_cast<image::Files>(imgId));
	}
	Logger::info("Images loaded : " + std::to_string(cache.size()));
}
ImageManager::~ImageManager() { ; }


std::shared_ptr<sf::Texture> ImageManager::load(const image::Files imgId) {

	// if imgId > or < throwerror
	for (CachedTexture& data : cache)
		if (data.id == imgId)
			//Logger::info("Image " + std::string(image::files[imgId]) + " already loaded");
			return data.texture;

	std::shared_ptr texture = std::make_shared<sf::Texture>();
	std::string filePath = std::string(image::files[imgId]);
	Logger::info((texture->loadFromFile(filePath) ? 
		"Loaded image " : "Failed to load image ") + filePath);

	//texture->setRepeated(false);
	//texture->setSmooth(true);
	cache.emplace_back(CachedTexture{imgId, texture});
	return texture;
}

std::shared_ptr<sf::Texture> ImageManager::get(const image::Files imgId) const {
	// return cache[imgId];
	for (const CachedTexture& data : cache)
		if (data.id == imgId)
			return data.texture;

	Logger::warn("Could not find image " + std::to_string(imgId) + " in image cache");
	// load();
	return nullptr;
}