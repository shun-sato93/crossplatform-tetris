//
//  UIBaseView.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIBaseView.hpp"

#include "Coordinates.hpp"

UIBaseView::UIBaseView(int zIndex)
:UIView(getWindowSize(), Color::NONE)
,_isClosed(false)
,callbackClosed(nullptr)
{
    className = "UIBaseView";
    
    this->zIndex =zIndex;
}

UIBaseView::~UIBaseView() {
    
}

bool UIBaseView::handleTouchEvent(const TouchEvent& touchEvent) {
    if (_isClosed) {
        return false;
    }
    
    for (auto it=children.begin(); it!=children.end(); ++it) {
        if ((*it)->handleTouchEvent(touchEvent)) {
            return true;
        }
    }
    
    return false;
}

void UIBaseView::close() {
    _isClosed = true;
    if (callbackClosed) {
        callbackClosed();
    }
}

void UIBaseView::setCallbackClosed(std::function<void(void)> callbackClosed) {
    this->callbackClosed = callbackClosed;
}

bool UIBaseView::isClosed() const {
    return _isClosed;
}

void UIBaseView::addChild(UIComponent* child) {
    UIComponent::addChild(child);
}
