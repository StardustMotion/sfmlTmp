#pragma once
#include <SFML/Graphics/RenderWindow.hpp>


class Window
{
public:
	Window();
	~Window();
	std::unique_ptr<sf::RenderWindow> renderWindow;
	sf::Vector2f win{ 960, 720 }; // size
	void init(const std::string& title);
};

