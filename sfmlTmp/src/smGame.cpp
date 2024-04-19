#include "smGame.hpp"
#include <SFML/Window/Event.hpp>
#include "smInputVirtual.hpp"

Game::Game(Window& window) :
	window(window),
	audio(),
	inputManager(window) {

	run();
}
Game::~Game() { ; }


void Game::run() {
	Logger::info("\n===================\nStarting up...\n===================");
	inputManager.setupBindings();
	InputVirtual& inputs = inputManager.inputs;
	while (window.isRunning()) {

		inputManager.poll(); // game loop tic
		if (inputs.check(InputVirtual::B)) {
			audio.sound(audio::SFX::DASH);
		}
		else if (inputs.check(InputVirtual::C)) {
			audio.sound(audio::SFX::MET);
		}
		else if (inputs.check(InputVirtual::START)) {
			audio.music(audio::BGM::MAIN);
		}
		else if (inputs.check(InputVirtual::A)) {
			audio.noMusic();
		}
	}
}


//
//Game::Game(Window& window) :
//    window(window),
//    audioManager() {
//}
//Game::~Game() { ; }
//
//
//
//void Game::run() {
//
//    sf::Texture laText = *textureManager.loadFromFile(Resources::S_TAILS);
//    sf::Sprite tails(laText);
//
//
//    tails.setScale(2.0f, 2.0f);
//    tails.setTextureRect(sf::IntRect(0, 0, 48, 32));
//    tails.setPosition(50.0f, window.getSize().y - 96.0f);
//
//    audio.changemus(Resources::A_BGM_MAIN);
//
//
//    sf::Font font;
//    Logger::debug("loading font");
//    if (!font.loadFromFile("res/font/04B_03_.ttf"))
//        Logger::error("failed loading fontes");
//
//    sf::Text text("kermesse", font, 75);
//
//    while (window.isOpen()) {
//        onUpdate(text, tails);
//        stopGame = eventManager.poll(); // || noStackSpace 
//        if (stopGame) {
//            window.close();
//        }
//    }
//
//}
//
//void Game::onUpdate(sf::Text& text, sf::Sprite& tails) {
//
//    sf::Vector2f position = text.getPosition();
//    position.x = position.x + 2.01f;
//    position.y = position.y + 2.01f;
//
//    text.setPosition(position.x, position.y);
//    text.setRotation(text.getRotation() + 6.0f);
//    text.setScale(text.getScale().x * -1, text.getScale().y * -1);
//
//
//    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//        showTails(tails, Game::TailsState::RIGHT);
//    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//        showTails(tails, Game::TailsState::LEFT);
//    else
//        showTails(tails, Game::TailsState::STOP);
//
//    window.clear();
//    //window.draw(textureManager.getBG());
//    window.draw(tails);
//    window.draw(text);
//
//    // free unused res
//    //textureManager.handleExpiredTexturesCache();
//
//    window.display();
//
//}