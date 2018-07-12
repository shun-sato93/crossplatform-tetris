//
//  CompetitiveMode.hpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef CompetitiveMode_hpp
#define CompetitiveMode_hpp


#include "GameMode.hpp"

class Player;

class CompetitiveMode: public GameMode {
public:
    CompetitiveMode();
    ~CompetitiveMode();
    
    void start() override;
    void pause(bool isPaused) override;
    void quit() override;
    void handleKeyboardInput(Keyboard::Types key) override;
private:
    
    Player* player;
    Player* aiPlayer;
};

#endif /* CompetitiveMode_hpp */
