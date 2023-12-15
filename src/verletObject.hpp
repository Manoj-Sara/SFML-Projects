#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "utils/math.hpp"

struct VerletObject
{
    sf::Vector2f position;
    sf::Vector2f position_last;
    sf::Vector2f acceleration;
    float        radius        = 10.0f;
    sf::Color    color         = sf::Color::White;
    int level;
    bool merging = false;

    VerletObject() = default;
    VerletObject(sf::Vector2f position_, float radius_, int level_, sf::Color color_)
        : position{position_}
        , position_last{position_}
        , acceleration{0.0f, 0.0f}
        , radius{radius_}
        , level{level_}
        , color{color_}
    {}

    void update(float dt)
    {
        // Compute how much we moved
        sf::Vector2f displacement = position - position_last;

        if (displacement.y < -0.05f) {
            displacement.y = -0.05f;
        }
        if (displacement.x > 0.5f) {
            displacement.x = 0.5f;
        }
        if (displacement.x < -0.5f) {
            displacement.x = -0.5f;
        }
        // Update position
        position_last = position;
        position      = position + displacement + acceleration * (dt * dt);
        // Reset acceleration
        acceleration  = {};
    }

    void accelerate(sf::Vector2f a)
    {
        acceleration += a;
        // if (acceleration.x > max_acceleration.x) {
        //     acceleration.x = max_acceleration.x;
        // }
        // if (acceleration.y > max_acceleration.y) {
        //     acceleration.y = max_acceleration.y;
        // }
    }

    void setVelocity(sf::Vector2f v, float dt)
    {
        position_last = position - (v * dt);
    }

    void addVelocity(sf::Vector2f v, float dt)
    {
        position_last -= v * dt;
    }

    [[nodiscard]]
    sf::Vector2f getVelocity(float dt) const
    {
        return (position - position_last) / dt;
    }
};