//
//  GameField.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef GameField_hpp
#define GameField_hpp

#include <functional>
#include <array>

#include "Updatable.hpp"
#include "Drawable.hpp"
#include "Constants.hpp"
#include "Vector2d.hpp"

class Tile;
class Block;

class GameField: Drawable, public Updatable {
public:
    GameField();
    ~GameField();
    
    void draw() const override;
    void update() override;
    void moveBlock(int x, int y);
    void rotateBlock();
    void setCallbackLineCleared(std::function<void(int)> callback);
    void setCallbackGameOver(std::function<void(void)> callback);
    void setCallbackNewBlockAdded(std::function<void(void)> callback);
    const vec2d& getOriginCoordinates() const;
    void setOriginCoordinates(const vec2d& coordinates);
    const std::array<std::array<Tile*, FIELD_HEIGHT>, FIELD_WIDTH>& getTiles() const;
    const Block* getBlock() const;
    void clearField();
private:
    void fixBlock();
    bool isBlockMovableTo(const Block* block, const vec2n& delta) const;
    void clearLines();
    
    vec2d originCoordinates;
    Block* block;
    std::array<std::array<Tile*, FIELD_HEIGHT>, FIELD_WIDTH> tiles;
    double lastBlockFallenMS;
    // callback
    std::function<void(int)> callbackLineCleared;
    std::function<void(void)> callbackGameOver;
    std::function<void(void)> callbackNewBlockAdded;
};

#endif /* GameField_hpp */
