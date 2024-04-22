#include "smGame.hpp"
#include <SFML/Window/Event.hpp>
#include "smInputVirtual.hpp"

Game::Game(Window& window) :
	window{ *window.renderWindow },
	canvas{ std::make_unique<sf::RenderTexture>() },
	audio{},
	inputManager{ *window.renderWindow },
	img{},
	scene{ img, inputManager.inputs, audio } {

	sf::Vector2f windowSize{ window.renderWindow->getSize() };
	canvas->create(windowSize.x, windowSize.y);
	// init view to center=(0,0)
	canvas->setView({ sf::Vector2f(0,0), sf::Vector2f(windowSize.x, windowSize.y) });

	run();
}
Game::~Game() { ; }

// single threaded for now
void Game::run() {
	Logger::info("\n===================\nStarting up...\n===================");
	while (window.isOpen()) {
		inputManager.poll(); // gameloop tic + input check
		update(); // game logic
		render();
	}
}

void Game::update() {
	scene.onUpdate();
}

void Game::render() {
	window.clear();
	canvas->clear();
	scene.onDraw(*canvas); // lend blank canvas to the scene to fill on
	canvas->display();

	// transfer canvas to final window
	sf::Sprite frame{ canvas->getTexture() };

	// <post-screen processing/shading todo here>

	window.draw(frame);
	window.display();
}
