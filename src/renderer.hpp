#pragma once
#include "solver.hpp"


class Renderer
{
public:
    explicit
    Renderer(sf::RenderTarget& target)
        : m_target{target}
    {

    }

    void render(const Solver& solver) const
    {
        // Render constraint
        // sf::RectangleShape constraintBottom{sf::Vector2f(constraint.z, 5.0f)};
        // sf::RectangleShape constraintLeft{sf::Vector2f(5.0f, constraint.z)};
        // sf::RectangleShape constraintRight{sf::Vector2f(5.0f, constraint.z)};
        // constraintBottom.setPosition(constraint.x, constraint.y);
        // constraintLeft.setPosition(constraint.x - 5, constraint.y);
        // constraintRight.setPosition(constraint.x + 5, constraint.y);
        
        // constraint_background.setOrigin(constraint.z, constraint.z);
        // constraint_background.setFillColor(sf::Color::Black);
        // constraint_background.setPosition(constraint.x, constraint.y);
        // constraint_background.setPointCount(128);
        m_target.draw(*solver.constraintBottom);
        m_target.draw(*solver.constraintLeft);
        m_target.draw(*solver.constraintRight);

        // Render objects
        sf::CircleShape circle{1.0f};
        circle.setPointCount(32);
        circle.setOrigin(1.0f, 1.0f);
        const auto& objects = solver.getObjects();
        for (const auto& obj : objects) {
            circle.setPosition(obj.position);
            circle.setScale(obj.radius, obj.radius);
            circle.setFillColor(obj.color);
            m_target.draw(circle);
        }
    }

private:
    sf::RenderTarget& m_target;
};
