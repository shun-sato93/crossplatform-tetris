//
//  AIDemoMode.cpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "AIDemoMode.hpp"

#include "GameField.hpp"
#include "PlayerAI.hpp"
#include "UIGameOver.hpp"
#include "UIManager.hpp"
#include "Utils.hpp"

AIDemoMode::AIDemoMode()
:player(nullptr)
{
}

AIDemoMode::~AIDemoMode() {
    SafeDelete(player);
}

void AIDemoMode::start() {
    player = new PlayerAI();
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

void AIDemoMode::pause(bool isPaused) {
    if (player == nullptr) {
        return;
    }
    player->setPauseGame(isPaused);
}

void AIDemoMode::quit() {
    SafeDelete(player);
}

void AIDemoMode::handleKeyboardInput(Keyboard::Types key) {
    switch (key) {
        case Keyboard::ESC:
            if (menuWindow == nullptr) {
                openMenuWindow();
            } else {
                closeMenuWindow();
            }
            break;
    }
    
    player->handleKeyboardInput(key);
}
