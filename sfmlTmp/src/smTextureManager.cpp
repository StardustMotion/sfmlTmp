
#include "smLogger.hpp"
#include "smTextureManager.hpp"

std::map<std::string, Animation> TextureManager::animations{};
std::map<std::string, std::shared_ptr<sf::Texture>> TextureManager::cache{};

// todo "paths db" file?

// maybe later defer texture loading (i.e on new scene load)
TextureManager::TextureManager() {
	for (const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator(".\\res\\texture")) {
		if (file.path().extension() == ".png") {			
			getTexture(static_cast<std::filesystem::path>(file.path()).replace_extension().string());
		}
		else if (file.path().extension() == ".anim" ) {
			parseAnimation(file.path());
		}
	}
	Logger::info(std::to_string(cache.size()) + " Images loaded, " + std::to_string(animations.size()) + " animations loaded");
}
TextureManager::~TextureManager() { ; }


void TextureManager::parseAnimation(std::filesystem::path path) {
	std::ifstream file{ path.string() };
	Logger::info("Parsing animation " + path.string() + "...");
	do {
		// Anim name must be same as .png file of the same folder
		std::string name;
		file >> name;

		// Size	
		sf::Vector2i size;
		file >> size.x;
		file >> size.y;

		// Frames
		std::vector<std::vector<AnimationFrame>> animation;
		do {
			std::vector<AnimationFrame> sequence;
			AnimationFrame frame;
			while (file >> frame.t >> frame.crop.x >> frame.crop.y) {
				sequence.push_back(frame);
				if (file.peek() != '\n')
					file.ignore(6, '|');
				else
					break;
			}
			animation.emplace_back(sequence);
			file.get(); // '\n'
		} while (file.peek() != '\n' && !file.eof());
		animations[name] = Animation{ size, animation };

	} while (!file.eof());
	Logger::info("Parsed " + path.string() + " animation successfully");
}

std::shared_ptr<sf::Texture> TextureManager::getTexture(const std::string name) {
	auto iter = cache.find(name);
	if (iter != cache.end()) {
		Logger::info("(Cache) Fetched texture " + name);
		return iter->second;
	}

	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
	if (texture->loadFromFile(name+".png")) {
		Logger::info("Loaded texture " + name);
		cache[name] = texture;
		////texture->setRepeated(false);
		////texture->setSmooth(true);
		return texture;
	}
	Logger::warn("Failed to load texture" + name);
	return nullptr;
}

Animation* TextureManager::getAnim(const std::string name) {
	if (auto anim = animations.find(name); anim != animations.end()) {
		return &(anim->second);
	}
	else {
		Logger::warn("Couldn't get animation " + name);
		return nullptr;
	}
	return nullptr;
}