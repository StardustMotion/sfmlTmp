#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Sleep.hpp>
#include "smLogger.hpp"
#include "smResources.hpp"
#include "smSoundList.hpp"

class AudioManager
{
private:
	bool		isEnabled;

	std::string musicFile;
	sf::Music	music;

public:
	bool playMusic(std::string const& filePath);
	//bool playSound(std::string& filePath);
	AudioManager();
	~AudioManager();

//private:
//	std::string currStreamPath;
//	sf::Music stream;
//	sf::SoundBuffer* buffers;
//	sf::Sound sound;
//public:
//	int changemus(std::string file);
//	int playsound(SoundList sfx);
//	void loadAllSounds();
};

