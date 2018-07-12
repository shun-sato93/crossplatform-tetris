
#include "opengl.hpp"
#include "GameContext.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    GameContext::get().goTitle();
    OpenGL::setup(argc, argv);
    
    return 0;
}
