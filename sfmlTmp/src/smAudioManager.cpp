#include "smAudioManager.hpp"

AudioManager::AudioManager() {
	isEnabled = true;
	/*buffers = new sf::SoundBuffer[static_cast<size_t>(SoundList::A_SOUNDS_TYPE_SIZE)];
	for (int i = 0; i < static_cast<size_t>(SoundList::A_SOUNDS_TYPE_SIZE); i++)
	        buffers[i] = sf::SoundBuffer();
	

	loadAllSounds();*/
}
AudioManager::~AudioManager() { ; }

bool AudioManager::playMusic(std::string const& filePath) {
	if (!isEnabled || (filePath == musicFile)) 
		return 1;

	music.stop();
	music.openFromFile(filePath);
	music.play();
	music.setLoop(true);
	music.setPitch(1.0f);

	musicFile = filePath;
	return 0;
}

//int AudioManager::playsound(SoundList sfx) {
//    sound.setBuffer(buffers[static_cast<size_t>(sfx)]);
//    sound.play();
//    return 0;
//}
//
//void AudioManager::loadAllSounds() {
//    buffers[static_cast<size_t>(SoundList::A_DASH)].loadFromFile(Resources::A_DASH);
//    buffers[static_cast<size_t>(SoundList::A_METWAVE)].loadFromFile(Resources::A_METWAVE);
//}
//
//AudioManager::AudioManager() {
//    buffers = new sf::SoundBuffer[static_cast<size_t>(SoundList::A_SOUNDS_TYPE_SIZE)];
//
//    for (int i = 0; i < static_cast<size_t>(SoundList::A_SOUNDS_TYPE_SIZE); i++)
//        buffers[i] = sf::SoundBuffer();
//
//    loadAllSounds();
//}
//AudioManager::~AudioManager() { 
//    delete[] buffers;
//}
