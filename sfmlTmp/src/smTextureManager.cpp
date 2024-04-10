#include "smTextureManager.hpp"


TextureManager::TextureManager() {

}
TextureManager::~TextureManager() {

}


std::shared_ptr<Texture> TextureManager::loadFromFile(string _path) {

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	if (!texture->loadFromFile(_path))
		Logger::error("couldnt load :( texture " + _path);
	else
		Logger::debug("loaded " + _path);




	return texture;
}

//sf::Sprite& TextureManager::getBG() {
//	return 
//}

void TextureManager::setBG(std::string bg) {

}