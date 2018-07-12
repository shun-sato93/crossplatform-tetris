//
//  SinglePlayMode.cpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "SinglePlayMode.hpp"

#include "GameField.hpp"
#include "Player.hpp"
#include "Utils.hpp"

#include "UIGameOver.hpp"
#include "UIManager.hpp"

SinglePlayMode::SinglePlayMode()
:player(nullptr)
{
}

SinglePlayMode::~SinglePlayMode() {
    SafeDelete(player);
}

void SinglePlayMode::start() {
    player = new Player();
    player->setOriginCoordinates(vec2d(0, 0));
    player->setCallbackGameOver([=] () {
        auto uiGameOver = new UIGameOver(player->getScore(), [=]() {
            if (player == nullptr) {
                return;
            }
            player->getGameField()->clearField();
        });
        UIManager::get().addNewBaseUI(uiGameOver);
    });
}

void SinglePlayMode::pause(bool isPaused) {
    if (player == nullptr) {
        return;
    }
    player->setPauseGame(isPaused);
}

void SinglePlayMode::quit() {
    SafeDelete(player);
}

void SinglePlayMode::handleKeyboardInput(Keyboard::Types key) {
    switch (key) {
        case Keyboard::ESC:
            if (menuWindow == nullptr) {
                if (player->isPaused()) {
                    return;
                }
                openMenuWindow();
            } else {
                closeMenuWindow();
            }
            break;
    }
    
    player->handleKeyboardInput(key);
}
