#pragma once
#include <vector>
#include <cmath>
#include <tuple>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "utils/math.hpp"
#include "verletObject.hpp"

class Solver
{
public:
    sf::RectangleShape *constraintBottom;
    sf::RectangleShape *constraintLeft;
    sf::RectangleShape *constraintRight;
    int gameState = 0;

    Solver() = default;

    VerletObject& addObject(sf::Vector2f position, int level)
    {
        switch (level) {
            case 1:
                return m_objects.emplace_back(position, 10.0f, 1, sf::Color::Blue);
                break;
            case 2:
                return m_objects.emplace_back(position, 20.0f, 2, sf::Color::Red);
                break;
            case 3:
                return m_objects.emplace_back(position, 30.0f, 3, sf::Color::Green);
                break;
            case 4:
                return m_objects.emplace_back(position, 40.0f, 4, sf::Color::Yellow);
                break;
            case 5:
                return m_objects.emplace_back(position, 50.0f, 5, sf::Color::Magenta);
                break;
            case 6:
                return m_objects.emplace_back(position, 60.0f, 6, sf::Color(076,047,037));
                break;
            case 7:
                return m_objects.emplace_back(position, 70.0f, 7, sf::Color(076,111,140));
                break;
            case 8:
                return m_objects.emplace_back(position, 80.0f, 8, sf::Color(132,175,170));
                break;
            case 9:
                return m_objects.emplace_back(position, 90.0f, 9, sf::Color(222,076,137));
                break;
            case 10:
                return m_objects.emplace_back(position, 100.0f, 10, sf::Color(037,041,074));
                break;
            case 11:
                gameState = 2;
                return m_objects.emplace_back(position, 110.0f, 11, sf::Color::Cyan);
                break;
            default:
                break;
        }

        std::cout << "You shouldn't be here" << std::endl;
        return m_objects.emplace_back(position, 10.0f, 1, sf::Color::Black);
    }

    void update()
    {
        m_time += m_frame_dt;
        const float step_dt = getStepDt();
        for (uint32_t i{m_sub_steps}; i--;) {
            applyGravity();
            checkCollisions(step_dt);
            applyConstraint();
            updateObjects(step_dt);
        }

        if (gameState == 1) {
            Reset();
        }
    }

    void Reset()
    {
        m_objects.clear();
        m_merges.clear();
        clock.restart();
        gameState = 0;
    }

    void setSimulationUpdateRate(uint32_t rate)
    {
        m_frame_dt = 1.0f / static_cast<float>(rate);
    }

    void setConstraint(sf::Vector2f position, float radius)
    {
        m_constraint_base = position;
        m_constraint_radius = radius;

        constraintBottom = new sf::RectangleShape(sf::Vector2f(m_constraint_radius, 10.0f));
        constraintLeft = new sf::RectangleShape(sf::Vector2f(10.0f, m_constraint_radius * 1.25f));
        constraintRight = new sf::RectangleShape(sf::Vector2f(10.0f, m_constraint_radius * 1.25f));

        constraintBottom->setOrigin(m_constraint_radius / 2.0f, 5.0f / 2.0f);
        constraintLeft->setOrigin(5.0f / 2.0f, m_constraint_radius * 1.25f / 2.0f);
        constraintRight->setOrigin(5.0f / 2.0f, m_constraint_radius * 1.25f / 2.0f);
        constraintBottom->setPosition(m_constraint_base.x, m_constraint_base.y * 2.0f * 0.875f);
        constraintLeft->setPosition(m_constraint_base.x - m_constraint_radius * 0.5f, m_constraint_base.y * 2.0f * 0.875f -  m_constraint_radius * 1.25f / 2.0f + 8.0f);
        constraintRight->setPosition(m_constraint_base.x + m_constraint_radius * 0.5f, m_constraint_base.y * 2.0f * 0.875f - m_constraint_radius * 1.25f / 2.0f + 8.0f);

        constraintBottom->setFillColor(sf::Color::Black);
        constraintLeft->setFillColor(sf::Color::Black);
        constraintRight->setFillColor(sf::Color::Black);
    }

    void setSubStepsCount(uint32_t sub_steps)
    {
        m_sub_steps = sub_steps;
    }

    void setObjectVelocity(VerletObject& object, sf::Vector2f v)
    {
        object.setVelocity(v, getStepDt());
    }

    [[nodiscard]]
    const std::vector<VerletObject>& getObjects() const
    {
        return m_objects;
    }

    [[nodiscard]]
    sf::Vector3f getConstraint() const
    {
        return {m_constraint_base.x, m_constraint_base.y, m_constraint_radius};
    }

    [[nodiscard]]
    uint64_t getObjectsCount() const
    {
        return m_objects.size();
    }

    [[nodiscard]]
    float getTime() const
    {
        return m_time;
    }

    [[nodiscard]]
    float getStepDt() const
    {
        return m_frame_dt / static_cast<float>(m_sub_steps);
    }

private:
    uint32_t                  m_sub_steps          = 1;
    sf::Vector2f              m_gravity            = {0.0f, 1000.0f};
    sf::Vector2f              m_constraint_base;
    float                     m_constraint_radius  = 100.0f;
    std::vector<VerletObject> m_objects;
    float                     m_time               = 0.0f;
    float                     m_frame_dt           = 0.0f;
    float                     m_max_velocity       = 10.0f;
    std::vector<std::tuple<sf::Vector2f, int>> m_merges;
    sf::Clock clock;

    void applyGravity()
    {
        for (auto& obj : m_objects) {
            obj.accelerate(m_gravity);
        }
    }

    void checkCollisions(float dt)
    {
        const float    response_coef = 0.75f;
        const uint64_t objects_count = m_objects.size();
        // Iterate on all objects
        for (uint64_t i{0}; i < objects_count; ++i) {
            VerletObject& object_1 = m_objects[i];
            // Iterate on object involved in new collision pairs
            for (uint64_t k{i + 1}; k < objects_count; ++k) {
                VerletObject&      object_2 = m_objects[k];
                const sf::Vector2f v        = object_1.position - object_2.position;
                const float        dist2    = v.x * v.x + v.y * v.y;
                const float        min_dist = object_1.radius + object_2.radius;
                // Check overlapping
                if (dist2 < min_dist * min_dist) {
                    if (object_1.radius == object_2.radius && !object_1.merging && !object_2.merging) {
                        sf::Vector2f newPosition = sf::Vector2f((object_1.position.x + object_2.position.x) / 2.0f, (object_1.position.y + object_2.position.y) / 2.0f);
                        object_1.merging = true;
                        object_2.merging = true;
                        m_merges.emplace_back(newPosition, object_1.level + 1);
                    }
                    const float        dist  = sqrt(dist2);
                    const sf::Vector2f n     = v / dist;
                    const float mass_ratio_1 = object_1.radius / (object_1.radius + object_2.radius);
                    const float mass_ratio_2 = object_2.radius / (object_1.radius + object_2.radius);
                    const float delta        = 0.5f * response_coef * (dist - min_dist);
                    // Update positions
                    object_1.position -= n * (mass_ratio_2 * delta);
                    object_2.position += n * (mass_ratio_1 * delta);
                }
            }
        }

        CallMerges();
    }

    void CallMerges() {
        for (int i = 0; i < m_objects.size(); i++) {
            if (m_objects[i].merging) {
                m_objects.erase(m_objects.begin() + i);
            }
        }
        for (auto merge : m_merges) {
            addObject(std::get<0>(merge), std::get<1>(merge));
        }

        m_merges.clear();
        //}
    }

    void applyConstraint()
    {
        for (auto& obj : m_objects) {
            if (obj.position.x - obj.radius < constraintLeft->getPosition().x + constraintLeft->getSize().x / 2.0f) {
                obj.position = sf::Vector2f(constraintLeft->getPosition().x + constraintLeft->getSize().x / 2.0f + obj.radius, obj.position.y);
            }
            else if (obj.position.x + obj.radius > constraintRight->getPosition().x - constraintRight->getSize().x / 2.0f) {
                obj.position = sf::Vector2f(constraintRight->getPosition().x - constraintRight->getSize().x / 2.0f - obj.radius, obj.position.y);
            }
            else if (obj.position.y + obj.radius > constraintBottom->getPosition().y - constraintBottom->getSize().y / 2) {
                obj.position = sf::Vector2f(obj.position.x, constraintBottom->getPosition().y - constraintBottom->getSize().y / 2.0f - obj.radius);
            }
        }
    }

    void updateObjects(float dt)
    {
        bool aboveLine = false;
        for (auto& obj : m_objects) {
            obj.update(dt);
            if (obj.position.y - obj.radius < m_constraint_base.y * 0.5f && !aboveLine) {
                aboveLine = true;
            }
        }

        if (!aboveLine) {
            clock.restart();
        }

        if (clock.getElapsedTime() >= sf::seconds(3.0f)) {
            gameState = 1;
        }
    }
};
