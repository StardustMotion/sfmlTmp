#include "smEventManager.hpp"
#include <SFML/Window/Event.hpp>
#include "smLogger.hpp"

EventManager::EventManager(sf::RenderWindow& window) :
    window(window),
    exit(false) {

};

EventManager::~EventManager() { ; }

/** 
* quits game if return true
* @param none
*/
bool EventManager::poll() {
	sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Logger::log("quitting game!!");
            exit = true;
        }
    }
    return exit;
};