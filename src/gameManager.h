#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game/game.h"

class GameManager: public Game {
    enum BrushType {Draw, Erase, Eyedrop};

    protected:
        sf::VertexArray grid;
        sf::Vector2i gridDimensions;
        sf::Vector2f xMargin;
        sf::Vector2f yMargin;
        sf::Vector2f unitDimensions;

        BrushType brushType = Draw;
        int brushSize = 1;
        int brushTexture = 1;
        
        std::string assetPath;
        std::unordered_map<int, sf::Texture*> assets;
        std::unordered_map<int, GameObject*> sprites;
        std::unordered_map<std::string, GameObject*> tiles;
        sf::Text typeText;
        sf::Font font;
        
        sf::Vector2i mouseGameObject;
        sf::Vector2i tileIndex;
        sf::Vector2f localGameObjectPosition;
        std::string tileIndexName;
    public:
        GameManager();
        ~GameManager();

        void CreateGrid(sf::Vector2i, sf::Vector2f, sf::Vector2f);
        void AddAsset(int, std::string);
        void LoadAssets();

        sf::Vector2i GetCurrentGameObjectIndex();

        void Update() override;
        void UpdateDisplay() override;
        void UpdateInput() override;
        void UpdateEvents() override;

        void Save();
        void Load(std::string);
};

#endif