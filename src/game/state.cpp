#include "state.h"
#include "stateStack.h"

State::State(StateStack& stack, Context context) : stack(&stack), context(context) {
    font.loadFromFile("../../assets/fonts/Helvetica.ttf");
}

State::~State() {

}

State::Context State::GetContext() const {
    return context;
}

void State::RequestStackPush(States::ID stateID) {
    stack->PushState(stateID);
}

void State::RequestStackPop() {
    stack->PopState();
}

void State::RequestStackClear() {
    stack->ClearStates();
}

void State::CenterOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void State::CenterOrigin(sf::Shape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void State::SetPlayerCount(int newPlayerCount) {
    stack->SetPlayerCount(newPlayerCount);
}