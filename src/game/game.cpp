#include "game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);

Game::Game() : window(sf::VideoMode(512, 512), "Game of Pong", sf::Style::Close),
stateStack(State::Context(window)) {
    // Game::CreateWindow();
    window.setKeyRepeatEnabled(false);
    LoadAssets();
    stateStack.SetFont(font);
}

Game::~Game() {
    // delete stateStack;
    // delete window;
}

// void Game::Update() {
//     UpdateMouse();
//     UpdateEvents();
//     UpdateInput();
//     UpdateDisplay();
//     window->display();
// }

void Game::Update(sf::Time deltaTime) {
    // std::cout << "Enter game Update" << std::endl;
    stateStack.Update(deltaTime);
    // UpdateDisplay();

    // if (stateStack->IsEmpty()) {
    //     std::cout << "State Stack is empty so closing" << std::endl;
    //     window->close();
    // }
}

void Game::UpdateDisplay() {
    window.clear();
    //std::cout << "prob  problem" << std::endl;
    stateStack.Draw();
    //std::cout << "or not" << std::endl;
    window.setView(window.getDefaultView());
    window.display();
}

// void Game::UpdateInput() {

// }

// void Game::UpdateMouse() {
//     mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
// }

// void Game::UpdateEvents() {
//     while (window->pollEvent(event)) {
//         switch (event.type) {
//             case sf::Event::Closed:
//                 window->close();
//                 break;
//             default:
//                 break;
//         }
//     }
// }

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
    //videoMode.width = SCREEN_WIDTH;
    //videoMode.height = SCREEN_HEIGHT;
    //window = new sf::RenderWindow(videoMode, "Game of Pong");
    // window->setFramerateLimit(60);

    windowHeight = static_cast<float>(window.getSize().y);
    windowWidth = static_cast<float>(window.getSize().x);
}

void Game::RegisterStates() {

}

// void Game::Play() {
//     UpdateEvents();

//     while (window->isOpen()) {
//         sf::Time deltaTime = clock.restart();
//         Update(deltaTime);
//     }
// }
void Game::Play() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            //std::cout << "Run Update" << std::endl;
            UpdateEvents();
            Update(timePerFrame);
            //std::cout << "Ran updates" << std::endl;
            if (stateStack.IsEmpty()) {
                std::cout << "StateStack is Empty" << std::endl;
                window.close();
            }
        }
        //std::cout << "about to ran Update display" << std::endl;
        UpdateDisplay();
        //std::cout << "Ran update display" << std::endl;
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