//
//  opengl.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef opengl_hpp
#define opengl_hpp

#include <string>

#include "ColorDefinition.hpp"
#include "Size.hpp"


namespace OpenGL {
    void setup(int argc, char** argv);
    void display();
    void update();
    void keyboardInput(unsigned char key, int x, int y);
    void specialKeyboardInput(int key, int x, int y);
    void mouseInput(int button, int state, int x, int y);
    
    void changeWindowSize(int width, int height);
    void reshape(int width, int height);
    
    void drawRectangle(Color::Types color, double x1, double y1, double x2, double y2);
    void drawText(double x, double y, const std::string& text, Color::Types color);
    void setColor(Color::Types color);
    
    Size getTextSize(const std::string& text, int font);
}

#endif /* opengl_hpp */
