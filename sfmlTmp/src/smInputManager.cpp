#include "smInputManager.hpp"
#include <SFML/Window/Event.hpp>
#include "smLogger.hpp"

InputManager::InputManager(sf::RenderWindow& window):
    window(window),
    inputs(),
    keyboard{},
    mouse{} {
    setupBindings();
}

InputManager::~InputManager() { ; }

InputEvent::InputEvent(InputDevice device, uint8_t id, bool state):
    device(device),
    id(id),
    state(state) {
}

/**
* returns true if quitting the game
* @param none
*/
void InputManager::poll() {
    sf::Event event;
    std::uint8_t res{ 0 };
    std::vector<InputEvent> inputEvents; 
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::EventType::KeyPressed) {
            if (event.key.code != sf::Keyboard::Key::Unknown) {
                inputEvents.emplace_back(InputEvent::KEYBOARD, event.key.code, true);
            }
        } else if (event.type == sf::Event::EventType::KeyReleased) {
            if (event.key.code != sf::Keyboard::Key::Unknown) {
                inputEvents.emplace_back(InputEvent::KEYBOARD, event.key.code, false);
            }
        } else if (event.type == sf::Event::EventType::MouseButtonPressed) {
            inputEvents.emplace_back(InputEvent::MOUSE, event.mouseButton.button, true);
        } else if (event.type == sf::Event::EventType::MouseButtonReleased) {
            inputEvents.emplace_back(InputEvent::MOUSE, event.mouseButton.button, false);
        } else if (event.type == sf::Event::LostFocus) {
            Logger::debug("Lost window focus");
            isFocus = false;
        } else if (event.type == sf::Event::GainedFocus) {
            Logger::debug("Gained window focus back");
            isFocus = true;
        } else if (event.type == sf::Event::Closed) {
            window.close();
        };

    }

    for (const auto& [device, id, state] : inputEvents) {
        if (device == InputEvent::KEYBOARD) {
            auto it = std::find(bindings.begin(), bindings.end(), id);
            if (it != std::end(bindings)) {
                std::size_t index = std::distance(bindings.begin(), it);
                inputs.event(static_cast<InputVirtual::Event>(index), state);
                Logger::debug(std::string(state ? "-->" : "<--") + " Key " + 
                    std::to_string(id) + " (" + std::string(InputVirtual::descriptions[index]) + ")");

            }
        } else { // MOUSE
           // ...
        }
    }
};

void InputManager::setupBindings() {
    for (int i = 0; i < static_cast<size_t>(InputVirtual::SIZE); i++) {
        bindings[i] = InputVirtual::preBindings[i];
        Logger::info("Bound " + std::to_string(bindings[i]) + " to " + std::string(InputVirtual::descriptions[i]));
    }
}