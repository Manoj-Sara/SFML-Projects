#include "particle.h"

// Default Constructor, implemented via the Delegate Constructor feature (C++14)
Particle::Particle() : Particle(32, sf::Vector2f(0,0), sf::Vector2f(0,0), 1) {
    color = sf::Color(rand()%256, rand()%256, rand()%256);
}

// Boilerplate "core" constructor, takes all possible relevant fields
Particle::Particle(float pixelRadius, sf::Vector2f initPos, sf::Vector2f initVelocity, float lifetime)
    : pixelVelocity(initVelocity), pixelRadius(pixelRadius), timeLeftToLive(lifetime)
{
    color = sf::Color(rand()%256, rand()%256, rand()%256);
    pixelPos = sf::Vector2f(initPos.x - pixelRadius, initPos.y - pixelRadius);
}

sf::CircleShape Particle::GetShape() {
    auto shape = sf::CircleShape(pixelRadius);
    shape.setPosition(pixelPos);
    shape.setFillColor(color);
    return shape;
}

void Particle::Update(float dt) {
    pixelPos += pixelVelocity * dt;
    timeLeftToLive -= dt;
}

bool Particle::IsDead() {
    return timeLeftToLive <= 0;
}