//
//  PlayerAI.hpp
//  tetris
//
//  Created by Shun Sato on 7/5/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef PlayerAI_hpp
#define PlayerAI_hpp

#include <vector>

#include "Player.hpp"

class EvaluationGameField;

/**
 * Player subclass which represents AI.
 */
class PlayerAI: public Player  {
public:
    enum BlockOperation {
        ROTATE,
        MOVE_RIGHT,
        MOVE_LEFT,
        MOVE_DOWN
    };
    
    PlayerAI();
    ~PlayerAI();
    
    void update() override;
    void handleKeyboardInput(Keyboard::Types key) override;
private:
    /** Last time of block operation in miliseconds  */
    double lastBlockOperationMS;
    /** Block operations */
    std::vector<BlockOperation> operationQueue;
    /** A game field to evaluate next block operation. */
    EvaluationGameField* evaluationGameField;
};

#endif /* PlayerAI_hpp */
