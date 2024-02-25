#include "smGame.hpp"

Game::Game(sf::RenderWindow& window) :
    window(window),
    eventManager(window) {
}
Game::~Game() { ; }


void Game::showTails(TailsState state) {
    if (state == Game::TailsState::STOP) {
        if (abs(speed) <= 2.0f) {
            speed = 0;
            tails.setTextureRect(sf::IntRect(0, 0, 48, 32));
            tailsAnimation = 0;
        }
        else speed = speed * 0.9f;
    }
    tailsRefresh++;
    if (tailsRefresh > 2 && speed) {
        tailsAnimation = 1 + (tailsAnimation % 8);
        tailsRefresh = 0;
    }
    if ((state== Game::TailsState::RIGHT) && speed < 8.0f) speed += 0.5f;
    else if ((state == Game::TailsState::LEFT) && speed > -8.0f) speed -= 0.5f;

    tails.move(speed, 0.0f);
    if (state != Game::TailsState::STOP) tails.setScale((state== Game::TailsState::RIGHT ? 2.0f : -2.0f), 2.0f);
    tails.setTextureRect(sf::IntRect(48 * tailsAnimation, 0, 48, 32));
}

void Game::run() {
	Logger::log("game starting.");

    sf::Texture texture;

    Logger::debug("loading texture");
    if (!texture.loadFromFile("res/sprite/tails/tails.png"))
        Logger::error("failed loading tails");

    tails.setTexture(texture);
    tails.setScale(2.0f, 2.0f);
    tails.setTextureRect(sf::IntRect(0, 0, 48,32));

    tails.setPosition(50.0f, window.getSize().y - 96.0f);

    sf::Music music;
    if (!music.openFromFile("res/audio/vwv.ogg"))
        Logger::error("failed loading music");

    music.play();

    sf::Font font;
    Logger::debug("loading font");
    if (!font.loadFromFile("res/font/04B_03_.ttf"))
        Logger::error("failed loading fontes");

    sf::Text text("kermesse", font, 75);

    sf::CircleShape rond(100.f);
    rond.setFillColor(sf::Color::Cyan);

    while (window.isOpen()) {

        sf::Vector2f position = text.getPosition();
        position.x = position.x + 2.01f;
        position.y = position.y + 2.01f;

        text.setPosition(position.x, position.y);
        text.setRotation(text.getRotation() + 6.0f);
        text.setScale(text.getScale().x*-1,text.getScale().y*-1);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            showTails(Game::TailsState::RIGHT);
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            showTails(Game::TailsState::LEFT);
        else
            showTails(Game::TailsState::STOP);

        window.clear();
        window.draw(tails);
        window.draw(text);
        window.draw(rond);
        
        // free unused res
        //textureManager.handleExpiredTexturesCache();

        window.display();

        stopGame = eventManager.poll(); // || noStackSpace 

        if (stopGame) {
            window.close();
        }
    }

}