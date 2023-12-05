# Pong Game Controls
- Arrow Keys to navigate Menu
- Enter Key to select Menu option
- Arrow Keys to move Player 1 (Right Paddle)
- W and S to move Player 2 (Left Paddle)
- P and Escape to pause and unpause

### Code References
- SFML Game Development Textbook by Haller, Hansson (this was a terrible mistake)

### Funny happenstance
- Decided to start implementing oneline statements without brackets
- Spent 40 hours straight completely rewriting all of my code multiple times cuz I couldn't find why something was causing my program to immediately close
- The bug:
    if (event.type == sf::Event::Closed)
            std::cout << "Closed window" << std::endl;
            window.close();
- Combination of being an idiot + trying to prep for any possible errors + being stupid + trying something new but dangerous + being dumb
- Probably will not be using oneline statements any time in the near future