#include "smInputManager.hpp"
#include <SFML/Window/Event.hpp>
#include "smLogger.hpp"

InputManager::InputManager(sf::RenderWindow& window):
    window(window),
    vInputs() {
    setupBindings();
}

InputManager::~InputManager() { ; }



/**
* returns true if quitting the game
* @param none
*/
void InputManager::poll() {
    sf::Event event;
       
    // switch any pressed key into a held status
    if (presses.any())
        for (std::size_t i{ 0 }; i < VInput::SIZE; ++i)
            if (presses.test(i)) {
                presses.reset(i);
                vInputs.event(static_cast<VInput::VInputType>(i), true);
            }
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::EventType::KeyPressed) {
            if (event.key.code != sf::Keyboard::Key::Unknown) {
                processInput(event.key.code, true);
            }
        } else if (event.type == sf::Event::EventType::KeyReleased) {
            if (event.key.code != sf::Keyboard::Key::Unknown) {
                processInput(event.key.code, false);
            }
        } else if (event.type == sf::Event::EventType::MouseButtonPressed) {
            processInput(event.mouseButton, true);
        } else if (event.type == sf::Event::EventType::MouseButtonReleased) {
            processInput(event.mouseButton, false);
        }
        
        else if (event.type == sf::Event::LostFocus) {
            Logger::debug("Lost window focus");
            isFocus = false;
        } else if (event.type == sf::Event::GainedFocus) {
            Logger::debug("Gained window focus back");
            isFocus = true;
        } else if (event.type == sf::Event::Closed) {
            window.close();
        };
    }
};

void InputManager::processInput(sf::Keyboard::Key key, bool state) {
    auto it = std::find(keyboardBindings.begin(), keyboardBindings.end(), key);
    if (it != std::end(keyboardBindings)) {
        VInput::VInputType vinput = static_cast<VInput::VInputType>(std::distance(keyboardBindings.begin(), it));
        if (state && !(vInputs.isHeld(vinput)))
            presses.set(vinput);
        vInputs.event(vinput,state);
    }
}

void InputManager::processInput(sf::Event::MouseButtonEvent event, bool state) {
    VInput::VInputType type = (event.button == sf::Mouse::Left) ? VInput::VInputType::A : VInput::VInputType::B;
    if (state && !(vInputs.isHeld(type)))
        presses.set(type);
    vInputs.event(type, { event.x, event.y }, state);
}

void InputManager::setupBindings() {
    for (int i = 0; i < VInput::SIZE; i++) {
        keyboardBindings[i] = VInput::preBindings[i];
        Logger::info("Bound " + std::to_string(keyboardBindings[i]) + " to " + std::string(VInput::descriptions[i]));
    }
}