//
//  Utils.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

/**
 * Utils.hpp defines utility functions that are used from entire project.
 */

/**
 * Delete pointers. Use this function instead of delete to avoid deleting same pointers twice.
 */
template<class T>
static inline void SafeDelete( T*& p ){
    delete (p);
    (p) = nullptr;
}


#endif /* Utils_hpp */
