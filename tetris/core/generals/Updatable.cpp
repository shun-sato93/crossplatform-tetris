//
//  Updatable.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "Updatable.hpp"

#include "Updater.hpp"

Updatable::Updatable()
:_hasUpdatedInThisFrame(false)
,_isPaused(false)
{
    Updater::get().registerUpdatable(this);
}
Updatable::~Updatable(){
    Updater::get().unregisterUpdatable(this);
}

void Updatable::setHasUpdatedInThisFrame(bool hasUpdatedInThisFrame) {
    _hasUpdatedInThisFrame = hasUpdatedInThisFrame;
}

bool Updatable::hasUpdatedInThisFrame() const {
    return _hasUpdatedInThisFrame;
}

void Updatable::setPause(bool isPaused) {
    _isPaused = isPaused;
}

bool Updatable::isPaused() const {
    return _isPaused;
}
