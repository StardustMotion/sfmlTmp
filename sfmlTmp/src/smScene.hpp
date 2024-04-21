#pragma once
#include <SFML/Graphics.hpp>
#include "smImageManager.hpp"
#include "smInputVirtual.hpp"
#include "smAudioManager.hpp"

class Scene
{
	sf::RenderWindow& window;
	const ImageManager& img;
	const InputVirtual& inputs;
	AudioManager& audio;

	sf::Sprite bg;
	bool state{ 0 };
	sf::View view;

public:
	Scene(sf::RenderWindow& window, const ImageManager& img, const InputVirtual& inputs, AudioManager& audio);
	~Scene();
	void onDraw(sf::RenderTexture& canvas);
	void onUpdate();
};

