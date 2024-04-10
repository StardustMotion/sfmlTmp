#include "smGame.hpp"

Game::Game(sf::RenderWindow& window) :
    window(window),
    eventManager(window, audio) {
}
Game::~Game() { ; }


void Game::showTails(sf::Sprite& tails, TailsState state) {
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
    if ((state == Game::TailsState::RIGHT) && speed < 8.0f) speed += 0.5f;
    else if ((state == Game::TailsState::LEFT) && speed > -8.0f) speed -= 0.5f;

    tails.move(speed, 0.0f);
    if (state != Game::TailsState::STOP) tails.setScale((state == Game::TailsState::RIGHT ? 2.0f : -2.0f), 2.0f);
    tails.setTextureRect(sf::IntRect(48 * tailsAnimation, 0, 48, 32));
}

void Game::run() {

    sf::Texture laText = *textureManager.loadFromFile(Resources::S_TAILS);
    sf::Sprite tails(laText);


    tails.setScale(2.0f, 2.0f);
    tails.setTextureRect(sf::IntRect(0, 0, 48, 32));
    tails.setPosition(50.0f, window.getSize().y - 96.0f);

    audio.changemus(Resources::A_BGM_MAIN);


    sf::Font font;
    Logger::debug("loading font");
    if (!font.loadFromFile("res/font/04B_03_.ttf"))
        Logger::error("failed loading fontes");

    sf::Text text("kermesse", font, 75);

    while (window.isOpen()) {
        onUpdate(text, tails);
        stopGame = eventManager.poll(); // || noStackSpace 
        if (stopGame) {
            window.close();
        }
    }

}

void Game::onUpdate(sf::Text& text, sf::Sprite& tails) {

    sf::Vector2f position = text.getPosition();
    position.x = position.x + 2.01f;
    position.y = position.y + 2.01f;

    text.setPosition(position.x, position.y);
    text.setRotation(text.getRotation() + 6.0f);
    text.setScale(text.getScale().x * -1, text.getScale().y * -1);


    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        showTails(tails, Game::TailsState::RIGHT);
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        showTails(tails, Game::TailsState::LEFT);
    else
        showTails(tails, Game::TailsState::STOP);

    window.clear();
    //window.draw(textureManager.getBG());
    window.draw(tails);
    window.draw(text);

    // free unused res
    //textureManager.handleExpiredTexturesCache();

    window.display();

}