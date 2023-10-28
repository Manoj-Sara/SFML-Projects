// define _CRTDBG_MAP_ALLOC
// #define _CRTDBG_MAP_ALLOC_NEW
// #include <cstdlib>
// #include <crtdbg.h>
// #ifdef _DEBUG
//    #ifndef DBG_NEW
//       #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//       #define new DBG_NEW
//    #endif
// #endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameManager.h"

int main()
{
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
   GameManager gameManager;
   gameManager.Play();
   return 0;
}