#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../game/state.h"

class GameState: public State {
    private:

    protected:

    public:
        GameState(StateStack& stack, Context context);
        ~GameState();
        bool Update(sf::Time deltaTime) override;
        bool UpdateEvents(const sf::Event& event) override;
        void UpdateDisplay() override;

    
};

#endif