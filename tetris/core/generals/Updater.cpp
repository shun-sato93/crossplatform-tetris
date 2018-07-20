//
//  Updater.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "Updater.hpp"

#include <algorithm>

#include "Updatable.hpp"


Updater::Updater()
:hasNumberOfRegisteredItemsChanged(false)
{}

Updater::~Updater() {}

void Updater::update(bool isContinuing)  {
    if (!isContinuing) {
        for (auto it=items.begin(); it!=items.end(); ++it) {
            (*it)->setHasUpdatedInThisFrame(false);
        }
    }
    
    for (auto it=items.begin(); it!=items.end(); ++it) {
        if ((*it)->hasUpdatedInThisFrame()) {
            continue;
        }
        (*it)->setHasUpdatedInThisFrame(true);
        
        if (!(*it)->isPaused()) {
            (*it)->update();
        }
        
        if (hasNumberOfRegisteredItemsChanged) {
            hasNumberOfRegisteredItemsChanged = false;
            update(true);
            return;
        }
    }
}

void Updater::registerUpdatable(Updatable* item) {
    items.push_back(item);
    hasNumberOfRegisteredItemsChanged = true;
}

void Updater::unregisterUpdatable(Updatable* item) {
    items.erase(remove(items.begin(), items.end(), item), items.end());
    hasNumberOfRegisteredItemsChanged = true;
}
