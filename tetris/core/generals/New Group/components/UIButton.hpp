//
//  UIButton.hpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIButton_hpp
#define UIButton_hpp

#include <functional>
#include <string>

#include "ColorDefinition.hpp"
#include "UIComponent.hpp"

class UIButton: public UIComponent {
public:
    UIButton(int width, int height);
    ~UIButton();
    
    void draw() const override;
    bool handleTouchEvent(const TouchEvent& touchEvent) override;
    
    void setEvent(std::function<void(void)> event);
    
    void setTitle(std::string title);
    void setTitleColor(Color::Types color);
    
private:
    Color::Types titleColor;
    std::string title;
    
    std::function<void(void)> event;
};

#endif /* UIButton_hpp */
