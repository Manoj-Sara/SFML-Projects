#include "gameManager.h"

GameManager::GameManager() {
}

GameManager::~GameManager() {

}

void GameManager::Update() {
    sf::Time dt_time = deltaSrc.restart();
    float dt = dt_time.asSeconds();

    for (int i = 0; i < particles.size(); i++) {
        particles[i].Update(dt);
    }

    for (int i = particles.size()-1; i >= 0; i--) {
        auto curPart = particles[i];
        if (curPart.IsDead()) {
            particles.erase(particles.begin() + i);
        }
    }
    Game::Update();
}

void GameManager::UpdateDisplay() {
    Game::UpdateDisplay();


    for (int i = 0; i < particles.size(); i++) {
        window->draw(particles[i].GetShape());
    }
    // window->draw(grid);

    // for (auto tile : tiles) {
    //    tile.second->Render(*window);
    // }
}

void GameManager::UpdateInput() {
    Game::UpdateInput();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        DrawParticles();
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

int GameManager::rollRandomPositiveInteger(int maxValue_exclusive) {
    return abs(rand()) % maxValue_exclusive;
}

float GameManager::rollRandomFloat01() {
    int32_t firstRes = abs(rand());
    // std::cout << firstRes << std::endl;
    const int32_t someDenominator = 0x7FFF;
    return float(firstRes % someDenominator) / someDenominator ;
}

sf::Vector2i GameManager::GetCurrentParticleIndex() {
    int currentX = static_cast<int>((mousePosition.x));
    int currentY = static_cast<int>((mousePosition.y));
    // std::cout << "X: " << currentX << ",Y: " << currentY << std::endl;
    return sf::Vector2i(currentX, currentY);
}

void GameManager::DrawParticles() {
    particles.reserve(maxParticles);
    // srand(420);

    for (int i = 0; i < maxParticles; i++) {
        // Determine random direction
        const int maxSpeed = 500;
        float randomSpeed = rollRandomPositiveInteger(maxSpeed + 1);
        float randomAngleInDegrees = rollRandomPositiveInteger(360);
        float randomAngleInRadius = randomAngleInDegrees * PI / 180.f;
        auto randomDirection = sf::Vector2f(
            cos(randomAngleInRadius),
            sin(randomAngleInRadius)
        );
        // Determine random size
        const int maxRandomSize = 32;
        float randomSize = rollRandomPositiveInteger(maxRandomSize+1);
        auto randVelocity = randomDirection * randomSpeed;
        // Roll a random lifetime
        const int maxLifetime = 2;
        float randomLifetime = rollRandomFloat01() * maxLifetime;
        // std::cout << randomLifetime << std::endl;
        // Create + add particle
        auto newParticle = Particle(randomSize, mousePosition, randVelocity, randomLifetime);
        particles.push_back(newParticle);
    }
    // src = source
    // dst = destination
}