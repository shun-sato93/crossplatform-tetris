
#include "opengl.hpp"
#include "GameContext.hpp"


int main(int argc, char** argv)
{
    GameContext::get().goTitle();
    // once a programe enter OpenGL::set() it will never come back since it will go inside a main loop.
    OpenGL::setup(argc, argv);
    
    return 0;
}
