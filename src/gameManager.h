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
        std::unordered_map<int, Tile*> sprites;
        std::unordered_map<std::string, Tile*> tiles;
        sf::Text instructions;
        sf::Font font;
        
        sf::Vector2i mouseTile;
        sf::Vector2i tileIndex;
        sf::Vector2f localTilePosition;
        std::string tileIndexName;
    public:
        GameManager();
        ~GameManager();

        void CreateGrid(sf::Vector2i, sf::Vector2f, sf::Vector2f);
        void AddAsset(int, std::string);
        void LoadAssets();
        void CreatePalette();
        void CreateInstructions();

        void DrawTiles();
        void EraseTiles();
        void EyedropTile();
        sf::Vector2i GetCurrentTileIndex();
        sf::Texture* GetBrushTexture();
        void SetBrushTexture(int);
        void SetBrushSize(int);

        void Update() override;
        void UpdateDisplay() override;
        void UpdateInput() override;
        void UpdateEvents() override;

        void Save();
        void Load(std::string);
};

#endif