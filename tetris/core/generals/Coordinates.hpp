//
//  Coordinates.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Coordinates_hpp
#define Coordinates_hpp

#include "Constants.hpp"
#include "Size.hpp"
#include "Vector2d.hpp"

/**
 * Coordinates.hpp defines functions that are related to coordinates and window size calculation.
 */

inline vec2d tileToPoint(const vec2n& tileCoordinates){
    return vec2d(
                 tileCoordinates.x * (TILE_SIZE + TILE_OFFSET),
                 tileCoordinates.y * (TILE_SIZE + TILE_OFFSET));
}

inline bool isInsideBound(const vec2n& tileCoordinates) {
    return 0 <= tileCoordinates.x && tileCoordinates.x < FIELD_WIDTH
            && 0 <= tileCoordinates.y && tileCoordinates.y < FIELD_HEIGHT;
}

inline vec2d getFieldSizeInPoint() {
    return vec2d(
                 FIELD_WIDTH * (TILE_SIZE + TILE_OFFSET) - TILE_OFFSET,
                 FIELD_HEIGHT * (TILE_SIZE + TILE_OFFSET) - TILE_OFFSET);
}

inline vec2d getVisibleFieldSizeInPoint() {
    return vec2d(
                 FIELD_WIDTH * (TILE_SIZE + TILE_OFFSET) - TILE_OFFSET,
                 (FIELD_HEIGHT - FIELD_INVISIBLE_TOP_OFFSET) * (TILE_SIZE + TILE_OFFSET) - TILE_OFFSET);
}

inline Size getWindowSize() {
    return Size(WINDOW_WIDTH, WINDOW_HEIGHT);
}

#endif /* Coordinates_hpp */
