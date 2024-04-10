#include "smAudioManager.hpp"

int AudioManager::changemus(std::string file) {

    if (file == currStreamPath) 
            return -1;

    stream.stop();

    if (!stream.openFromFile(file)) {
        Logger::error("failed loading music " + file);
        return -1;
    }
    else {
        stream.play();
        stream.setLoop(true);
        //stream.setPitch(1.0f);
        Logger::debug("opening music " + file);
    }
    return 0;


}
int AudioManager::playsound(SoundList sfx) {
    sound.setBuffer(buffers[static_cast<size_t>(sfx)]);
    sound.play();
    return 0;
}

void AudioManager::loadAllSounds() {
    buffers[static_cast<size_t>(SoundList::A_DASH)].loadFromFile(Resources::A_DASH);
    buffers[static_cast<size_t>(SoundList::A_METWAVE)].loadFromFile(Resources::A_METWAVE);
}

AudioManager::AudioManager() {
    buffers = new sf::SoundBuffer[static_cast<size_t>(SoundList::A_SOUNDS_TYPE_SIZE)];

    for (int i = 0; i < static_cast<size_t>(SoundList::A_SOUNDS_TYPE_SIZE); i++)
        buffers[i] = sf::SoundBuffer();

    loadAllSounds();
}
AudioManager::~AudioManager() { 
    delete[] buffers;
}
