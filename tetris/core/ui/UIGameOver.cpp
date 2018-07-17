//
//  UIGameOver.cpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIGameOver.hpp"

#include "Coordinates.hpp"
#include "GameContext.hpp"
#include "UIButton.hpp"
#include "UILabel.hpp"


UIGameOver::UIGameOver(int score, std::function<void(void)> retryDelegate)
:UIBaseView(100)
,retryDelegate(retryDelegate)
,score(score)
{
    className = "UIGameOver";
    
    setup();
}

UIGameOver::~UIGameOver() {
    
}

void UIGameOver::setup() {
    GameContext::get().setPauseGame(true);
    
    const int menuWindowWidth = 300;
    const int menuWindowHeight = 300;
    
    auto menuWindowView = new UIView(
                                        Size(menuWindowWidth, menuWindowHeight),
                                        Color::GREY);
    menuWindowView->setAnchor(Anchor::CENTER);
    
    
    auto gameOverLabel = new UILabel(
                                     "GAME OVER",
                                     Color::_1);
    gameOverLabel->setCoordinates(vec2d(0, -10), Anchor::UPPER_CENTER);
    
    auto scoreLabel = new UILabel(
                                     "SCORE:" + std::to_string(score),
                                     Color::_1);
    scoreLabel->setCoordinates(vec2d(0, -40), Anchor::UPPER_CENTER);
                                     
    
    const int buttonWidth = 150;
    const int buttonHeight = 50;
    auto resumeButton = new UIButton(Size(buttonWidth, buttonHeight));
    resumeButton->setTitle("Retry");
    resumeButton->setCoordinates(vec2d(0, 50), Anchor::CENTER);
    resumeButton->setBackgroundColor(Color::WHITE);
    resumeButton->setEvent([=] () {
        GameContext::get().setPauseGame(false);
        if (retryDelegate) {
            retryDelegate();
        }
        close();
    });
    
    auto backToTitleButton = new UIButton(Size(buttonWidth, buttonHeight));
    backToTitleButton->setTitle("Back to Title");
    backToTitleButton->setCoordinates(vec2d(0, -50), Anchor::CENTER);
    backToTitleButton->setBackgroundColor(Color::WHITE);
    backToTitleButton->setEvent([=] () {
        GameContext::get().goTitle();
        close();
    });
    
    menuWindowView->addChild(gameOverLabel);
    menuWindowView->addChild(scoreLabel);
    menuWindowView->addChild(resumeButton);
    menuWindowView->addChild(backToTitleButton);
    addChild(menuWindowView);
}

void UIGameOver::draw() const {
    
}
