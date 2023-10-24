#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <string.h>

class GameObject {
    public:
        sf::Vector2i index;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f localPosition;
        sf::Vector2f dimensions;
        sf::Vector2f scale;
        int textureNumber;

        GameObject(sf::Vector2i, sf::Texture*, sf::Vector2f, sf::Vector2f, int);
        GameObject(GameObject&);
        ~GameObject();

        void Render(sf::RenderTarget&);

        sf::Vector2f GetPosition();
        void SetPosition(sf::Vector2f);
        void SetLocalPosition(sf::Vector2f);
        void SetSpriteDimensions(sf::Vector2f);
        void SetTexture(sf::Texture*);
};

#endif