#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <string.h>

class Particle {
    public:
        // sf::Vector2i index;
        // sf::Sprite sprite;
        // sf::Texture texture;
        // sf::Vector2f localPosition;
        // sf::Vector2f dimensions;
        // sf::Vector2f scale;
        // int textureNumber;

        sf::Vector2f pixelPos;
        sf::Vector2f pixelVelocity;
        float pixelRadius;
        float timeLeftToLive;
        sf::Color color;

        // Particle(sf::Vector2i, sf::Texture*, sf::Vector2f, sf::Vector2f, int);
        // Particle(Particle&);
        // ~Particle();

        // void Render(sf::RenderTarget&);

        // sf::Vector2f GetPosition();
        // void SetPosition(sf::Vector2f);
        // void SetLocalPosition(sf::Vector2f);
        // void SetSpriteDimensions(sf::Vector2f);
        // void SetTexture(sf::Texture*);
        Particle();
        Particle(float, sf::Vector2f, sf::Vector2f, float);

        sf::CircleShape GetShape();
        void Update(float);
        bool IsDead();
};

#endif