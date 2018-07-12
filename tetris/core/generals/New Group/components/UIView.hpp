//
//  UIView.hpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIView_hpp
#define UIView_hpp

#include "UIComponent.hpp"
#include "ColorDefinition.hpp"

class UIView: public UIComponent {
public:
    UIView(int width, int height, Color::Types color);
    ~UIView();
    
    void draw() const override;
protected:
    Color::Types color;
};

#endif /* UIView_hpp */
