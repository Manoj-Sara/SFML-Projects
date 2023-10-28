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

#include "particle.h"

class Game {
    protected:
        // window
        sf::RenderWindow* window;
        float windowHeight;
        float windowWidth;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::Vector2f mousePosition;

        const int SCREEN_WIDTH = 512;
        const int SCREEN_HEIGHT = 512;

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

};

#endif