#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

class State {
    protected:

    public:
        State();
        ~State();
        virtual void Update(sf::Time deltaTime);
        virtual void UpdateDisplay();
        virtual void UpdateInput();
        virtual void UpdateEvents();
        
};

#endif