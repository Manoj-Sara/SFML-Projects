#include "gameObject.h"

GameObject::GameObject(sf::Vector2i newIndex, sf::Texture* newTexture, sf::Vector2f newDimensions, sf::Vector2f newLocalPosition, int newTextureNumber) {
    index = newIndex;
    dimensions = newDimensions;
    SetTexture(newTexture);
    // sprite.setPosition(newLocalPosition);
    SetLocalPosition(newLocalPosition);
    textureNumber = newTextureNumber;
}

GameObject::GameObject(GameObject &inputGameObject) {
    this->index = inputGameObject.index;
    this->texture = inputGameObject.texture;
    this->sprite = inputGameObject.sprite;
    this->dimensions = inputGameObject.dimensions;
    this->scale = inputGameObject.scale;
    this->localPosition = inputGameObject.localPosition;
    this->textureNumber = inputGameObject.textureNumber;
}

GameObject::~GameObject() {

}

void GameObject::Render(sf::RenderTarget& target) {
    target.draw(sprite);
}

sf::Vector2f GameObject::GetPosition() {
    return sprite.getPosition();
}

void GameObject::SetPosition(sf::Vector2f newPosition) {
    sprite.setPosition(newPosition);
}

void GameObject::SetSpriteDimensions(sf::Vector2f spriteScale) {
    dimensions = spriteScale;
    scale = sf::Vector2f(dimensions.x / sprite.getLocalBounds().width, dimensions.y / sprite.getLocalBounds().height);
    sprite.setScale(scale);
}

void GameObject::SetLocalPosition(sf::Vector2f newLocalPosition) {
    localPosition = newLocalPosition;
    SetPosition(localPosition + GetPosition());
}

void GameObject::SetTexture(sf::Texture* newTexture) {
    texture = *newTexture;
    sprite.setTexture(texture, true);
    SetSpriteDimensions(dimensions);
}