//
//  UIManager.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIManager.hpp"

#include <iostream>

#include "Coordinates.hpp"
#include "UIBaseView.hpp"
#include "Utils.hpp"

UIManager::UIManager()
{
}

UIManager::~UIManager() {
}

void UIManager::update() {
    for (auto it=baseViews.begin(); it!=baseViews.end();) {
        if ((*it)->isClosed()) {
            SafeDelete(*it);
            it = baseViews.erase(it);
        } else {
            ++it;
        }
    }
}

void UIManager::handleTouchEvent(const TouchEvent& touchEvent) {
    // using reverse iterator to handle touch event in zindex descend order
    for (auto it=baseViews.rbegin(); it!=baseViews.rend(); ++it) {
        if ((*it)->handleTouchEvent(touchEvent)) {
            return;
        }
    }
}

void UIManager::addNewBaseUI(UIBaseView* baseView) {
    baseViews.push_back(baseView);
    // sort by zindex to prioritize top layer ui
    sort(baseViews.begin(), baseViews.end(), &Drawable::zindexAscend);
    std::cout << "UIManager::addNewBaseUI " << baseView->getClassName() << " " << baseView->getZIndex() << std::endl;
}

void UIManager::clearAllBaseUI() {
    for (auto it=baseViews.begin(); it!=baseViews.end(); ++it) {
        (*it)->close();
    }
}

const std::vector<UIBaseView*>& UIManager::getBaseViews() const {
    return baseViews;
}
