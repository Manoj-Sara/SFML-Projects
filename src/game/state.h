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
#include <map>
#include <functional>
#include <utility>
#include <memory>

#include "stateIdentifiers.h"

class StateStack;

class State {
    public:
        typedef std::unique_ptr<State> ptr;

        struct Context {
            sf::RenderWindow* window;
            sf::Font font;
            int playerCount;

            Context(sf::RenderWindow& window, int playerCount = 0) : window(&window), playerCount(playerCount) {};
        };
        
        State(StateStack& stack, Context context);
        virtual ~State();

        virtual bool Update(sf::Time deltaTime) = 0;
        virtual bool UpdateEvents(const sf::Event& event) = 0;
        virtual void UpdateDisplay() = 0;

        void CenterOrigin(sf::Text& text);

    protected:
        sf::Font font;
        
        void RequestStackPush(States::ID stateID);
        void RequestStackPop();
        void RequestStackClear();

        Context GetContext() const;

    private:
        StateStack* stack;
        Context context;
};

#endif