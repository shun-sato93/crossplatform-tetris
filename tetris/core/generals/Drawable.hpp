//
//  Drawable.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include "Hookable.hpp"

/**
 * Base class of drawable objects in the game.
 * Every objects that has draw function should inherit this class so that their draw functions will be automatically called by Drawer when it's needed.
 */
class Drawable {
public:
    Drawable();
    Drawable(int zIndex);
    virtual ~Drawable();
    
    /**
     * Draw function. Classes those inherits Drawable need to override.
     */
    virtual void draw() const = 0;
    
    bool isVisible() const;
    
    int getZIndex() const;
    virtual void setZIndex(int zIndex);
    
    // for sort comparison
    inline static bool zindexAscend(const Drawable* a, const Drawable* b){
        return (a->zIndex.get() < b->zIndex.get());
    }
protected:
    /** Drawing order. Smaller zindex means a drawable will be drawn earlier than others that have bigger zindex. */
    hookable<int> zIndex;
    /** Visibility flag. Updater won't call Drawable::draw() as long as this flag is false. */
    bool _isVisible;
};

#endif /* Drawable_hpp */
