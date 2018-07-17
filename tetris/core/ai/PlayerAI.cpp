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

using namespace std;


const int OPERATION_SPEED = 1;

PlayerAI::PlayerAI()
:lastBlockOperationMS(now_ms())
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
    if (!operationQueue.empty() && now_ms() - lastBlockOperationMS > OPERATION_SPEED) {
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
        lastBlockOperationMS = now_ms();
    }
}

void PlayerAI::handleKeyboardInput(Keyboard::Types key) {
    
}
