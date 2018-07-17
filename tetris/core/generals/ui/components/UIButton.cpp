//
//  UIButton.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIButton.hpp"

#include "IOInterface.hpp"

UIButton::UIButton(const Size& size)
:UIComponent(size)
,titleColor(Color::BLACK)
{
    className = "UIButton";
}

UIButton::~UIButton() {
}

void UIButton::draw() const {
    const vec2d absoluteCoordinates = getAbsoluteCoordinates();
    
    IOInterface::get().drawRectangle(absoluteCoordinates.x, absoluteCoordinates.y, size.width, size.height, backgroundColor);
    
    Size textSize = IOInterface::get().getTextSize(title, 0);
    IOInterface::get().drawText(absoluteCoordinates.x + (size.width - textSize.width) / 2, absoluteCoordinates.y + (size.height - textSize.height) / 2, title, titleColor);
}

bool UIButton::handleTouchEvent(const TouchEvent& touchEvent) {
    if (!isTouchEventInside(touchEvent)) {
        return false;
    }
    
    if (event) {
        event();
    }
    
    return true;
}

void UIButton::setEvent(std::function<void(void)> event) {
    this->event = event;
}

void UIButton::setTitle(std::string title) {
    this->title = title;
    className = "UIButton " + title;
}

void UIButton::setTitleColor(Color::Types color) {
    this->titleColor = color;
}
