//
//  Drawable.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "Drawable.hpp"

#include "Drawer.hpp"

Drawable::Drawable()
:zIndex(0)
,_isVisible(true) {
    Drawer::get().registerDrawable(this);
    this->zIndex.setHook([=](int oldValue, int newValue) {
        if (oldValue != newValue) {
            Drawer::get().sortDrawables();
        }
    });
}

Drawable::Drawable(int zIndex)
:zIndex(zIndex)
,_isVisible(true) {
    
    Drawer::get().registerDrawable(this);
    this->zIndex.setHook([=](int oldValue, int newValue) {
        if (oldValue != newValue) {
            Drawer::get().sortDrawables();
        }
    });
}

Drawable::~Drawable() {
    Drawer::get().unregisterDrawable(this);
}

bool Drawable::isVisible() const {
    return _isVisible;
}

int Drawable::getZIndex() const {
    return zIndex.get();
}

void Drawable::setZIndex(int zIndex) {
    this->zIndex = zIndex;
}
