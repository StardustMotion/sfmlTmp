#include "smWindow.hpp"
#include "smLogger.hpp"

Window::Window() { ; }
Window::~Window() { ; }


void Window::init(const std::string& title) {

	Logger::debug("Init window...");

	// camera/view

	// ANDROID checks?

	renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(win.x, win.y), title);
	renderWindow->setFramerateLimit(60);
	//window->setIcon
}
