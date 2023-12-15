#include "gameManager.h"

GameManager::GameManager() {
    LoadAssets();
    CreateWinText();

    solver.setConstraint({static_cast<float>(SCREEN_WIDTH) * 0.5f, static_cast<float>(SCREEN_HEIGHT) * 0.5f}, 450.0f);
    solver.setSubStepsCount(8);
    solver.setSimulationUpdateRate(60);

    loseLine = new sf::RectangleShape(sf::Vector2f(450.0f, 5.0f));
    loseLine->setOrigin(sf::Vector2f(225.0f, 5.0f));
    loseLine->setPosition(sf::Vector2f(static_cast<float>(SCREEN_WIDTH) * 0.5f, static_cast<float>(SCREEN_HEIGHT) * 0.25f));
    loseLine->setFillColor(sf::Color(128,128,128));

    currentBall = rand() % 5 + 1;
}

GameManager::~GameManager() {

}

void GameManager::Update() {
    if (solver.gameState != 2) {
        solver.update();
    }

    Game::Update();
}

void GameManager::UpdateDisplay() {
    Game::UpdateDisplay();

    window->draw(*loseLine);
    window->draw(*solver.constraintBottom);
    window->draw(*solver.constraintLeft);
    window->draw(*solver.constraintRight);

    sf::CircleShape circle{1.0f};
    circle.setPointCount(32);
    circle.setOrigin(1.0f, 1.0f);

    switch (currentBall) {
        case 1:
            circle.setScale(10.0f, 10.0f);
            circle.setFillColor(sf::Color::Blue);
            break;
        case 2:
            circle.setScale(20.0f, 20.0f);
            circle.setFillColor(sf::Color::Red);
            break;
        case 3:
            circle.setScale(30.0f, 30.0f);
            circle.setFillColor(sf::Color::Green);
            break;
        case 4:
            circle.setScale(40.0f, 40.0f);
            circle.setFillColor(sf::Color::Yellow);
            break;
        case 5:
            circle.setScale(50.0f, 50.0f);
            circle.setFillColor(sf::Color::Magenta);
            break;
        default:
            break;
    }

    maxLeft = solver.constraintLeft->getPosition().x + solver.constraintLeft->getSize().x / 2.0f + circle.getScale().x + 0.1f;
    maxRight = solver.constraintRight->getPosition().x - solver.constraintRight->getSize().x / 2.0f - circle.getScale().x - 0.1f;

    newPosition = mousePosition.x;
    if (mousePosition.x < maxLeft) {
        newPosition = maxLeft;
    }
    if (mousePosition.x > maxRight) {
        newPosition = maxRight;
    }

    circle.setPosition(newPosition, spawnHeight);

    if (clock.getElapsedTime().asSeconds() >= object_spawn_delay && solver.gameState != 2) {
        window->draw(circle);
    }

    const auto& objects = solver.getObjects();
    for (const auto& obj : objects) {
        circle.setPosition(obj.position);
        circle.setScale(obj.radius, obj.radius);
        circle.setFillColor(obj.color);
        window->draw(circle);
    }

    if (solver.gameState == 2) {
        window->draw(winText);
    }
}

void GameManager::UpdateInput() {
    Game::UpdateInput();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (mousePosition.x > solver.constraintLeft->getPosition().x + solver.constraintLeft->getSize().x / 2.0f 
        && mousePosition.x < solver.constraintRight->getPosition().x - solver.constraintRight->getSize().x / 2.0f
        && clock.getElapsedTime().asSeconds() >= object_spawn_delay && solver.gameState != 2) {
            clock.restart();
            SpawnBall();
        }
    }
}

void GameManager::UpdateEvents() {
    Game::UpdateEvents();
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

void GameManager::AddAsset(int key, std::string fileName) {
    assets[key] = new sf::Texture();
    assets[key]->loadFromFile(fileName);
}

void GameManager::LoadAssets() {
    #if _WIN32
        assetPath = "../../../assets/textures/";
    #elif __APPLE__
        assetPath = "../../assets/textures/";
    #endif
}

void GameManager::CreateWinText() {
    font.loadFromFile(assetPath + "../fonts/Helvetica.ttf");
    winText.setFillColor(sf::Color::Cyan);
    winText.setFont(font);
    winText.setCharacterSize(200);
    winText.setPosition(0, SCREEN_HEIGHT / 2 - 50.0f);
    winText.setString("YOU WIN!!!");
}

sf::Vector2i GameManager::GetCurrentGameObjectIndex() {
    int currentX = static_cast<int>((mousePosition.x - xMargin.x) / unitDimensions.x);
    int currentY = static_cast<int>((mousePosition.y - yMargin.x) / unitDimensions.y);
    return sf::Vector2i(currentX, currentY);
}

void GameManager::SpawnBall() {
    auto& object = solver.addObject(sf::Vector2f(newPosition, spawnHeight), currentBall);
    currentBall = rand() % 5 + 1;
}