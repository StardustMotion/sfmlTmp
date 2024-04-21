#include "smAudioManager.hpp"
#include <string>
#include <string_view>

AudioManager::AudioManager():
	isEnabled(true) {
	for (std::size_t i{ 0 }; i < static_cast<std::size_t>(audio::SFX::SFX_SIZE); ++i) {
		buffers[i] = sf::SoundBuffer(); // new
		std::string filePath = std::string(audio::root) + std::string(audio::sfx[i]);
		Logger::info("Loading sound..." + filePath);
		buffers[i].loadFromFile(filePath);
	}
}
AudioManager::~AudioManager() { ; } // delete[] buffers

void AudioManager::music(audio::BGM const bgm) {
	auto filePath = std::string(audio::root) + std::string(audio::bgm[static_cast<size_t>(bgm)]);
	if (!isEnabled || (filePath == musicFile))
		return;
	stream.stop();
	Logger::info("Playing BGM " + filePath);
	stream.openFromFile(filePath);
	stream.play();
	stream.setLoop(true);
	stream.setPitch(1.0f);
}
void AudioManager::noMusic() {
	if (!isEnabled) 
		return;
	Logger::info("Stopping BGM");
	stream.stop();
}
void AudioManager::sound(audio::SFX const sfx) {
	if (!isEnabled) 
		return;
	sfSound.setBuffer(buffers[static_cast<std::size_t>(sfx)]);
	sfSound.play();
}