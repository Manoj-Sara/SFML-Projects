#include "gameState.h"

GameState::GameState(StateStack& stack, Context context) : State::State(stack, context) {

}

GameState::~GameState() {

}

bool GameState::Update(sf::Time deltaTime) {
    return true;
}

bool GameState::UpdateEvents(const sf::Event& event) {
    return true;
}

void GameState::UpdateDisplay() {

}