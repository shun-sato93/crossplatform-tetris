//
//  GameField.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "GameField.hpp"

#include <vector>

#include "Block.hpp"
#include "ColorDefinition.hpp"
#include "Constants.hpp"
#include "Coordinates.hpp"
#include "Drawer.hpp"
#include "IOInterface.hpp"
#include "Utils.hpp"
#include "Tile.hpp"
#include "Time.hpp"

using namespace std;

GameField::GameField()
:originCoordinates(0, 0)
,block(new Block(this))
,lastBlockFallenMS(Time::now_ms())
{
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=0; j<FIELD_HEIGHT; ++j) {
            tiles[i][j] = new Tile(this, i, j, Tile::EMPTY, Color::NONE, 1);
        }
    }
    block->setupNewBlockAtOriginalPosition();
}

GameField::~GameField() {
    for (auto it=tiles.begin(); it!=tiles.end(); ++it) {
        for (auto secondIt=(*it).begin(); secondIt!=(*it).end(); ++secondIt) {
            SafeDelete(*secondIt);
        }
    }
    SafeDelete(block);
}

void GameField::draw() const {
    auto fieldSizeInPoint = getVisibleFieldSizeInPoint();
    IOInterface::drawRectangle(
                                     originCoordinates.x,
                                     originCoordinates.y,
                                     fieldSizeInPoint.x,
                                     fieldSizeInPoint.y,
                                     Color::BLACK);
}

void GameField::update() {
    auto currentMS = Time::now_ms();
    if (block != nullptr && (currentMS - lastBlockFallenMS > BLOCK_SPEED)) {
        if (isBlockMovableTo(block, vec2n(0, -1))) {
            block->moveBy(0, -1);
        } else {
            fixBlock();
            clearLines();
        }
        lastBlockFallenMS = currentMS;
    }
}

void GameField::fixBlock() {
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
    
    block->setupNewBlockAtOriginalPosition();
    
    if (callbackNewBlockAdded) {
        callbackNewBlockAdded();
    }
    if (!isBlockMovableTo(block, vec2n(0, -1))) {
        // game over
        if (callbackGameOver) {
            callbackGameOver();
        }
    }
}

void GameField::clearField() {
    for (int i=0; i<FIELD_WIDTH; ++i) {
        for (int j=0; j<FIELD_HEIGHT; ++j) {
            tiles[i][j]->setStatus(Tile::EMPTY);
        }
    }
}

bool GameField::isBlockMovableTo(const Block* block, const vec2n& delta) const {
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

void GameField::moveBlock(int x, int y) {
    if (isBlockMovableTo(block, vec2n(x, y))) {
        block->moveBy(x, y);
    }
}

void GameField::rotateBlock() {
    if (block == nullptr) {
        return;
    }
    block->rotate([&] (const Block* block) {
        return isBlockMovableTo(block, vec2n());
    });
}

void GameField::clearLines() {
    for (int j=0; j<FIELD_HEIGHT; ++j) {
        bool isClearable = true;
        for (int i=0; i<FIELD_WIDTH; ++i) {
            if (tiles[i][j]->getStatus() != Tile::FILLED) {
                isClearable = false;
                break;
            }
        }
        
        if (isClearable) {
            // move all the upper lines down by 1
            for (int k=j+1; k<FIELD_HEIGHT; ++k) {
                for (int h=0; h<FIELD_WIDTH; ++h) {
                    tiles[h][k]->copyColorAndStatus(tiles[h][k-1]);
                }
            }
            j -= 1;
            if (callbackLineCleared) {
                callbackLineCleared(FIELD_WIDTH);
            }
        }
    }
}

void GameField::setCallbackLineCleared(std::function<void(int)> callback) {
    callbackLineCleared = callback;
}
void GameField::setCallbackGameOver(std::function<void(void)> callback) {
    callbackGameOver = callback;
}
void GameField::setCallbackNewBlockAdded(std::function<void(void)> callback) {
    callbackNewBlockAdded = callback;
}

const vec2d& GameField::getOriginCoordinates() const {
    return originCoordinates;
}

const std::array<std::array<Tile*, FIELD_HEIGHT>, FIELD_WIDTH>& GameField::getTiles() const {
    return tiles;
}

const Block* GameField::getBlock() const {
    return block;
}

void GameField::setOriginCoordinates(const vec2d& coordinates) {
    originCoordinates = coordinates;
}
