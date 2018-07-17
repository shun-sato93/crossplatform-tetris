//
//  Drawer.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Drawer_hpp
#define Drawer_hpp

#include <vector>

#include "Singleton.hpp"

class Drawable;

/**
 * Drawing class that manages every drawable objects.
 * Singleton.
 */
class Drawer: public Singleton<Drawer> {
public:
    ~Drawer();
    /**
     * This function should be called from platform dependent drawing callback
     */
    void draw() const;
    
    /**
     * Automatically called when a drawable object is created. Don't call this function by yourself.
     */
    void registerDrawable(const Drawable* item);
    /**
     * Automatically called when a drawable object is deleted. Don't call this function by yourself.
     */
    void unregisterDrawable(const Drawable* item);
    
    /**
     * Sort drawables by zIndex order
     */
    void sortDrawables();
private:
    friend class Singleton<Drawer>;
    Drawer();
    
    std::vector<const Drawable*> items;
};

#endif /* Drawer_hpp */
