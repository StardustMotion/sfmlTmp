#pragma once
#include <SFML/Graphics/RenderWindow.hpp>


class Window
{
public:
	Window();
	~Window();
	std::unique_ptr<sf::RenderWindow> renderWindow;
	void init(const std::string& title, uint16_t x = 960, uint16_t y = 720);
};

