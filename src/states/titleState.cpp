#include "titleState.h"

TitleState::TitleState(StateStack& stack, Context context) : State(stack, context), titleText(), promptText() {
    sf::RenderWindow& window = *GetContext().window;
    blinkTime = sf::Time::Zero;
    showText = true;
    titleText.setFont(font);
    titleText.setString("PONG");
    CenterOrigin(titleText);
    titleText.setPosition(window.getSize().x/2 - 20, 200);
    titleText.setCharacterSize(50);

    promptText.setFont(font);
    promptText.setString("Press any key to start");
    CenterOrigin(promptText);
    promptText.setPosition(window.getSize().x/2, 400);
    promptText.setCharacterSize(30);
}

TitleState::~TitleState() {

}

bool TitleState::UpdateEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        std::cout << "Moving from Title to Menu" << std::endl;
        RequestStackPop();
        RequestStackPush(States::Menu);
    }

    return true;
}

bool TitleState::Update(sf::Time deltaTime) {
    blinkTime += deltaTime;

    if (blinkTime >= sf::seconds(0.5f)) {
        showText = !showText;
        if (showText == true) {
            blinkTime = sf::Time::Zero;
        }
        else {
            blinkTime = sf::seconds(0.3f);
        }
    }

    return true;
}

void TitleState::UpdateDisplay() {
    sf::RenderWindow& window = *GetContext().window;
    window.draw(titleText);
    if (showText == true)
        window.draw(promptText);
}