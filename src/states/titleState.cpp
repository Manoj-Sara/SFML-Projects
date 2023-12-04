#include "titleState.h"

TitleState::TitleState(StateStack& stack, Context context) : State(stack, context), titleText(), promptText() {
    blinkTime = sf::Time::Zero;
    showText = true;

    //titleText.setFont(context.font);
    //std::cout << font.getInfo().family << std::endl;
    std::cout << context.font.getInfo().family << std::endl;
    titleText.setFont(font);
    titleText.setString("PONG");
    CenterOrigin(titleText);
    //titleText.setPosition(context.window->getView().getSize() / 2.f);
    titleText.setPosition(246, 200);
    titleText.setCharacterSize(50);

    //promptText.setFont(context.font);
    promptText.setFont(font);
    promptText.setString("Press any key to start");
    CenterOrigin(promptText);
    //promptText.setPosition(context.window->getView().getSize() / 2.f);
    promptText.setPosition(256, 400);
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
    //std::cout << "HEre's the problem" << std::endl;
    sf::RenderWindow& window = *GetContext().window;
    //std::cout << "got window" << std::endl;
    window.draw(titleText);
    //std::cout << "Drew titeltext" << std::endl;
    if (showText == true)
        window.draw(promptText);
}