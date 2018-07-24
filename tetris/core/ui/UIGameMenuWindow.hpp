//
//  UIGameMenuWindow.hpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIGameMenuWindow_hpp
#define UIGameMenuWindow_hpp

#include "UIBaseView.hpp"

/**
 * Menu window a user can open during a game.
 */
class UIGameMenuWindow: public UIBaseView {
public:
    UIGameMenuWindow();
    ~UIGameMenuWindow();
    
    void draw() const override;
private:
    void setup();
};

#endif /* UIGameMenuWindow_hpp */
