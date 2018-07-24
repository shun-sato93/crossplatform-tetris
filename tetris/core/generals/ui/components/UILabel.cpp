//
//  UILabel.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UILabel.hpp"

#include "IOInterface.hpp"

UILabel::UILabel(const std::string& text, Color::Types textColor)
:UIComponent(Size())
,text(text)
,textColor(textColor) {
    className = "UILabel " + text;
    sizeToFitText();
}

UILabel::UILabel(const std::string& text, Color::Types textColor, const Size& size)
:UIComponent(size)
,text(text)
,textColor(textColor) {
    className = "UILabel " + text;
}

UILabel::~UILabel() {
}

void UILabel::draw() const {
    const vec2d absoluteCoordinates = getAbsoluteCoordinates();
    IOInterface::drawRectangle(absoluteCoordinates.x, absoluteCoordinates.y, size.width, size.height, backgroundColor);
    
    Size textSize = IOInterface::getTextSize(text, 0);
    IOInterface::drawText(absoluteCoordinates.x + (size.width - textSize.width) / 2, absoluteCoordinates.y + (size.height - textSize.height) / 2, text, textColor);
}

void UILabel::setText(const std::string& text) {
    this->text = text;
}

void UILabel::setTextColor(Color::Types color) {
    this->textColor = color;
}

void UILabel::sizeToFitText() {
    size = IOInterface::getTextSize(text, 0);
}
