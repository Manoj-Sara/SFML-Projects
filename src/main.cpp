#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameManager.h"



// int32_t main(int32_t, char*[])
// {
//     const float        object_spawn_delay    = 0.025f;
//     const float        object_spawn_speed    = 1200.0f;
//     const sf::Vector2f object_spawn_position = {500.0f, 200.0f};
//     const float        object_min_radius     = 1.0f;
//     const float        object_max_radius     = 20.0f;
//     const uint32_t     max_objects_count     = 100;
//     const float        max_angle             = 1.0f;

//    GameManager gameManager;
//    gameManager.Play();
//     return 0;
// }

int main()
{
   srand(time(0));
   GameManager gameManager;
   gameManager.Play();
   return 0;
}