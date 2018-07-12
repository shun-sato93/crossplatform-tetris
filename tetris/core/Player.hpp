//
//  Player.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <functional>

#include "Hookable.hpp"
#include "Keyboard.hpp"
#include "Vector2d.hpp"
#include "Updatable.hpp"

class GameField;
class UIFieldBackground;

class Player: public Updatable {
public:
    Player();
    virtual ~Player();
    
    virtual void update() override;
    virtual void handleKeyboardInput(Keyboard::Types key);
    
    void setOriginCoordinates(const vec2d& coordinates);
    void setCallbackGameOver(std::function<void(void)> callbackGameOver);
    GameField* getGameField();
    void setPauseGame(bool isPaused);
    int getScore() const;
protected:
    std::function<void(void)> callbackGameOver;
    GameField* gameField;
    UIFieldBackground* uiFieldBackground;
    hookable<int> score;
    hookable<int> highscore;
};

#endif /* Player_hpp */
