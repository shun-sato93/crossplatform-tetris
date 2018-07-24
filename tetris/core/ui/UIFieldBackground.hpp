//
//  UIFieldBackground.hpp
//  tetris
//
//  Created by Shun Sato on 7/3/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIFieldBackground_hpp
#define UIFieldBackground_hpp

#include "UIBaseView.hpp"

class UILabel;

/**
 * Background UI during a game.
 */
class UIFieldBackground: public UIBaseView {
public:
    UIFieldBackground();
    ~UIFieldBackground();
    
    void draw() const override;
    void setScore(int score);
    void setHighscore(int highscore);
private:
    void setup();
    
    UILabel* scoreLabel;
    UILabel* highscoreLabel;
};

#endif /* UIFieldBackground_hpp */
