#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "Engine/Engine.h"

int main (int argc, char* argv[])  
{
    Carrot::Engine::GetInstance()->Initialize();
    Carrot::Engine::GetInstance()->Loop();

    return 0;
}