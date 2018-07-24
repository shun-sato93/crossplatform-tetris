//
//  IOInterface.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef IOInterface_hpp
#define IOInterface_hpp

#include <string>

#include "ColorDefinition.hpp"
#include "Keyboard.hpp"
#include "Size.hpp"


/**
 * Interface class for input output.
 * This class separates the core game logics from platform dependent codes.
 * Singleton.
 */
namespace IOInterface {
    /**
     * draw a rectangle at specified coordinates with specified color.
     */
    void drawRectangle(double x, double y, double width, double height, Color::Types color);
    
    /**
     * draw a text at specified coordinates with specified color.
     */
    void drawText(double x, double y, const std::string& text, Color::Types color);
    
    /**
     * handles keyboard events. This should be called from platform dependent input delegates.
     */
    void keyboardInput(Keyboard::Types input);
    
    /**
     * change window size
     */
    void changeWindowSize(int width, int height);
    
    Size getTextSize(const std::string& text, int font);
};

#endif /* IOInterface_hpp */
