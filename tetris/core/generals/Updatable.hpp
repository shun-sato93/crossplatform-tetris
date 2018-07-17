//
//  Updatable.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Updatable_hpp
#define Updatable_hpp

/**
 * Base class of updatable objects in the game.
 * Every objects that has update function should inherit this class so that their update functions will be automatically called by Updater when it's needed.
 */
class Updatable {
public:
    Updatable();
    virtual ~Updatable();
    
    /**
     * Update function. Classes those inherits Updatable need to override.
     */
    virtual void update() = 0;
    
    void setHasUpdatedInThisFrame(bool hasUpdatedInThisFrame);
    bool hasUpdatedInThisFrame() const;
    
    void setPause(bool isPaused);
    bool isPaused() const;
private:
    bool _hasUpdatedInThisFrame;
    bool _isPaused;
};


#endif /* Updatable_hpp */
