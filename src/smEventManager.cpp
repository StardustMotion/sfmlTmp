#include "smEventManager.hpp"
#include <SFML/Window/Event.hpp>
#include "smLogger.hpp"

EventManager::EventManager(sf::RenderWindow& window) :
    window(window) {
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
                Logger::log("pressed key scan " + event.key.scancode);
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