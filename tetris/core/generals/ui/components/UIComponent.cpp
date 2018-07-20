//
//  UIComponent.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIComponent.hpp"

#include <algorithm>
#include <iostream>

#include "Utils.hpp"
#include "TouchEvent.hpp"

UIComponent::UIComponent(const Size& size)
:coordinates(0, 0)
,size(size)
,parent(nullptr)
,backgroundColor(Color::NONE)
,anchor(Anchor::LOWER_LEFT)
{
    
}

UIComponent::~UIComponent() {
    std::cout << "UIComponent::~UIComponent start " << className << " numChildren:" << children.size() <<std::endl;
    
    for (auto it=children.begin(); it!=children.end(); ++it) {
        SafeDelete(*it);
    }
    children.clear();
    std::cout << "UIComponent::~UIComponent　end " << className << " numChildren:" << children.size() <<std::endl;
}

void UIComponent::draw() const {
}

bool UIComponent::handleTouchEvent(const TouchEvent& touchEvent) {
    for (auto it=children.begin(); it!=children.end(); ++it) {
        if ((*it)->handleTouchEvent(touchEvent)) {
            return true;
        }
    }
    
    if (!isTouchEventInside(touchEvent)) {
        return false;
    }
    return true;
}

void UIComponent::setBackgroundColor(Color::Types color) {
    backgroundColor = color;
}

const vec2d& UIComponent::getRelativeCoordinates() const {
    return coordinates;
}

vec2d UIComponent::getAbsoluteCoordinates() const {
    vec2d absoluteCoordinates = (parent == nullptr ? coordinates : coordinates + parent->getAbsoluteCoordinates());
    auto parentSize = (parent == nullptr ? Size() : parent->getSize());
    switch (anchor) {
        case Anchor::UPPER_CENTER:
            absoluteCoordinates.x += (parentSize.width - size.width) / 2;
            absoluteCoordinates.y += parentSize.height - size.height;
            break;
        case Anchor::LOWER_CENTER:
            absoluteCoordinates.x += (parentSize.width - size.width) / 2;
            break;
        case Anchor::CENTER_LEFT:
            absoluteCoordinates.y += (parentSize.height - size.height) / 2;
            break;
        case Anchor::CENTER:
            absoluteCoordinates.x += (parentSize.width - size.width) / 2;
            absoluteCoordinates.y += (parentSize.height - size.height) / 2;
            break;
        case Anchor::CENTER_RIGHT:
            absoluteCoordinates.x += parentSize.width - size.width;
            absoluteCoordinates.y += (parentSize.height - size.height) / 2;
            break;
        case Anchor::UPPER_LEFT:
            absoluteCoordinates.y += parentSize.height - size.height;
            break;
        case Anchor::UPPER_RIGHT:
            absoluteCoordinates.x += parentSize.width - size.width;
            absoluteCoordinates.y += parentSize.height - size.height;
            break;
        case Anchor::LOWER_LEFT:
            break;
        case Anchor::LOWER_RIGHT:
            absoluteCoordinates.x += parentSize.width - size.width;
            break;
    }
    return absoluteCoordinates;
}

void UIComponent::addChild(UIComponent* child) {
    children.push_back(child);
    child->setParent(this);
}

void UIComponent::removeChild(UIComponent* child) {
    children.erase(remove(children.begin(), children.end(), child), children.end());
    child->setParent(nullptr);
}

void UIComponent::removeAllChildren() {
    for (auto it=children.begin(); it!=children.end(); ++it) {
        removeChild(*it);
    }
}

void UIComponent::setParent(UIComponent* parent) {
    this->parent = parent;
    if (parent != nullptr) {
        setZIndex(parent->getZIndex() + 1);
    }
}

void UIComponent::setCoordinates(const vec2d& coordinates) {
    this->coordinates = coordinates;
}

void UIComponent::setCoordinates(const vec2d& coordinates, Anchor::Types anchor) {
    this->coordinates = coordinates;
    this->anchor = anchor;
}

const Size& UIComponent::getSize() const {
    return size;
}

const std::string& UIComponent::getClassName() const {
    return className;
}

void UIComponent::setZIndex(int zIndex) {
    this->zIndex = zIndex;
    for (auto it=children.begin(); it!=children.end(); ++it) {
        (*it)->setZIndex(zIndex + 1);
    }
}

void UIComponent::setAnchor(Anchor::Types anchor) {
    this->anchor = anchor;
}

Anchor::Types UIComponent::getAnchor() const {
    return anchor;
}

bool UIComponent::isTouchEventInside(const TouchEvent& touchEvent) const {
    const vec2d absoluteCoordinates = getAbsoluteCoordinates();
    return (absoluteCoordinates.x <= touchEvent.getCoordinates().x && touchEvent.getCoordinates().x <= absoluteCoordinates.x + size.width
            && absoluteCoordinates.y <= touchEvent.getCoordinates().y && touchEvent.getCoordinates().y <= absoluteCoordinates.y + size.height);
}
