#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <cmath>
#include "../game/state.h"

class GameState: public State {
    private:
        enum GameStates {
            NoPlay,
            PrePlay,
            InPlay,
            PostPlay
        };

        enum Direction {
            Still,
            Up,
            Down
        };

        const float MAX_BOUNCE_ANGLE = 5 * M_PI / 12;
        struct Paddle {
            sf::RectangleShape paddleBox;
            Direction direction;

            Paddle(sf::RectangleShape paddleBox, Direction direction = Still) : paddleBox(paddleBox), direction(direction) {};
        };

        sf::CircleShape ball;
        
        sf::Text scoreLeftText;
        int scoreLeft;
        sf::Text scoreRightText;
        int scoreRight;

        float ballSpeed;
        sf::Vector2f ballVelocity;
        int paddle1Move;
        int paddle2Move;

        Paddle paddleLeft;
        Paddle paddleRight;

        GameStates playState;
        bool showText;
        sf::Time pauseTime;
        sf::Time blinkTime;
        sf::Time startDelay;

    protected:

    public:
        GameState(StateStack& stack, Context context);
        ~GameState();
        bool Update(sf::Time deltaTime) override;
        bool UpdateEvents(const sf::Event& event) override;
        void UpdateDisplay() override;

        void CalcBounce(sf::RectangleShape paddle);
        sf::Vector2f RandomVelocity();
};

#endif