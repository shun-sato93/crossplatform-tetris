//
//  UITitleScreen.hpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UITitleScreen_hpp
#define UITitleScreen_hpp

#include "UIBaseView.hpp"

/**
 * Title screen.
 */
class UITitleScreen: public UIBaseView {
public:
    UITitleScreen();
    ~UITitleScreen();
    
    void draw() const override;
private:
    void setup();
};

#endif /* UITitleScreen_hpp */
