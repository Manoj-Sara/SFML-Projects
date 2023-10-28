#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game/game.h"

class GameManager: public Game {
    public:
        const int maxParticles = 64;
        const float PI = 3.141592654f;
        std::vector<Particle> particles;
        sf::Clock deltaSrc;


        GameManager();
        ~GameManager();

        void DrawParticles();
        sf::Vector2i GetCurrentParticleIndex();

        void Update() override;
        void UpdateDisplay() override;
        void UpdateInput() override;
        void UpdateEvents() override;

        int rollRandomPositiveInteger(int);
        float rollRandomFloat01();
};

#endif