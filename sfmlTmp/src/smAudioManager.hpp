#pragma once

#include <string>
#include <string_view>
#include <SFML/Audio.hpp>
#include <SFML/System/Sleep.hpp>
#include "smLogger.hpp"
#include "smAudio.hpp"


class AudioManager
{
	bool isEnabled;
	std::string_view musicFile;
	sf::Music stream;
	sf::Sound sfSound;
	std::array<sf::SoundBuffer, static_cast<std::size_t>(audio::SFX::SFX_SIZE)> buffers;

public:
	AudioManager();
	~AudioManager(); // delete[] buffers
	void music(audio::BGM const bgm);
	void noMusic();
	void sound(audio::SFX const sfx);
};

