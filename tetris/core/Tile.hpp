//
//  Tile.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include "Drawable.hpp"
#include "Vector2d.hpp"
#include "ColorDefinition.hpp"

class Drawable;
class GameField;

class Tile: Drawable {
public:
    enum TileStatus {
        EMPTY,
        FILLED,
    };
    
    Tile(GameField* gameField, int tileX, int tileY, TileStatus tileStatus, Color::Types color);
    Tile(GameField* gameField, int tileX, int tileY, TileStatus tileStatus, Color::Types color, int zindex);
    virtual ~Tile();
    
    void draw() const override;
    void setStatus(TileStatus tileStatus);
    TileStatus getStatus() const;
    void setColor(Color::Types color);
    Color::Types getColor() const;
    void setCoordinates(const vec2n& tileCoordinates);
    void copyColorAndStatus(Tile* destination) const;
    const vec2n& getCoordinates() const;
    
private:
    TileStatus tileStatus = EMPTY;
    vec2n coordinates;
    Color::Types color;
    GameField* gameField;
};

#endif /* Tile_hpp */
