#ifndef APPLICATION_H
#define APPLICATION_H

#include "game/stateStack.h"

// class Application {
//     public:
//         Application();
//         void run();

//     private:
//         void processInput();
//         void Update(sf::Time deltaTime);
//         void render();
//         void UpdateStatistics(sf::Time deltaTime);
//         void RegisterStates();

//         static const sf::Time TimePerFrame;

//         sf::RenderWindow window;
//         sf::Font font;

//         StateStack statestack;
//         sf::Text statisticsText;
//         sf::Time statisticsUpdateTime;
//         std::size_t statisticsNumFrames;
// };

#include "game/game.h"

class Application : public Game {
    public:
        Application();
        ~Application();

        void RegisterStates() override;
        void Update(sf::Time deltaTime) override;
        void UpdateDisplay() override;
        void UpdateEvents() override;
    
    private:
        sf::Font font;
        std::string assetPath;
};

#endif