//
//  UIView.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIView.hpp"

#include "IOInterface.hpp"

UIView::UIView(int width, int height, Color::Types color)
:UIComponent(width, height)
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
    IOInterface::get().drawRectangle(absoluteCoordinates.x, absoluteCoordinates.y, size.width, size.height, color);
}
