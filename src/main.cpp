#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameManager.h"

int main()
{
   GameManager gameManager;
   gameManager.Play();
   return 0;
}

//  auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
//     window.setFramerateLimit(144);
//
//     while (window.isOpen())
//     {
//         for (auto event = sf::Event{}; window.pollEvent(event);)
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
//         }
//
//         window.clear();
//         window.display();
//     }