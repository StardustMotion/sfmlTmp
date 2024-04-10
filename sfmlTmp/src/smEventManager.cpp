#include "smEventManager.hpp"
#include <SFML/Window/Event.hpp>
#include "smLogger.hpp"

EventManager::EventManager(sf::RenderWindow& window, AudioManager& audio) :
    window(window),
    audio(audio) {
};

EventManager::~EventManager() { ; }

/**
* quits game if return true
* @param none
*/
bool EventManager::poll() {

    sf::Event event;
    bool exit = false;
    while (window.pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::TextEntered:
            Logger::log("text enter " + event.text.unicode);
            break;

        case sf::Event::Closed:
            Logger::log("closed windower ");
            exit = true;
            break;

        case sf::Event::Resized:
            Logger::log("resized windo");
            break;

        case sf::Event::KeyPressed:
            Logger::log("pressed key " + event.key.code);
            //Logger::log("pressed key scan " + event.key.scancode);
            if (event.key.code == sf::Keyboard::H) {
                audio.playsound(SoundList::A_DASH);
                Logger::debug("hit the key");
            }
            else if (event.key.code == sf::Keyboard::G) {
                audio.playsound(SoundList::A_METWAVE);
                Logger::debug("hit the key wave");

            }

            break;

        case sf::Event::KeyReleased:
            Logger::log("released key " + event.key.code);
            Logger::log("released key scan " + event.key.scancode);
            break;

        case sf::Event::MouseButtonPressed:
            Logger::log("click!! " + event.mouseButton.button);
            break;

            //case sf::Event::Count:
            //    break;

        }
    }

    return exit;
};