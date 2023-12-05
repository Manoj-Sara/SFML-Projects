#include "game.h"

Game::Game() : window(sf::VideoMode(700, 512), "Game of Pong", sf::Style::Close),
stateStack(State::Context(window)) {
    window.setKeyRepeatEnabled(false);
    LoadAssets();
    stateStack.SetFont(font);
}

Game::~Game() {

}

void Game::Update(sf::Time deltaTime) {
    stateStack.Update(deltaTime);
}

void Game::UpdateDisplay() {
    window.clear();
    stateStack.Draw();
    window.setView(window.getDefaultView());
    window.display();
}

void Game::UpdateEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        stateStack.HandleEvent(event);

        if (event.type == sf::Event::Closed) {
            std::cout << "Closed window" << std::endl;
            window.close();
        }
    }
}

void Game::CreateWindow() {

    windowHeight = static_cast<float>(window.getSize().y);
    windowWidth = static_cast<float>(window.getSize().x);
}

void Game::RegisterStates() {

}

void Game::Play() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        UpdateEvents();
        Update(deltaTime);
        if (stateStack.IsEmpty()) {
            window.close();
        }
        UpdateDisplay();
    }
}

void Game::LoadAssets() {
    #if _WIN32
        assetPath = "../../../assets/textures/";
    #elif __APPLE__
        assetPath = "../../assets/textures/";
    #endif

    font.loadFromFile(assetPath + "../fonts/Helvetica.ttf");
}