#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "../game/state.h"

class MenuState: public State {
    private:
        enum Options {
            Play1P,
            Play2P,
            Exit
        };

        std::vector<sf::Text> options;
        int optionIndex;
        sf::RectangleShape optionBox;

    protected:

    public:
        MenuState(StateStack& stack, Context context);
        ~MenuState();
        bool Update(sf::Time deltaTime) override;
        bool UpdateEvents(const sf::Event& event) override;
        void UpdateDisplay() override;

        sf::Text NewOption(std::string optionText);
        void UpdateOptionText();
};

#endif