//
//  UIView.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIView.hpp"

#include "IOInterface.hpp"
#include "Size.hpp"

UIView::UIView(const Size& size, Color::Types color)
:UIComponent(size)
,color(color)
{
    className = "UIView";
}

UIView::~UIView()
{}

void UIView::draw() const {
    if (color == Color::NONE) {
        return;
    }
    const vec2d absoluteCoordinates = getAbsoluteCoordinates();
    IOInterface::drawRectangle(absoluteCoordinates.x, absoluteCoordinates.y, size.width, size.height, color);
}
