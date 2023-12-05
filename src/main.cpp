#include <SFML/Graphics.hpp>
#include <iostream>

#include "gameManager.h"

int main()
{
   srand(time(0));
   GameManager gameManager;
   gameManager.Play();
   return 0;
}