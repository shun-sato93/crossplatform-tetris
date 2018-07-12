//
//  SinglePlayMode.hpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef SinglePlayMode_hpp
#define SinglePlayMode_hpp

#include "GameMode.hpp"

class Player;

class SinglePlayMode: public GameMode {
public:
    SinglePlayMode();
    ~SinglePlayMode();
    
    void start() override;
    void pause(bool isPaused) override;
    void quit() override;
    void handleKeyboardInput(Keyboard::Types key) override;
private:
    
    Player* player;
};

#endif /* SinglePlayMode_hpp */
