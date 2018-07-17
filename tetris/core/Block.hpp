//
//  Block.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <vector>
#include "Vector2d.hpp"
#include <functional>

class GameField;
class Tile;

/**
 * Falling block class.
 */
class Block {
public:
    Block(GameField* gameField);
    ~Block();
    
    void setupNewBlockAtOriginalPosition();
    void moveBy(int x, int y);
    void rotate(std::function<bool(const Block*)> checkMovable);
    void setCoordinates(const vec2n& coordinates);
    const vec2n& getCoordinates() const;
    const std::vector<std::vector<Tile*>>& getTiles() const;
    const int getSize() const;
    
    void copy(const Block* block);
private:
    void updateTileCoordinates();
    
    vec2n coordinates;
    std::vector<int> blockTypeIndices;
    std::vector<std::vector<Tile*>> tiles;
};

#endif /* Block_hpp */
