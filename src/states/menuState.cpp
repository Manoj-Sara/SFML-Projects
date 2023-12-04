#include "menuState.h"
#include "../game/stateStack.h"

MenuState::MenuState(StateStack& stack, Context context) : State::State(stack, context), optionBox(sf::Vector2f(100, 50)) {
    options.push_back(NewOption("Play 1P"));
    options.push_back(NewOption("Play 2P"));
    options.push_back(NewOption("Exit Game"));

    optionIndex = 0;
    options[0].setFillColor(sf::Color::Black);
    optionBox.setFillColor(sf::Color::White);
    sf::FloatRect bounds = optionBox.getLocalBounds();
    optionBox.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
    optionBox.setPosition(options[0].getPosition());
}

MenuState::~MenuState() {

}

bool MenuState::Update(sf::Time deltaTime) {
    return true;
}

bool MenuState::UpdateEvents(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return false;
    }

    if (event.key.code == sf::Keyboard::Up) {
        if (optionIndex > 0)
            optionIndex--;
        else
            optionIndex = options.size() - 1;
        
        UpdateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Down) {
        if (optionIndex < options.size() - 1)
            optionIndex++;
        else
            optionIndex = 0;

        UpdateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Return) {
        // Code neater with pop request in every condition even if repititive

        if (optionIndex == Play1P) {
            RequestStackPop();
            //stack.SetPlayerCount(1);
            RequestStackPush(States::Game);
            // stack->SetPlayerCount(1);
        }
        else if (optionIndex == Play2P) {
            RequestStackPop();
            //stack.SetPlayerCount(2);
            RequestStackPush(States::Game);
            // stack->SetPlayerCount(2);
        }
        else if (optionIndex == Exit) {
            RequestStackPop(); // Clearing the stack leaves the game
        }
    }

    return true;
}

void MenuState::UpdateDisplay() {
    sf::RenderWindow& window = *GetContext().window;

    window.draw(optionBox);

    for (sf::Text option : options) {
        window.draw(option);
    }
}

sf::Text MenuState::NewOption(std::string optionText) {
    sf::Text newOption;
    float newOptionPos = options.size() * 50;
    newOption.setFont(font);
    newOption.setString(optionText);
    newOption.setCharacterSize(20);
    CenterOrigin(newOption);
    newOption.setPosition(256, 200 + newOptionPos);
    return newOption;
}

void MenuState::UpdateOptionText() {
    if (options.empty()) {
        return;
    }

    for (sf::Text& text : options) {
        text.setFillColor(sf::Color::White);
    }

    optionBox.setPosition(options[optionIndex].getPosition());
    options[optionIndex].setFillColor(sf::Color::Black);
}