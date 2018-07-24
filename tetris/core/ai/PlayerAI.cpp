//
//  PlayerAI.cpp
//  tetris
//
//  Created by Shun Sato on 7/5/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "PlayerAI.hpp"

#include "GameField.hpp"
#include "EvaluationGameField.hpp"
#include "Utils.hpp"
#include "Time.hpp"

using namespace std;


const int OPERATION_SPEED = 1;

PlayerAI::PlayerAI()
:lastBlockOperationMS(Time::now_ms())
,evaluationGameField(new EvaluationGameField())
{
    gameField->setCallbackNewBlockAdded([=] () {
        operationQueue = evaluationGameField->computeNextBlockOperations(gameField);
    });
    
    operationQueue = evaluationGameField->computeNextBlockOperations(gameField);
}

PlayerAI::~PlayerAI() {
    SafeDelete(evaluationGameField);
}

void PlayerAI::update() {
    double currentMS = Time::now_ms();
    if (!operationQueue.empty() && currentMS - lastBlockOperationMS > OPERATION_SPEED) {
        auto nextOperation = operationQueue.back();
        switch(nextOperation) {
            case ROTATE:
                gameField->rotateBlock();
                break;
            case MOVE_LEFT:
                gameField->moveBlock(-1, 0);
                break;
            case MOVE_RIGHT:
                gameField->moveBlock(1, 0);
                break;
            case MOVE_DOWN:
                gameField->moveBlock(0, -1);
                break;
        }
        operationQueue.pop_back();
        lastBlockOperationMS = currentMS;
    }
}

void PlayerAI::handleKeyboardInput(Keyboard::Types key) {
    
}
