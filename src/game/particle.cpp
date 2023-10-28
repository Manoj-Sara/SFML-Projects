#include "particle.h"

Particle::Particle(sf::Vector2i newIndex, sf::Texture* newTexture, sf::Vector2f newDimensions, sf::Vector2f newLocalPosition, int newTextureNumber) {
    index = newIndex;
    dimensions = newDimensions;
    SetTexture(newTexture);
    // sprite.setPosition(newLocalPosition);
    SetLocalPosition(newLocalPosition);
    textureNumber = newTextureNumber;
}

Particle::Particle(Particle &inputParticle) {
    this->index = inputParticle.index;
    this->texture = inputParticle.texture;
    this->sprite = inputParticle.sprite;
    this->dimensions = inputParticle.dimensions;
    this->scale = inputParticle.scale;
    this->localPosition = inputParticle.localPosition;
    this->textureNumber = inputParticle.textureNumber;
}

Particle::~Particle() {

}

void Particle::Render(sf::RenderTarget& target) {
    target.draw(sprite);
}

sf::Vector2f Particle::GetPosition() {
    return sprite.getPosition();
}

void Particle::SetPosition(sf::Vector2f newPosition) {
    sprite.setPosition(newPosition);
}

void Particle::SetSpriteDimensions(sf::Vector2f spriteScale) {
    dimensions = spriteScale;
    scale = sf::Vector2f(dimensions.x / sprite.getLocalBounds().width, dimensions.y / sprite.getLocalBounds().height);
    sprite.setScale(scale);
}

void Particle::SetLocalPosition(sf::Vector2f newLocalPosition) {
    localPosition = newLocalPosition;
    SetPosition(localPosition + GetPosition());
}

void Particle::SetTexture(sf::Texture* newTexture) {
    texture = *newTexture;
    sprite.setTexture(texture, true);
    SetSpriteDimensions(dimensions);
}