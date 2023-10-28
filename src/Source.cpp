#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <vector>

// https://learn.microsoft.com/en-us/visualstudio/ide/how-to-create-project-templates?view=vs-2022

class Particle {

public:
    sf::Vector2f pixelPos;
    sf::Vector2f pixelVelocity;
    float pixelRadius;
    float timeLeftToLive;

    // Default Constructor, implemented via the Delegate Constructor feature (C++14)
    Particle() : Particle(32, sf::Vector2f(0,0), sf::Vector2f(0,0), 1) {

    }

    // Boilerplate "core" constructor, takes all possible relevant fields
    Particle(float pixelRadius, sf::Vector2f initPos, sf::Vector2f initVelocity, float lifetime)
        : pixelPos(initPos), pixelVelocity(initVelocity), pixelRadius(pixelRadius), timeLeftToLive(lifetime)
    {
    }

    sf::CircleShape getShape() {
        auto shape = sf::CircleShape(pixelRadius);
        shape.setPosition(pixelPos);
        shape.setFillColor(sf::Color::White);
        return shape;
    }

    void update(float dt) {
        pixelPos += pixelVelocity * dt;
        timeLeftToLive -= dt;
    }

    bool isDead() {
        return timeLeftToLive <= 0;
    }

};

int rollRandomPositiveInteger(int maxValue_exclusive) {
    return abs(rand()) % maxValue_exclusive;
}

float rollRandomFloat01() {
    int32_t firstRes = abs(rand());
    std::cout << firstRes << std::endl;
    const int32_t someDenominator = 0x7FFF;
    return float(firstRes % someDenominator) / someDenominator ;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    const int maxParticles = 64;
    const float PI = 3.141592654f;
    std::vector<Particle> particles;
    particles.reserve(maxParticles);
    srand(420);

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
        std::cout << randomLifetime << std::endl;
        // Create + add particle
        auto newParticle = Particle(randomSize, sf::Vector2f(400, 300), randVelocity, randomLifetime);
        particles.push_back(newParticle);
    }
    std::cout << particles.size() << std::endl;
    // src = source
    // dst = destination
    sf::Clock deltaSrc;

    while (window.isOpen())
    {
        // Extract deltatime
        sf::Time dt_time = deltaSrc.restart();
        float dt = dt_time.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the world state
        for (int i = 0; i < particles.size(); i++) {
            particles[i].update(dt);
        }

        // Maybe kill foreach
        for (int i = particles.size()-1; i >= 0; i--) {
            auto curPart = particles[i];
            if (curPart.isDead()) {
                particles.erase(particles.begin() + i);
            }
        }

        // Draw the damn stuff
        window.clear();
        for (int i = 0; i < particles.size(); i++) {
            window.draw(particles[i].getShape());
        }
        window.display();
    }

    return 0;
}