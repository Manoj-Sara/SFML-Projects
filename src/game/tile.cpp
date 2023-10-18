#include "tile.h"

Tile::Tile(sf::Vector2i newIndex, sf::Texture* newTexture, sf::Vector2f newDimensions, sf::Vector2f newLocalPosition, int newTextureNumber) {
    index = newIndex;
    dimensions = newDimensions;
    SetTexture(newTexture);
    // sprite.setPosition(newLocalPosition);
    SetLocalPosition(newLocalPosition);
    textureNumber = newTextureNumber;
}

Tile::Tile(Tile &inputTile) {
    this->index = inputTile.index;
    this->texture = inputTile.texture;
    this->sprite = inputTile.sprite;
    this->dimensions = inputTile.dimensions;
    this->scale = inputTile.scale;
    this->localPosition = inputTile.localPosition;
    this->textureNumber = inputTile.textureNumber;
}

Tile::~Tile() {

}

void Tile::Render(sf::RenderTarget& target) {
    target.draw(sprite);
}

sf::Vector2f Tile::GetPosition() {
    return sprite.getPosition();
}

void Tile::SetPosition(sf::Vector2f newPosition) {
    sprite.setPosition(newPosition);
}

void Tile::SetSpriteDimensions(sf::Vector2f spriteScale) {
    dimensions = spriteScale;
    scale = sf::Vector2f(dimensions.x / sprite.getLocalBounds().width, dimensions.y / sprite.getLocalBounds().height);
    sprite.setScale(scale);
}

void Tile::SetLocalPosition(sf::Vector2f newLocalPosition) {
    localPosition = newLocalPosition;
    SetPosition(localPosition + GetPosition());
}

void Tile::SetTexture(sf::Texture* newTexture) {
    texture = *newTexture;
    sprite.setTexture(texture, true);
    SetSpriteDimensions(dimensions);
}