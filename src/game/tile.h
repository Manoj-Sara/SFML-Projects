#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <string.h>

class Tile {
    public:
        sf::Vector2i index;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f localPosition;
        sf::Vector2f dimensions;
        sf::Vector2f scale;
        int textureNumber;

        Tile(sf::Vector2i, sf::Texture*, sf::Vector2f, sf::Vector2f, int);
        Tile(Tile&);
        ~Tile();

        void Render(sf::RenderTarget&);

        sf::Vector2f GetPosition();
        void SetPosition(sf::Vector2f);
        void SetLocalPosition(sf::Vector2f);
        void SetSpriteDimensions(sf::Vector2f);
        void SetTexture(sf::Texture*);
};

#endif