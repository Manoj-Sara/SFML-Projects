#include "gameManager.h"
#include "game/state.h"
#include "game/stateIdentifiers.h"
#include "states/titleState.h"
#include "states/menuState.h"
#include "states/gameState.h"
#include "states/pauseState.h"

GameManager::GameManager() {
    RegisterStates();
    stateStack.PushState(States::Title);
}

GameManager::~GameManager() {

}

void GameManager::Update(sf::Time deltaTime) {
    Game::Update(deltaTime);
}

void GameManager::UpdateEvents() {
    Game::UpdateEvents();
}

void GameManager::UpdateDisplay() {
    Game::UpdateDisplay();
}

void GameManager::RegisterStates() {
    stateStack.RegisterState<TitleState>(States::Title);
    stateStack.RegisterState<MenuState>(States::Menu);
    stateStack.RegisterState<GameState>(States::Game);
    stateStack.RegisterState<PauseState>(States::Pause);
}