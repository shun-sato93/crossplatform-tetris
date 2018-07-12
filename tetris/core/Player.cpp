//
//  Player.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "Player.hpp"

#include "GameField.hpp"
#include "UIManager.hpp"
#include "UIFieldBackground.hpp"
#include "Utils.hpp"

Player::Player()
:gameField(new GameField())
,score(0)
,highscore(0)
{
    uiFieldBackground = new UIFieldBackground();
    UIManager::get().addNewBaseUI(uiFieldBackground);
    
    gameField->setCallbackLineCleared([=](int numCleared) {
        score = score.get() + numCleared;
        uiFieldBackground->setScore(score.get());
    });
    gameField->setCallbackGameOver([=]() {
        if (score.get() > highscore.get()) {
            highscore = score;
        }
        uiFieldBackground->setHighscore(highscore.get());

        if (callbackGameOver) {
            callbackGameOver();
        }
        
        score = 0;
        uiFieldBackground->setScore(score.get());
    });
}

Player::~Player() {
    uiFieldBackground->close();
    SafeDelete(gameField);
}

void Player::update() {
    
}

GameField* Player::getGameField() {
    return gameField;
}

void Player::setPauseGame(bool isPaused) {
    setPause(isPaused);
    gameField->setPause(isPaused);
}

void Player::handleKeyboardInput(Keyboard::Types key) {
    switch (key) {
        case Keyboard::UP:
            break;
        case Keyboard::DOWN:
            gameField->moveBlock(0, -1);
            break;
        case Keyboard::LEFT:
            gameField->moveBlock(-1, 0);
            break;
        case Keyboard::RIGHT:
            gameField->moveBlock(1, 0);
            break;
        case Keyboard::SPACE:
            gameField->rotateBlock();
            break;
    }
}

void Player::setOriginCoordinates(const vec2d& coordinates) {
    gameField->setOriginCoordinates(vec2d(coordinates.x + 180, coordinates.y + 10));
    uiFieldBackground->setCoordinates(coordinates);
}

void Player::setCallbackGameOver(std::function<void(void)> callbackGameOver) {
    this->callbackGameOver = callbackGameOver;
}

int Player::getScore() const {
    return score.get();
}
