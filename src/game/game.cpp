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
    windowPal->display();
    windowText->display();
}

void Game::UpdateDisplay() {
    window->clear();
    windowPal->clear();
    windowText->clear();
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

    while (windowPal->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                windowPal->close();
                break;
            default:
                break;
        }
    }

    while (windowText->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                windowText->close();
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

    videoMode.width = PALETTE_SCREEN_WIDTH;
    videoMode.height = PALETTE_SCREEN_HEIGHT;
    windowPal = new sf::RenderWindow(videoMode, "Palette", sf::Style::Titlebar || sf::Style::Resize);
    windowPal->setFramerateLimit(60);

    windowPalHeight = static_cast<float>(windowPal->getSize().y);
    windowPalWidth = static_cast<float>(windowPal->getSize().x);

    windowPal->setPosition(sf::Vector2i(windowPal->getPosition().x + 350, windowPal->getPosition().y));

    videoMode.width = TEXT_SCREEN_WIDTH;
    videoMode.height = TEXT_SCREEN_HEIGHT;
    windowText = new sf::RenderWindow(videoMode, "Keyboard Controls", sf::Style::Titlebar || sf::Style::Close);
    windowText->setFramerateLimit(60);

    windowTextHeight = static_cast<float>(windowText->getSize().y);
    windowTextWidth = static_cast<float>(windowText->getSize().x);
    windowText->setPosition(sf::Vector2i(windowText->getPosition().x, windowText->getPosition().y + 500));
}

void Game::Play() {
    while (window->isOpen()) {
        Update();
    }
}