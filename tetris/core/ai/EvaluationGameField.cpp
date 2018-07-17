//
//  EvaluationGameField.cpp
//  tetris
//
//  Created by Shun Sato on 7/6/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "EvaluationGameField.hpp"

#include <iostream>

#include "Block.hpp"
#include "Coordinates.hpp"
#include "GameField.hpp"
#include "Utils.hpp"
#include "Tile.hpp"

using namespace std;

struct BlockPlacingEvaluation {
    BlockPlacingEvaluation(int numRotate, const vec2n& deltaFromOrigin, double evaluation, int numBuriedSpaces)
    :numRotate(numRotate)
    ,deltaFromOrigin(deltaFromOrigin)
    ,evaluation(evaluation)
    ,numBuriedSpaces(numBuriedSpaces){}
    
    // copy constructor
    BlockPlacingEvaluation(const BlockPlacingEvaluation& a)
    :numRotate(a.numRotate)
    ,deltaFromOrigin(a.deltaFromOrigin)
    ,evaluation(a.evaluation)
    ,numBuriedSpaces(a.numBuriedSpaces){}
    
    int numRotate;
    vec2n deltaFromOrigin;
    // smaller is better
    double evaluation;
    int numBuriedSpaces;
    
    // for sort comparison
    inline static bool evaluationAscend(const BlockPlacingEvaluation& a, const BlockPlacingEvaluation& b) {
        return (a.evaluation < b.evaluation);
    }
};

void printTiles(const std::array<std::array<Tile*, FIELD_HEIGHT>, FIELD_WIDTH>& tiles) {
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=0; j<FIELD_HEIGHT; ++j) {
            std::cout << tiles[i][j]->getStatus();
        }
        std::cout << std::endl;
    }
}
void printBlock(const Block* block) {
    auto tiles = block->getTiles();
    for (int i=0; i<tiles.size(); ++i) {
        for (int j=0; j<tiles.front().size(); ++j) {
            std::cout << tiles[i][j]->getStatus();
        }
        std::cout << std::endl;
    }
}

EvaluationGameField::EvaluationGameField()
:block(new Block(nullptr))
{
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=0; j<FIELD_HEIGHT; ++j) {
            tiles[i][j] = new Tile(nullptr, i, j, Tile::EMPTY, Color::NONE, 1);
        }
    }
}

EvaluationGameField::~EvaluationGameField() {
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=0; j<FIELD_HEIGHT; ++j) {
            SafeDelete(tiles[i][j]);
        }
    }
    SafeDelete(block);
}

std::vector<PlayerAI::BlockOperation> EvaluationGameField::computeNextBlockOperations(const GameField* gameField) {
    std::vector<BlockPlacingEvaluation> evaluations;
    std::vector<PlayerAI::BlockOperation> operationQueue;
    
    copyGameField(gameField);
    
    auto currentSpacesEvaluation = getSpacesEvaluation();
    
    for (int numRotation=0; numRotation<4; ++numRotation) {
        copyGameField(gameField);
        for(int i=0; i<numRotation; ++i) {
            rotateBlock();
        }
        
        //        printBlock(block);
        //        printTiles(tiles);
        //        cout << "blockX:" << block->getCoordinates().x <<"blockY:" <<  block->getCoordinates().y << endl;
        
        // calculate left movable spaces and right movable spaces
        int leftSpace = 0, rightSpace = 0;
        while(true) {
            if (isBlockMovableTo(block, vec2n(leftSpace-1, 0))) {
                --leftSpace;
            } else {
                break;
            }
        }
        while(true) {
            if (isBlockMovableTo(block, vec2n(rightSpace+1, 0))) {
                ++rightSpace;
            } else {
                break;
            }
        }
        cout << "left:" << leftSpace << " right:" << rightSpace << endl;
        
        for (int x=leftSpace; x<=rightSpace; ++x) {
            // recopy original game field
            copyGameField(gameField);
            
            for(int i=0; i<numRotation; ++i) {
                rotateBlock();
            }
            block->moveBy(x, 0);
            int y = 0;
            while(isBlockMovableTo(block, vec2n(0, y - 1))) {
                y -= 1;
            }
            block->moveBy(0, y);
            fixBlock();
            
            //            printTiles(tiles);
            
            // evaluate current map
            int numCleared = clearLines();
            int highestHeight = getHighestHeight();
            SpacesEvaluation spacesEvaluation = getSpacesEvaluation();
            double evaluation = 1.0*highestHeight + 10.0*spacesEvaluation.numBuriedSpaces + 1.0*spacesEvaluation.distanceToBuriedSpaces - 3.0*numCleared + 0.3*y - 0.1*abs(x);
            
            cout << "x:" << x << " y:" << y << " numCleared:" << numCleared << " highestHeight:" << highestHeight << " numBeriedSpaces:" << spacesEvaluation.numBuriedSpaces << " distanceToBuriedSpaces:" << spacesEvaluation.distanceToBuriedSpaces << " evaluation:" << evaluation << endl << endl;
            evaluations.push_back(BlockPlacingEvaluation(numRotation, vec2n(x, y), evaluation, spacesEvaluation.numBuriedSpaces));
        }
    }
    
    if (evaluations.empty()) {
        // failed to create operation queue
        return operationQueue;
    }
    
    
    sort(evaluations.begin(), evaluations.end(), &BlockPlacingEvaluation::evaluationAscend);
    
    for (auto it=evaluations.begin(); it!=evaluations.end(); ++it) {
        cout << (*it).evaluation << " ";
    }
    cout << endl;
    
    // get finest placing
    auto bestPlacing = evaluations.front();
    
    if (bestPlacing.numBuriedSpaces > currentSpacesEvaluation.numBuriedSpaces) {
        cout << "new:" << bestPlacing.numBuriedSpaces <<  " current:" << currentSpacesEvaluation.numBuriedSpaces << endl;
    }
    
    for (int i=0; i<abs(bestPlacing.deltaFromOrigin.y); ++i) {
        operationQueue.push_back(PlayerAI::MOVE_DOWN);
    }
    
    for (int i=0; i<abs(bestPlacing.deltaFromOrigin.x); ++i) {
        if (bestPlacing.deltaFromOrigin.x < 0) {
            operationQueue.push_back(PlayerAI::MOVE_LEFT);
        } else {
            operationQueue.push_back(PlayerAI::MOVE_RIGHT);
        }
    }
    for (int i=0; i<bestPlacing.numRotate; ++i) {
        operationQueue.push_back(PlayerAI::ROTATE);
    }
    return operationQueue;
}

void EvaluationGameField::fixBlock() {
    auto blockTiles = block->getTiles();
    
    for (int i=0; i<blockTiles.size(); ++i) {
        for (int j=0; j<blockTiles.size(); ++j) {
            if (blockTiles[i][j]->getStatus() != Tile::FILLED) {
                continue;
            }
            auto coordinates = blockTiles[i][j]->getCoordinates();
            if (isInsideBound(coordinates)) {
                blockTiles[i][j]->copyColorAndStatus(tiles[coordinates.x][coordinates.y]);
            }
        }
    }
}
bool EvaluationGameField::isBlockMovableTo(const Block* block, const vec2n& delta) const {
    auto blockTiles = block->getTiles();
    
    for (int i=0; i<blockTiles.size(); ++i) {
        for (int j=0; j<blockTiles.size(); ++j) {
            if (blockTiles[i][j]->getStatus() != Tile::FILLED) {
                continue;
            }
            auto newCoordinates = blockTiles[i][j]->getCoordinates() + delta;
            if (!isInsideBound(newCoordinates) || tiles[newCoordinates.x][newCoordinates.y]->getStatus() == Tile::FILLED) {
                return false;
            }
        }
    }
    return true;
    
}
void EvaluationGameField::moveBlock(int x, int y) {
    if (isBlockMovableTo(block, vec2n(x, y))) {
        block->moveBy(x, y);
    }
    
}
void EvaluationGameField::rotateBlock() {
    if (block == nullptr) {
        return;
    }
    block->rotate([&] (const Block* block) {
        return isBlockMovableTo(block, vec2n());
    });
    
}
int EvaluationGameField::clearLines() {
    int numCleared = 0;
    for (int j=0; j<FIELD_HEIGHT; ++j) {
        bool isClearable = true;
        for (int i=0; i<FIELD_WIDTH; ++i) {
            if (tiles[i][j]->getStatus() != Tile::FILLED) {
                isClearable = false;
                break;
            }
        }
        
        if (isClearable) {
            ++numCleared;
            // move all the upper lines down by 1
            for (int k=j+1; k<FIELD_HEIGHT; ++k) {
                for (int h=0; h<FIELD_WIDTH; ++h) {
                    tiles[h][k]->copyColorAndStatus(tiles[h][k-1]);
                }
            }
            j -= 1;
        }
    }
    return numCleared;
}

void EvaluationGameField::clearField() {
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=0; j<FIELD_HEIGHT; ++j) {
            tiles[i][j]->setStatus(Tile::EMPTY);
        }
    }
}

void EvaluationGameField::copyGameField(const GameField* gameField) {
    auto originalBlock = gameField->getBlock();
    block->copy(originalBlock);
    auto originalTiles = gameField->getTiles();
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=0; j<FIELD_HEIGHT; ++j) {
            originalTiles[i][j]->copyColorAndStatus(tiles[i][j]);
        }
    }
}

int EvaluationGameField::getHighestHeight() const {
    int highest = 0;
    
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=FIELD_HEIGHT-1; j>=0; --j) {
            if (tiles[i][j]->getStatus() == Tile::FILLED) {
                if (j+1 > highest) {
                    highest = j+1;
                }
                break;
            }
        }
    }
    
    return highest;
}

EvaluationGameField::SpacesEvaluation EvaluationGameField::getSpacesEvaluation() const {
    SpacesEvaluation spacesEvaluation;
    
    for (int i=0; i<FIELD_WIDTH; ++i) {
        bool startCounting = false;
        int buriedSpacesCounter = 0;
        int distanceToBeriedSpaceCounter = 0;
        for (int j=FIELD_HEIGHT-1; j>=0; --j) {
            if (tiles[i][j]->getStatus() == Tile::FILLED) {
                startCounting = true;
                if (buriedSpacesCounter == 0) {
                    ++distanceToBeriedSpaceCounter;
                }
            } else if (startCounting) {
                ++buriedSpacesCounter;
            }
            if (buriedSpacesCounter > 0) {
                spacesEvaluation.distanceToBuriedSpaces += distanceToBeriedSpaceCounter;
            }
            spacesEvaluation.numBuriedSpaces += buriedSpacesCounter;
        }
    }
    
    return spacesEvaluation;
}

const int testArray[FIELD_WIDTH][FIELD_HEIGHT] = {
    {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

void EvaluationGameField::test() {
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=0; j<FIELD_HEIGHT; ++j) {
            if (testArray[i][j] == 1) {
                tiles[i][j]->setStatus(Tile::FILLED);
            } else {
                tiles[i][j]->setStatus(Tile::EMPTY);
            }
        }
    }
    printTiles(tiles);
    
    SpacesEvaluation spacesEvaluation = getSpacesEvaluation();
    cout << "test " << "highestHeight:" << getHighestHeight() << " numBeriedSpaces:" << spacesEvaluation.numBuriedSpaces << " distanceToBuriedSpaces:" << spacesEvaluation.distanceToBuriedSpaces << endl;
}

