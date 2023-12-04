#include "application.h"
#include "game/state.h"
#include "game/stateIdentifiers.h"
#include "states/titleState.h"
#include "states/menuState.h"
#include "states/gameState.h"
#include "states/pauseState.h"

Application::Application() {
    RegisterStates();
    stateStack.PushState(States::Title);
    std::cout << "finished constructing application" << std::endl;
}

Application::~Application() {

}

void Application::Update(sf::Time deltaTime) {
    Game::Update(deltaTime);
}

void Application::UpdateEvents() {
    Game::UpdateEvents();
}

void Application::UpdateDisplay() {
    Game::UpdateDisplay();
}

void Application::RegisterStates() {
    stateStack.RegisterState<TitleState>(States::Title);
    stateStack.RegisterState<MenuState>(States::Menu);
    stateStack.RegisterState<GameState>(States::Game);
    stateStack.RegisterState<PauseState>(States::Pause);
}

// #include "application.h"
// // #include "game/stateStack.cpp"

// Application::Application() {
//     RegisterStates();
//     LoadAssets();
//     // CreateInstructions();
//     // SetBrushSize(1);
//     stateStack = new StateStack(State::Context(window, font));
//     // stateStack->SetContext(window, font);
//     stateStack->PushState(States::Title);
// }

// Application::~Application() {

// }

// void Application::Update(sf::Time deltaTime) {

// }

// void Application::UpdateDisplay() {

// }

// void Application::RegisterStates() {
//     std::cout << "About to Register States" << std::endl;
//     stateStack->RegisterState<TitleState>(States::Title);
//     stateStack->RegisterState<MenuState>(States::Menu);
//     stateStack->RegisterState<GameState>(States::Game1P);
//     // stateStack->RegisterState<GameState>(States::Game2P);
//     stateStack->RegisterState<PauseState>(States::Pause);
//     std::cout << "Finished regging states" << std::endl;
// }
