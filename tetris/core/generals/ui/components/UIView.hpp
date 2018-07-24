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

class Size;

/**
 * Plane ui view that simply draws its shape if the color is specified.
 */
class UIView: public UIComponent {
public:
    UIView(const Size& size, Color::Types color);
    ~UIView();
    
    void draw() const override;
protected:
    Color::Types color;
};

#endif /* UIView_hpp */
