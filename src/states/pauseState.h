#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "../game/state.h"

class PauseState: public State {
    private:

    protected:

    public:
        PauseState(StateStack& stack, Context context);
        ~PauseState();
        bool Update(sf::Time deltaTime) override;
        bool UpdateEvents(const sf::Event& event) override;
        void UpdateDisplay() override;
};

#endif