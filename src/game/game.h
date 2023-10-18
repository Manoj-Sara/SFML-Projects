#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

#include "tile.h"

class Game {
    protected:
        // window
        sf::RenderWindow* window;
        sf::RenderWindow* windowPal;
        sf::RenderWindow* windowText;
        float windowHeight;
        float windowWidth;
        float windowPalHeight;
        float windowPalWidth;
        float windowTextHeight;
        float windowTextWidth;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::Vector2f mousePosition;

        const int SCREEN_WIDTH = 512;
        const int SCREEN_HEIGHT = 512;
        const int PALETTE_SCREEN_WIDTH = 130;
        const int PALETTE_SCREEN_HEIGHT = 512;
        const int TEXT_SCREEN_WIDTH = 512;
        const int TEXT_SCREEN_HEIGHT = 200;
        const int TILE_WIDTH = 64;
        const int TILE_HEIGHT = 64;
    public:
        Game();
        ~Game();
        virtual void Update();
        virtual void UpdateDisplay();
        virtual void UpdateInput();
        virtual void UpdateEvents();
        void UpdateMouse();
        void Play();
        void CreateWindows();
        void LoadAssets();
        void CreatePalette();


};

#endif