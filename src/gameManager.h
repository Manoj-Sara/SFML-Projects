#ifndef APPLICATION_H
#define APPLICATION_H

#include "game/stateStack.h"

#include "game/game.h"

class GameManager : public Game {
    public:
        GameManager();
        ~GameManager();

        void RegisterStates() override;
        void Update(sf::Time deltaTime) override;
        void UpdateDisplay() override;
        void UpdateEvents() override;
    
    private:
        sf::Font font;
        std::string assetPath;
};

#endif