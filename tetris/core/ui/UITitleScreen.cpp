//
//  UITitleScreen.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UITitleScreen.hpp"

#include "AIDemoMode.hpp"
#include "Coordinates.hpp"
#include "CompetitiveMode.hpp"
#include "GameContext.hpp"
#include "SinglePlayMode.hpp"
#include "UIButton.hpp"

UITitleScreen::UITitleScreen()
:UIBaseView(0)
{
    className = "UITitleScreen";
    setup();
}

UITitleScreen::~UITitleScreen()
{}

void UITitleScreen::setup() {
    color = Color::WHITE;
    
    const Size buttonSize(150, 50);
    UIButton* startPlayerButton = new UIButton(buttonSize);
    startPlayerButton->setCoordinates(vec2d(0, 100), Anchor::CENTER);
    startPlayerButton->setTitle("Single Play");
    startPlayerButton->setBackgroundColor(Color::GREY);
    startPlayerButton->setEvent([=] () {
        GameContext::get().startGame(new SinglePlayMode());
        close();
    });
    
    UIButton* watchAIDemoButton = new UIButton(buttonSize);
    watchAIDemoButton->setCoordinates(vec2d(0, 0), Anchor::CENTER);
    watchAIDemoButton->setTitle("Watch AI Demo");
    watchAIDemoButton->setBackgroundColor(Color::GREY);
    watchAIDemoButton->setEvent([=] () {
        GameContext::get().startGame(new AIDemoMode());
        close();
    });
    
    UIButton* competitiveButton = new UIButton(buttonSize);
    competitiveButton->setCoordinates(vec2d(0, -100), Anchor::CENTER);
    competitiveButton->setTitle("VS AI");
    competitiveButton->setBackgroundColor(Color::GREY);
    competitiveButton->setEvent([=] () {
        GameContext::get().startGame(new CompetitiveMode());
        close();
    });
    
    addChild(startPlayerButton);
    addChild(watchAIDemoButton);
    addChild(competitiveButton);
}

void UITitleScreen::draw() const {
    UIView::draw();
}
