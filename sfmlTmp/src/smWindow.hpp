#pragma once
#include <SFML/Graphics/RenderWindow.hpp>


class Window
{
public:
	Window();
	~Window();
	sf::RenderWindow* getWindow();
	void init(const std::string& title);
	bool isRunning();
private:
	sf::RenderWindow* window{ nullptr };
};

