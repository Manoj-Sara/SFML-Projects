#include "game.h"

Game::Game() {
    Game::CreateWindows();
}

Game::~Game() {
    delete window;
}

void Game::Update() {
    UpdateMouse();
    UpdateEvents();
    UpdateInput();
    UpdateDisplay();
    window->display();
}

void Game::UpdateDisplay() {
    window->clear();
}

void Game::UpdateInput() {

}

void Game::UpdateMouse() {
    mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void Game::UpdateEvents() {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            default:
                break;
        }
    }
}

void Game::CreateWindows() {
    videoMode.width = SCREEN_WIDTH;
    videoMode.height = SCREEN_HEIGHT;
    window = new sf::RenderWindow(videoMode, "Map Editor");
    window->setFramerateLimit(60);

    windowHeight = static_cast<float>(window->getSize().y);
    windowWidth = static_cast<float>(window->getSize().x);
}

void Game::Play() {
    while (window->isOpen()) {
        Update();
    }
}