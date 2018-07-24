//
//  UIGameOver.hpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIGameOver_hpp
#define UIGameOver_hpp

#include <functional>

#include "UIBaseView.hpp"

/**
 * Game over window.
 */
class UIGameOver: public UIBaseView {
public:
    UIGameOver(int score, std::function<void(void)> retryDelegate);
    ~UIGameOver();
    
    void draw() const override;
private:
    void setup();
    
    std::function<void(void)> retryDelegate;
    const int score;
};

#endif /* UIGameOver_hpp */
