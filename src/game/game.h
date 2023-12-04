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

#include "gameObject.h"
#include "stateStack.h"

class Game {
    protected:
        // window
        sf::RenderWindow window;
        float windowHeight;
        float windowWidth;
        sf::VideoMode videoMode;
        sf::Vector2f mousePosition;

        StateStack stateStack;

        static const sf::Time timePerFrame;

        const int SCREEN_WIDTH = 512;
        const int SCREEN_HEIGHT = 512;
        const int TILE_WIDTH = 64;
        const int TILE_HEIGHT = 64;

        sf::Font font;
        std::string assetPath;

    public:
        Game();
        ~Game();
        // virtual void Update();
        // virtual void UpdateDisplay();
        // virtual void UpdateInput();
        // void UpdateMouse();
        void Play();
        void CreateWindow();
        // virtual void LoadAssets();

        virtual void RegisterStates();
        virtual void Update(sf::Time deltaTime);
        virtual void UpdateDisplay();
        virtual void UpdateEvents();

        void LoadAssets();

};

#endif