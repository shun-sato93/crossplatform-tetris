//
//  Tile.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "Tile.hpp"

#include "Coordinates.hpp"
#include "GameField.hpp"
#include "IOInterface.hpp"

Tile::Tile(GameField* gameField, int tileX, int tileY, TileStatus tileStatus, Color::Types color)
:Drawable(0)
,gameField(gameField)
,coordinates(tileX, tileY)
,tileStatus(tileStatus)
,color(color)
{}

Tile::Tile(GameField* gameField, int tileX, int tileY, TileStatus tileStatus, Color::Types color, int zindex)
:Drawable(zindex)
,gameField(gameField)
,coordinates(tileX, tileY)
,tileStatus(tileStatus)
,color(color)
{}

Tile::~Tile() {
}

void Tile::draw() const {
    if (tileStatus == Tile::EMPTY) {
        return;
    }
    if (gameField == nullptr) {
        return;
    }
    vec2d point = tileToPoint(coordinates);
    const vec2d& originCoordinates = gameField->getOriginCoordinates();
    point += originCoordinates;
    IOInterface::get().drawRectangle(
                                     point.x,
                                     point.y,
                                     TILE_SIZE,
                                     TILE_SIZE,
                                     color);
}

void Tile::setStatus(TileStatus tileStatus) {
    this->tileStatus = tileStatus;
}

Tile::TileStatus Tile::getStatus() const {
    return tileStatus;
}

void Tile::setColor(Color::Types color) {
    this->color = color;
}

Color::Types Tile::getColor() const {
    return color;
}

void Tile::copyColorAndStatus(Tile* destination) const {
    if (destination == nullptr) {
        return;
    }
    destination->setStatus(tileStatus);
    destination->setColor(color);
}

void Tile::setCoordinates(const vec2n& tileCoordinates) {
    coordinates = tileCoordinates;
}

const vec2n& Tile::getCoordinates() const {
    return coordinates;
}
