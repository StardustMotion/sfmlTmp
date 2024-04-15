#include "smWindow.hpp"
#include "smLogger.hpp"

Window::Window() { ; }
Window::~Window() {
	delete window;
}

sf::RenderWindow* Window::getWindow() {
	return window;
}

void Window::init(const std::string& title) {
	Logger::debug("Init window...");
	if (window)
		delete window;
	window = nullptr;

	// camera/view

	// ANDROID checks?

	window = new sf::RenderWindow(sf::VideoMode(960, 720), title);
	window->setFramerateLimit(48);
	//window->setIcon
}

bool Window::isRunning() {
	return window->isOpen();
}