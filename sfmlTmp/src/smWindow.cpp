#include "smWindow.hpp"
#include "smLogger.hpp"

Window::Window() { ; }
Window::~Window() { ; }


void Window::init(const std::string& title, uint16_t x, uint16_t y) {
	Logger::debug("Init window...");

	// camera/view

	// ANDROID checks?

	renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(x, y), title);
	renderWindow->setFramerateLimit(60);
	//window->setIcon
}
