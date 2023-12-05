#include "gameState.h"

GameState::GameState(StateStack& stack, Context context) : State::State(stack, context),
paddleRight(sf::RectangleShape(sf::Vector2f(10.0f, 70.0f))), paddleLeft(sf::RectangleShape(sf::Vector2f(10.0f, 70.0f))), ball(5.0f) {
    sf::RenderWindow& window = *GetContext().window;

    CenterOrigin(paddleRight.paddleBox);
    CenterOrigin(paddleLeft.paddleBox);
    CenterOrigin(ball);
    paddleRight.paddleBox.setPosition(window.getSize().x - 20, 256);
    paddleLeft.paddleBox.setPosition(20, 256);
    ball.setPosition(window.getSize().x/2, window.getSize().y/2);
    ballSpeed = 450.0f;
    ballVelocity = RandomVelocity();
    paddle1Move = 0;
    paddle2Move = 0;

    scoreLeft = 0;
    CenterOrigin(scoreLeftText);
    scoreLeftText.setFont(font);
    scoreLeftText.setString(std::to_string(scoreLeft));
    scoreLeftText.setCharacterSize(50);
    scoreLeftText.setPosition(window.getSize().x/4, 100);
    scoreRight = 0;
    CenterOrigin(scoreRightText);
    scoreRightText.setFont(font);
    scoreRightText.setString(std::to_string(scoreRight));
    scoreRightText.setCharacterSize(50);
    scoreRightText.setPosition((window.getSize().x/4)*3, 100);

    playState = GameStates::PrePlay;
    showText = true;
    pauseTime = sf::seconds(1.0f);
    blinkTime = sf::Time::Zero;
}

GameState::~GameState() {

}

bool GameState::Update(sf::Time deltaTime) {
    sf::RenderWindow& window = *GetContext().window;
    
    if (startDelay >= sf::Time::Zero) {
        startDelay -= deltaTime;
    }

    if (paddleRight.direction == Direction::Down) {
        if (paddleRight.paddleBox.getGlobalBounds().top + paddleRight.paddleBox.getSize().y < window.getSize().y) {
            paddleRight.paddleBox.move(0.0f, 400.0f * deltaTime.asSeconds());
        }
    }
    if (paddleRight.direction == Direction::Up) {
        if (paddleRight.paddleBox.getGlobalBounds().top > 0) {
            paddleRight.paddleBox.move(0.0f, -400.0f * deltaTime.asSeconds());
        }
    }
    if (paddleLeft.direction == Direction::Down) {
        if (paddleLeft.paddleBox.getGlobalBounds().top + paddleLeft.paddleBox.getSize().y < window.getSize().y) {
            if (GetContext().playerCount == 1 && startDelay < sf::Time::Zero) {
                paddleLeft.paddleBox.move(0.0f, 350.0f * deltaTime.asSeconds());
            }
            if (GetContext().playerCount == 2) {
                paddleLeft.paddleBox.move(0.0f, 400.0f * deltaTime.asSeconds());
            }
        }
    }
    if (paddleLeft.direction == Direction::Up) {
        if (paddleLeft.paddleBox.getGlobalBounds().top > 0) {
            if (GetContext().playerCount == 1 && startDelay < sf::Time::Zero) {
                paddleLeft.paddleBox.move(0.0f, -350.0f * deltaTime.asSeconds());
            }
            if (GetContext().playerCount == 2) {
                paddleLeft.paddleBox.move(0.0f, -400.0f * deltaTime.asSeconds());
            }
        }
    }
    if (GetContext().playerCount == 1) {
        if (paddleLeft.paddleBox.getPosition().y > ball.getPosition().y - 10.0f && paddleLeft.paddleBox.getPosition().y < ball.getPosition().y + 10.0f) {
            paddleLeft.direction = Direction::Still;
        }
        else if (paddleLeft.paddleBox.getPosition().y < ball.getPosition().y && paddleLeft.paddleBox.getGlobalBounds().top + paddleLeft.paddleBox.getSize().y < window.getSize().y) {
            paddleLeft.direction = Direction::Down;
        }
        else if (paddleLeft.paddleBox.getPosition().y > ball.getPosition().y && paddleLeft.paddleBox.getGlobalBounds().top > 0) {
            paddleLeft.direction = Direction::Up;
        }
    }

    switch (playState) {
        case PrePlay:
            pauseTime -= deltaTime;
            if (pauseTime <= sf::Time::Zero) {
                playState = GameStates::InPlay;
                pauseTime = sf::seconds(1.0f);
            }

            break;

        case InPlay:
            if (ball.getGlobalBounds().intersects(paddleRight.paddleBox.getGlobalBounds())) {
                CalcBounce(paddleRight.paddleBox);

                ballSpeed += 10.0f;
                if (GetContext().playerCount == 1) {
                    startDelay = sf::seconds(0.3f);
                }
            }
            if (ball.getGlobalBounds().intersects(paddleLeft.paddleBox.getGlobalBounds())) {
                CalcBounce(paddleLeft.paddleBox);
            }

            if (ball.getGlobalBounds().top <= 0 || ball.getGlobalBounds().top + (ball.getRadius() * 2) >= window.getSize().y) {
                ballVelocity.y = -ballVelocity.y;
            }
            if (ball.getGlobalBounds().left + (ball.getRadius() * 2) < 0) {
                ballVelocity.x = -ballVelocity.x;
                scoreRight++;
                scoreRightText.setString(std::to_string(scoreRight));
                playState = GameStates::PostPlay;
            }
            else if (ball.getGlobalBounds().left > window.getSize().x) {
                ballVelocity.x = -ballVelocity.x;
                scoreLeft++;
                scoreLeftText.setString(std::to_string(scoreLeft));
                playState = GameStates::PostPlay;
            }
            ball.move(ballVelocity * deltaTime.asSeconds());

            break;

        case PostPlay:
            pauseTime -= deltaTime;
            blinkTime += deltaTime;

            if (blinkTime >= sf::seconds(0.23f)) {
                showText = !showText;
                blinkTime = sf::Time::Zero;
            }

            if (pauseTime < sf::Time::Zero) {
                showText = true;
                pauseTime = sf::seconds(0.5f);
                playState = GameStates::PrePlay;
                ball.setPosition(window.getSize().x/2, window.getSize().y/2);
                ballSpeed = 450.0f;
                ballVelocity = RandomVelocity();

            }

            break;

        default:
            break;
    }

    return true;
}

bool GameState::UpdateEvents(const sf::Event& event) {
    sf::RenderWindow& window = *GetContext().window;
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P) {
            RequestStackPush(States::Pause);
            std::cout << "Moving from Game to Pause" << std::endl;
        }
        
        if (event.key.code == sf::Keyboard::Up) {
            paddleRight.direction = Direction::Up;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            paddleRight.direction = Direction::Down;
        }
        if (GetContext().playerCount == 2) {
            if (event.key.code == sf::Keyboard::W) {
                paddleLeft.direction = Direction::Up;
            }
            else if (event.key.code == sf::Keyboard::S) {
                paddleLeft.direction = Direction::Down;
            }
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
            paddleRight.direction = Direction::Still;
        }
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S) {
            paddleLeft.direction = Direction::Still;
        }
    }
    return true;
}

void GameState::UpdateDisplay() {
    sf::RenderWindow& window = *GetContext().window;

    if (showText == true) {
        window.draw(scoreLeftText);
        window.draw(scoreRightText);
    }

    window.draw(paddleRight.paddleBox);
    window.draw(paddleLeft.paddleBox);

    if (playState != GameStates::PostPlay) {
        window.draw(ball);
    }
}

void GameState::CalcBounce(sf::RectangleShape paddle) {
    float displacement = paddle.getPosition().y - ball.getPosition().y;
    float bounceAngle = (displacement / (paddle.getSize().y / 2));
    if (paddle.getPosition().x == paddleRight.paddleBox.getPosition().x) {
        ballVelocity = sf::Vector2f(-cos(bounceAngle), -sin(bounceAngle)) * ballSpeed;
    }
    else if (paddle.getPosition().x == paddleLeft.paddleBox.getPosition().x) {
        ballVelocity = sf::Vector2f(cos(bounceAngle), -sin(bounceAngle)) * ballSpeed;
    }
}

sf::Vector2f GameState::RandomVelocity() {
    float newAngle = -1.0 + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(2.0)));
    return sf::Vector2f(cos(newAngle), sin(newAngle)) * ballSpeed;
}