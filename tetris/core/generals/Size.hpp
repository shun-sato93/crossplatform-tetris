//
//  Size.hpp
//  tetris
//
//  Created by Shun Sato on 7/11/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Size_hpp
#define Size_hpp

/**
 * Simple 2 dimentional size definition of everything.
 */
struct Size {
    Size(int width, int height)
    :width(width)
    ,height(height)
    {}
    
    Size()
    :width(0)
    ,height(0)
    {}
    
    int width;
    int height;
};

#endif /* Size_hpp */
