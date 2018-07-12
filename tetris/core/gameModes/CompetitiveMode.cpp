//
//  CompetitiveMode.cpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "CompetitiveMode.hpp"

#include "Constants.hpp"
#include "IOInterface.hpp"
#include "PlayerAI.hpp"
#include "Utils.hpp"

CompetitiveMode::CompetitiveMode()
:player(nullptr)
{
}

CompetitiveMode::~CompetitiveMode() {
    SafeDelete(player);
    SafeDelete(aiPlayer);
}

void CompetitiveMode::start() {
    IOInterface::get().changeWindowSize(WINDOW_WIDTH_TWO_PLAYER, WINDOW_HEIGHT);
    player = new Player();
    aiPlayer = new PlayerAI();
    
    player->setOriginCoordinates(vec2d(0, 0));
    aiPlayer->setOriginCoordinates(vec2d(WINDOW_WIDTH, 0));
}

void CompetitiveMode::pause(bool isPaused) {
    if (player != nullptr) {
        player->setPauseGame(isPaused);
    }
    if (aiPlayer != nullptr) {
        aiPlayer->setPauseGame(isPaused);
    }
}

void CompetitiveMode::quit() {
    IOInterface::get().changeWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    SafeDelete(player);
    SafeDelete(aiPlayer);
}

void CompetitiveMode::handleKeyboardInput(Keyboard::Types key) {
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
    aiPlayer->handleKeyboardInput(key);
}
