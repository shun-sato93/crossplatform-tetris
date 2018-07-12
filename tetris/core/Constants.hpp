//
//  Constants.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Constants_hpp
#define Constants_hpp

/**
 * Constants.hpp defines constant global variables.
 */

const int WINDOW_WIDTH = 520;
const int WINDOW_HEIGHT = 690;
const int WINDOW_WIDTH_TWO_PLAYER = WINDOW_WIDTH * 2;

const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 28;
// Height of invisible top area outside of window.
const int FIELD_INVISIBLE_TOP_OFFSET = 7;

// Size of tile.
const int TILE_SIZE = 30;
// Interval size of tiles.
const int TILE_OFFSET = 2;

// The interval of a block movement in milisecond. smaller = faster
const int BLOCK_SPEED = 200;


#endif /* Constants_hpp */
