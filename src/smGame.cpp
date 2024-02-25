#include "smGame.hpp"


Game::Game(sf::RenderWindow& window) :
    window(window),
    eventManager(window) {
}
Game::~Game() { ; }
void Game::run() {
	Logger::log("game starting.");

    sf::Texture texture;

    Logger::debug("loading texture");
    if (!texture.loadFromFile("res/sprite/rock.png"))
    {
        Logger::error("failed loading rock");
    }

    Logger::debug("loading sprite");
    sf::Sprite sprite(texture);

    sf::Music music;
    if (!music.openFromFile("res/audio/vwv.ogg")) {
        Logger::error("failed loading music");
    }

    music.play();

    sf::Font font;
    Logger::debug("loading font");
    if (!font.loadFromFile("res/font/04B_03_.ttf")) {
        Logger::error("failed loading fontes");
    }
    sf::Text text("kermesse", font, 75);


    while (window.isOpen()) {

        // quits game if returns true
        if (eventManager.poll())
            window.close();


        window.clear();

        window.draw(sprite);
        window.draw(text);

        window.display();

    }

}