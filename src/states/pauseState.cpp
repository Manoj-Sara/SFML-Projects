#include "pauseState.h"

PauseState::PauseState(StateStack& stack, Context context) : State::State(stack, context) {

}

PauseState::~PauseState() {

}

bool PauseState::Update(sf::Time deltaTime) {
    return false;
}

bool PauseState::UpdateEvents(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return false;
    }

    if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P) {
        RequestStackPop();
        std::cout << "Moving from Pause to Game" << std::endl;
    }

    return false;
}

void PauseState::UpdateDisplay() {
    sf::RenderWindow& window = *GetContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
}