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

#include "stateStack.h"

class Game {
    protected:
        sf::RenderWindow window;
        float windowHeight;
        float windowWidth;
        sf::VideoMode videoMode;
        sf::Vector2f mousePosition;

        StateStack stateStack;

        const sf::Time timePerFrame = sf::seconds(1.0f/60.0f);

        const int SCREEN_WIDTH = 700;
        const int SCREEN_HEIGHT = 512;

        sf::Font font;
        std::string assetPath;

    public:
        Game();
        ~Game();
        void Play();
        void CreateWindow();

        virtual void RegisterStates();
        virtual void Update(sf::Time deltaTime);
        virtual void UpdateDisplay();
        virtual void UpdateEvents();

        void LoadAssets();

};

#endif