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
    
    const Size menuWindowSize(300, 300);
    UIView* menuWindowView = new UIView(
                                    menuWindowSize,
                                    Color::GREY);
    menuWindowView->setAnchor(Anchor::CENTER);
    
    const Size buttonSize(150, 50);
    UIButton* resumeButton = new UIButton(buttonSize);
    resumeButton->setCoordinates(vec2d(0, 50), Anchor::CENTER);
    resumeButton->setTitle("Resume");
    resumeButton->setBackgroundColor(Color::WHITE);
    resumeButton->setEvent([=] () {
        GameContext::get().setPauseGame(false);
        close();
    });
    
    UIButton* backToTitleButton = new UIButton(buttonSize);
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
