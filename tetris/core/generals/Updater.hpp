//
//  Updater.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Updater_hpp
#define Updater_hpp

#include <vector>
#include "Singleton.hpp"

class Updatable;

/**
 * Updating class that manages every updatable objects.
 * Singleton.
 */
class Updater: public Singleton<Updater> {
public:
    ~Updater();
    
    /**
     * This function should be called from platform dependent update callback
     */
    void update(bool isContinuing);
    
    /**
     * Automatically called when a updatable object is created. Don't call this function by yourself.
     */
    void registerUpdatable(Updatable* item);
    /**
     * Automatically called when a updatable object is deleted. Don't call this function by yourself.
     */
    void unregisterUpdatable(Updatable* item);
    
private:
    friend class Singleton<Updater>;
    Updater();
    
    std::vector<Updatable*> items;
    bool hasNumberOfRegisteredItemsChanged;
};

#endif /* Updater_hpp */
