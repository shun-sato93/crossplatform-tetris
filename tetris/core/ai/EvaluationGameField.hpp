//
//  EvaluationGameField.hpp
//  tetris
//
//  Created by Shun Sato on 7/6/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef EvaluationGameField_hpp
#define EvaluationGameField_hpp

#include <array>
#include <vector>

#include "Constants.hpp"
#include "Vector2d.hpp"
#include "PlayerAI.hpp"

class Block;
class GameField;
class Tile;

/**
 * Game field for ai evaluation.
 */
class EvaluationGameField {
public:
    EvaluationGameField();
    ~EvaluationGameField();
    
    std::vector<PlayerAI::BlockOperation> computeNextBlockOperations(const GameField* gameField);
    
private:
    struct SpacesEvaluation {
        int numBuriedSpaces = 0;
        int distanceToBuriedSpaces = 0;
    };
    
    void fixBlock();
    bool isBlockMovableTo(const Block* block, const vec2n& delta) const;
    void moveBlock(int x, int y);
    void rotateBlock();
    int clearLines();
    void clearField();
    void copyGameField(const GameField* gameField);
    int getHighestHeight() const;
    SpacesEvaluation getSpacesEvaluation() const;
    
    void test();
    
    std::vector<PlayerAI::BlockOperation> operationQueue;
    
    const vec2d originCoordinates;
    Block* block;
    std::array<std::array<Tile*, FIELD_HEIGHT>, FIELD_WIDTH> tiles;
};

#endif /* EvaluationGameField_hpp */
