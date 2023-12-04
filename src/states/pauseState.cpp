#include "pauseState.h"

PauseState::PauseState(StateStack& stack, Context context) : State::State(stack, context) {

}

PauseState::~PauseState() {

}

bool PauseState::Update(sf::Time deltaTime) {
    return true;
}

bool PauseState::UpdateEvents(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Escape) {
        RequestStackClear();
        RequestStackPush(States::Menu);
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