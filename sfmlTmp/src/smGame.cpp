#include "smGame.hpp"
#include <SFML/Window/Event.hpp>
#include "smVInput.hpp"

Game::Game(sf::RenderWindow& window)
	: window(window)
	, audioManager()
	, textureManager()
	, inputManager{ window } {

	// add a hook for game elements to reach those
	ResourceHandler::audioManager = &audioManager;
	ResourceHandler::textureManager = &textureManager;
	VInputHandler::vInputs = &inputManager.vInputs;

	canvas.create(window.getSize().x, window.getSize().y);

	// init view to center=(0,0)
	canvas.setView({ sf::Vector2f(0,0), { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)} });


	run();
}
Game::~Game() { ; }

// single threaded for now
void Game::run() {
	SonicScene scene;
	double fps = 30.0;
	double deltaT = 1.0 / fps;
	Logger::info("\n===================\nStarting up (" + tos(fps) + " FPS)...\n================== = ");
	sf::Clock clock;
	clock.restart();

	uint64_t frameCount{};

	while (window.isOpen()) {
		inputManager.poll(); // gameloop tic/sleep() + input check
		frameCount++;
		
		this->update(deltaT, scene); // game logic
		this->render(scene);

	}
	float finalTime = clock.getElapsedTime().asSeconds();
	Logger::info("\n===================\nGame end\n===================\nTime elapsed : " 
		+ tos(finalTime) +
		"\nFrames : " + tos(frameCount) + " (" + tos(frameCount/ finalTime) + ")");
}

void Game::update(double deltaT, SonicScene& scene) {
	scene.onUpdate(deltaT, canvas.getView());
}

void Game::render(SonicScene& scene) {
	window.clear();
	canvas.clear();
	scene.onDraw(canvas); // lend blank canvas to the scene to fill on
	canvas.display();

	// transfer canvas to final window
	sf::Sprite frame{ canvas.getTexture() };

	// <post-screen processing/shading todo here>

	window.draw(frame);
	window.display();
}
