//
//  Drawer.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "Drawer.hpp"

#include <iostream>

#include "Drawable.hpp"

Drawer::Drawer()
{
    
}

Drawer::~Drawer() {}

void Drawer::draw() const {
    for (auto it=items.begin(); it!=items.end(); ++it) {
        if (!(*it)->isVisible()) {
            continue;
        }
        (*it)->draw();
    }
}

void Drawer::registerDrawable(Drawable* item) {
    items.push_back(item);
    sortDrawables();
}

void Drawer::sortDrawables() {
    // sort by zindex so that drawables will be drawn in proper order
    sort(items.begin(), items.end(), &Drawable::zindexAscend);
}

void Drawer::unregisterDrawable(Drawable* item) {
    items.erase(remove(items.begin(), items.end(), item), items.end());
}
