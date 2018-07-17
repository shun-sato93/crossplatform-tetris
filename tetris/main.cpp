
#include "opengl.hpp"
#include "GameContext.hpp"


int main(int argc, char** argv)
{
    GameContext::get().goTitle();
    OpenGL::setup(argc, argv);
    
    return 0;
}
