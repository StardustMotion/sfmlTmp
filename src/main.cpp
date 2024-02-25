#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "smLogger.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "gaming");

    sf::Texture texture;

    Logger::debug("loading texture");
    if (!texture.loadFromFile("res/sprite/rock.png"))
    {
        Logger::error("failed loading rock");
        return EXIT_FAILURE;
    }

    Logger::debug("loading sprite");
    sf::Sprite sprite(texture);

    sf::Music music;
    if (!music.openFromFile("res/audio/vwv.ogg")) {
        Logger::error("failed loading music");
        return EXIT_FAILURE;
    }

    music.play();

    sf::Font font;
    Logger::debug("loading font");
    if (!font.loadFromFile("res/font/04B_03_.TTF")) {
        Logger::error("failed loading fontes");
        return EXIT_FAILURE;
    }
    sf::Text text("kermesse", font, 50);


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        window.draw(sprite);
        window.draw(text);

        window.display();

    }

    return EXIT_SUCCESS;
}