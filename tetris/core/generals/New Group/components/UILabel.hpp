//
//  UILabel.hpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UILabel_hpp
#define UILabel_hpp

#include <string>

#include "ColorDefinition.hpp"
#include "UIComponent.hpp"

class TouchEvent;

class UILabel: public UIComponent {
public:
    UILabel(const std::string& text, Color::Types textColor);
    UILabel(const std::string& text, Color::Types textColor, int width, int height);
    ~UILabel();
    
    void draw() const override;
    
    void setText(const std::string& text);
    void setTextColor(Color::Types color);
    void sizeToFitText();
private:
    Color::Types textColor;
    std::string text;
};

#endif /* UILabel_hpp */
