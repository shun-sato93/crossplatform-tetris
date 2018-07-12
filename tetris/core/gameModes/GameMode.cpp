//
//  GameMode.cpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "GameMode.hpp"

#include "UIGameMenuWindow.hpp"
#include "UIManager.hpp"

GameMode::GameMode()
:menuWindow(nullptr) {
    
}

GameMode::~GameMode() {
    if (menuWindow != nullptr) {
        menuWindow->close();
    }
}

void GameMode::openMenuWindow() {
    if (menuWindow != nullptr) {
        closeMenuWindow();
    }
    menuWindow = new UIGameMenuWindow();
    menuWindow->setCallbackClosed([&]() {
        menuWindow = nullptr;
    });
    UIManager::get().addNewBaseUI(menuWindow);
}

void GameMode::closeMenuWindow() {
    if (menuWindow == nullptr) {
        return;
    }
    menuWindow->close();
    pause(false);
    menuWindow = nullptr;
}
