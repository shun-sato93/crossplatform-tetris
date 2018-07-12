//
//  Block.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "Block.hpp"

#include <algorithm>
#include <random>

#include "Constants.hpp"
#include "Random.hpp"
#include "Tile.hpp"
#include "Utils.hpp"

const int BLOCK_WIDTH = 5;

const int BLOCK_TYPES[][BLOCK_WIDTH][BLOCK_WIDTH] = {
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
    },
};

Block::Block(GameField* gameField) {
    tiles.resize(BLOCK_WIDTH);
    for (int i=0; i<tiles.size(); ++i) {
        tiles[i].resize(BLOCK_WIDTH);
    }
    for (int i=0; i<BLOCK_WIDTH; ++i) {
        for (int j=0; j<BLOCK_WIDTH; ++j) {
            tiles[i][j] = new Tile(gameField, coordinates.x+i, coordinates.y+j, Tile::EMPTY, Color::Types::NONE, 2);
        }
    }
}

Block::~Block() {
    for (auto it=tiles.begin(); it!=tiles.end(); ++it) {
        for(auto secondIt=it->begin(); secondIt!=it->end(); ++secondIt) {
            SafeDelete(*secondIt);
        }
    }
}

void Block::setupNewBlockAtOriginalPosition() {
    coordinates.set(FIELD_WIDTH / 2 - 3, FIELD_HEIGHT-BLOCK_WIDTH);
    updateTileCoordinates();
    Color::Types randomColor = Color::getRandomColor();
    
    static auto randomEngine = std::default_random_engine {};
    if (blockTypeIndices.empty()) {
        int numBlockTypes = sizeof(BLOCK_TYPES) / sizeof(BLOCK_TYPES[0]);
        for (int i=0; i<numBlockTypes; ++i) {
            blockTypeIndices.push_back(i);
        }
        std::shuffle(blockTypeIndices.begin(), blockTypeIndices.end(), randomEngine);
    }
    int nextBlockIndex = blockTypeIndices.back();
    blockTypeIndices.pop_back();
    
    for (int i=0; i<tiles.size(); ++i) {
        for (int j=0; j<tiles.front().size(); ++j) {
            tiles[i][j]->setColor(randomColor);
            if (BLOCK_TYPES[nextBlockIndex][i][j] == 0) {
                tiles[i][j]->setStatus(Tile::EMPTY);
            } else {
                tiles[i][j]->setStatus(Tile::FILLED);
            }
        }
    }
}

void Block::rotate(std::function<bool(const Block*)> checkMovable) {
    Tile::TileStatus tempTileStatus[BLOCK_WIDTH][BLOCK_WIDTH];
    
    for (int i = 0; i < BLOCK_WIDTH; ++i) {
        for (int j = 0; j < BLOCK_WIDTH; ++j) {
            tempTileStatus[i][j] = tiles[i][j]->getStatus();
        }
    }
    for (int i = 0; i < BLOCK_WIDTH; ++i) {
        for (int j = 0; j < BLOCK_WIDTH; ++j) {
            tiles[i][j]->setStatus(tempTileStatus[BLOCK_WIDTH - j - 1][i]);
        }
    }
    if (!checkMovable(this)) {
        for (int i = 0; i < BLOCK_WIDTH; ++i) {
            for (int j = 0; j < BLOCK_WIDTH; ++j) {
                tiles[i][j]->setStatus(tempTileStatus[i][j]);
            }
        }
    }
}

void Block::moveBy(int x, int y) {
    coordinates.x += x;
    coordinates.y += y;
    updateTileCoordinates();
}

void Block::updateTileCoordinates() {
    for (int i=0; i<tiles.size(); ++i) {
        for (int j=0; j<tiles.front().size(); ++j) {
            tiles[i][j]->setCoordinates(vec2n(coordinates.x+i, coordinates.y+j));
        }
    }
}

void Block::setCoordinates(const vec2n& coordinates) {
    this->coordinates = coordinates;
}

const vec2n& Block::getCoordinates() const {
    return coordinates;
}

const std::vector<std::vector<Tile*>>& Block::getTiles() const {
    return tiles;
}

const int Block::getSize() const {
    return BLOCK_WIDTH;
}

void Block::copy(const Block* block) {
    coordinates = block->getCoordinates();
    for (int i=0; i<tiles.size(); ++i) {
        for (int j=0; j<tiles.front().size(); ++j) {
            auto tile = block->getTiles()[i][j];
            tile->copyColorAndStatus(tiles[i][j]);
            tiles[i][j]->setCoordinates(tile->getCoordinates());
        }
    }
}
