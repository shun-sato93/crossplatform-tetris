//
//  GameMode.hpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef GameMode_hpp
#define GameMode_hpp

#include "Updatable.hpp"

#include "Keyboard.hpp"

class UIGameMenuWindow;

class GameMode {
public:
    GameMode();
    virtual ~GameMode();
    
    virtual void start() = 0;
    virtual void pause(bool isPaused) = 0;
    virtual void quit() = 0;
    virtual void handleKeyboardInput(Keyboard::Types key) = 0;
protected:
    void openMenuWindow();
    void closeMenuWindow();
    
    UIGameMenuWindow* menuWindow;
};

#endif /* GameMode_hpp */
