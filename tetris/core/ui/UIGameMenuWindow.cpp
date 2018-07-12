//
//  UIGameMenuWindow.cpp
//  tetris
//
//  Created by Shun Sato on 7/10/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIGameMenuWindow.hpp"

#include "Coordinates.hpp"
#include "GameContext.hpp"
#include "UIButton.hpp"
#include "UIView.hpp"

UIGameMenuWindow::UIGameMenuWindow()
:UIBaseView(100){
    className = "UIGameMenuWindow";
    setup();
}

UIGameMenuWindow::~UIGameMenuWindow()
{}

void UIGameMenuWindow::setup() {
    GameContext::get().setPauseGame(true);
    
    const int menuWindowWidth = 300;
    const int menuWindowHeight = 300;
    UIView* menuWindowView = new UIView(
                                    menuWindowWidth,
                                    menuWindowHeight,
                                    Color::GREY);
    menuWindowView->setAnchor(Anchor::CENTER);
    
    const int buttonWidth = 150;
    const int buttonHeight = 50;
    UIButton* resumeButton = new UIButton(
                                           buttonWidth,
                                           buttonHeight);
    resumeButton->setCoordinates(vec2d(0, 50), Anchor::CENTER);
    resumeButton->setTitle("Resume");
    resumeButton->setBackgroundColor(Color::WHITE);
    resumeButton->setEvent([=] () {
        GameContext::get().setPauseGame(false);
        close();
    });
    
    UIButton* backToTitleButton = new UIButton(
                                               buttonWidth,
                                               buttonHeight);
    backToTitleButton->setCoordinates(vec2d(0, -50), Anchor::CENTER);
    backToTitleButton->setTitle("Back to Title");
    backToTitleButton->setBackgroundColor(Color::WHITE);
    backToTitleButton->setEvent([=] () {
        close();
        GameContext::get().goTitle();
    });
    
    menuWindowView->addChild(resumeButton);
    menuWindowView->addChild(backToTitleButton);
    addChild(menuWindowView);
}

void UIGameMenuWindow::draw() const {
    UIView::draw();
}
