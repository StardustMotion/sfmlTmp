#include "smGame.hpp"
#include <SFML/Window/Event.hpp>
#include "smInputVirtual.hpp"

Game::Game(Window& window) :
	window{ window },
	audio{},
	inputManager{ window },
	img{},
	scene{ *window.getWindow(), img, inputManager.inputs, audio },
	canvas{ std::make_unique<sf::RenderTexture>() } {

	canvas->create(window.getWindow()->getSize().x, window.getWindow()->getSize().y);

	run();
}
Game::~Game() { ; }

// single threaded for now
void Game::run() {
	Logger::info("\n===================\nStarting up...\n===================");
	while (window.isRunning()) {
		inputManager.poll(); // gameloop tic + input check
		update(); // game logic
		render();
	}
}

void Game::update() {
	scene.onUpdate();
}

void Game::render() {
	window.getWindow()->clear();
	scene.onDraw(*canvas); // lend blank canvas to the scene to fill on
	canvas->display();

	// transfer canvas to final window
	sf::Sprite frame{ canvas->getTexture() };

	// <post-screen processing/shading todo here>

	window.getWindow()->draw(frame);
	window.getWindow()->display();
}
