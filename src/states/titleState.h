#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "../game/state.h"

class TitleState : public State {
    private:
        sf::Text titleText;
        sf::Text promptText;
        sf::Time blinkTime;
        bool showText;
        
    protected:

    public:
        TitleState(StateStack& stack, Context context);
        ~TitleState();

        bool Update(sf::Time deltaTime) override;
        bool UpdateEvents(const sf::Event& event) override;
        void UpdateDisplay() override;
        
};

#endif