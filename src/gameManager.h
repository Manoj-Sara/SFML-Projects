#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game/game.h"
#include "verletObject.hpp"
#include "solver.hpp"
#include "utils/math.hpp"
#include "utils/number_generator.hpp"

class GameManager: public Game {

    protected:
        sf::Vector2f xMargin;
        sf::Vector2f yMargin;
        sf::Vector2f unitDimensions;
        sf::Clock clock;
        sf::RectangleShape *loseLine;
        
        std::string assetPath;
        std::unordered_map<int, sf::Texture*> assets;
        std::unordered_map<int, GameObject*> sprites;
        std::unordered_map<std::string, GameObject*> tiles;
        std::vector<std::tuple<float, sf::Color>> balls;
        sf::Text winText;
        sf::Font font;
        
        sf::Vector2i mouseGameObject;
        sf::Vector2i tileIndex;
        sf::Vector2f localGameObjectPosition;
        float maxLeft;
        float maxRight;
        float newPosition;
        std::string tileIndexName;

        Solver   solver;
        const float object_spawn_delay = 1.0f;
        const float spawnHeight = 100.0f;
        int currentBall;

    public:
        GameManager();
        ~GameManager();

        void AddAsset(int, std::string);
        void LoadAssets();
        void CreateWinText();

        sf::Vector2i GetCurrentGameObjectIndex();
        void SpawnBall();

        void Update() override;
        void UpdateDisplay() override;
        void UpdateInput() override;
        void UpdateEvents() override;
};

#endif