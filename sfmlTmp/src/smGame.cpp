#include "smGame.hpp"
#include <SFML/Window/Event.hpp>
#include "smVirtualInput.hpp"

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
	double fps = 30.0;
	double deltaT = 1.0 / fps;
	Logger::info("\n===================\nStarting up (" + tos(fps) + " FPS)...\n================== = ");
	sf::Clock clock;
	clock.restart();

	uint64_t frameCount{};

	while (renderWindow.isOpen()) {
		inputManager.poll(); // gameloop tic/sleep() + input check
		frameCount++;
		this->update(deltaT); // game logic
		this->render();

	}
	float finalTime = clock.getElapsedTime().asSeconds();
	Logger::info("\n===================\nGame end\n===================\nTime elapsed : " 
		+ tos(finalTime) +
		"\nFrames : " + tos(frameCount) + " (" + tos(frameCount/ finalTime) + ")");
}

void Game::update(double deltaT) {
	scene.onUpdate(deltaT);
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
