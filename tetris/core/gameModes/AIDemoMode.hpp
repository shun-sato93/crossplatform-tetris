//
//  AIDemoMode.hpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef AIDemoMode_hpp
#define AIDemoMode_hpp

#include "GameMode.hpp"

class Player;

class AIDemoMode: public GameMode {
public:
    AIDemoMode();
    ~AIDemoMode();
    
    void start() override;
    void pause(bool isPaused) override;
    void quit() override;
    void handleKeyboardInput(Keyboard::Types key) override;
private:
    Player* player;
};


#endif /* AIDemoMode_hpp */
