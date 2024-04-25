#include "smGame.hpp"
#include <SFML/Window/Event.hpp>
#include "smInputVirtual.hpp"

Game::Game(Window& window):
	win(window.win),
	renderWindow{ *window.renderWindow },
	canvas{ std::make_unique<sf::RenderTexture>() },
	audio{},
	inputManager{ *window.renderWindow },
	img{},
	scene{ win, img, inputManager.inputs, audio } {

	sf::Vector2f windowSize{ window.renderWindow->getSize() };
	canvas->create(windowSize.x, windowSize.y);

	// init view to center=(0,0)
	canvas->setView({ sf::Vector2f(0,0), std::move(windowSize) });

	run();
}
Game::~Game() { ; }

// single threaded for now
void Game::run() {
	Logger::info("\n===================\nStarting up...\n===================");
	while (renderWindow.isOpen()) {
		inputManager.poll(); // gameloop tic + input check
		update(); // game logic
		render();
	}
}

void Game::update() {
	scene.onUpdate();
}

void Game::render() {
	renderWindow.clear();
	canvas->clear();
	scene.onDraw(*canvas); // lend blank canvas to the scene to fill on
	canvas->display();

	// transfer canvas to final window
	sf::Sprite frame{ canvas->getTexture() };

	// <post-screen processing/shading todo here>

	renderWindow.draw(frame);
	renderWindow.display();
}
