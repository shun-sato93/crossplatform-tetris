//
//  IOInterface.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "IOInterface.hpp"

#include "Constants.hpp"
#include "GameContext.hpp"
#include "GameMode.hpp"
#include "opengl.hpp"

IOInterface::IOInterface() {
    
}

IOInterface::~IOInterface() {
    
}

void IOInterface::drawRectangle(double x1, double y1, double width, double height, Color::Types color) const {
    OpenGL::drawRectangle(color, x1, y1, x1+width, y1+height);
}

void IOInterface::drawText(double x, double y, std::string text, Color::Types color) const {
    OpenGL::drawText(x, y, text, color);
}

void IOInterface::keyboardInput(Keyboard::Types input) const {
    auto gameMode = GameContext::get().getGameMode();
    if (gameMode != nullptr) {
        gameMode->handleKeyboardInput(input);
    }
}

void IOInterface::changeWindowSize(int width, int height) const {
    OpenGL::changeWindowSize(width, height);
}

Size IOInterface::getTextSize(const std::string& text, int font) const {
    return OpenGL::getTextSize(text, font);
}
