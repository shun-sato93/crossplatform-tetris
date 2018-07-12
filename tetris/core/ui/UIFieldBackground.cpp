//
//  UIFieldBackground.cpp
//  tetris
//
//  Created by Shun Sato on 7/3/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIFieldBackground.hpp"

#include <string>

#include "Coordinates.hpp"
#include "IOInterface.hpp"
#include "UILabel.hpp"


UIFieldBackground::UIFieldBackground()
:UIBaseView(-110)
,scoreLabel(nullptr)
,highscoreLabel(nullptr)
{
    className = "UIFieldBackground";
    setup();
}

UIFieldBackground::~UIFieldBackground() {
    
}

void UIFieldBackground::setup() {
    color = Color::WHITE;
    
    scoreLabel = new UILabel("SCORE: 0", Color::BLACK);
    scoreLabel->setCoordinates(vec2d(10, -50), Anchor::UPPER_LEFT);
    highscoreLabel = new UILabel("HIGHSCORE: 0", Color::BLACK);
    highscoreLabel->setCoordinates(vec2d(10, -70), Anchor::UPPER_LEFT);
    UILabel* keysDescription = new UILabel("KEYS:", Color::BLACK);
    keysDescription->setCoordinates(vec2d(10, -250), Anchor::UPPER_LEFT);
    UILabel* up = new UILabel("Up", Color::BLACK);
    up->setCoordinates(vec2d(10, -270), Anchor::UPPER_LEFT);
    UILabel* down = new UILabel("Down", Color::BLACK);
    down->setCoordinates(vec2d(10, -290), Anchor::UPPER_LEFT);
    UILabel* right = new UILabel("Right", Color::BLACK);
    right->setCoordinates(vec2d(10, -310), Anchor::UPPER_LEFT);
    UILabel* left = new UILabel("Left", Color::BLACK);
    left->setCoordinates(vec2d(10, -330), Anchor::UPPER_LEFT);
    UILabel* space = new UILabel("Space(Rotate)", Color::BLACK);
    space->setCoordinates(vec2d(10, -350), Anchor::UPPER_LEFT);
    UILabel* esc = new UILabel("ESC(Open Menu)", Color::BLACK);
    esc->setCoordinates(vec2d(10, -370), Anchor::UPPER_LEFT);
    
    addChild(scoreLabel);
    addChild(highscoreLabel);
    addChild(keysDescription);
    addChild(up);
    addChild(down);
    addChild(right);
    addChild(left);
    addChild(space);
    addChild(esc);
}

void UIFieldBackground::draw() const {
    UIView::draw();
}

void UIFieldBackground::setScore(int score) {
    if (scoreLabel == nullptr) {
        return;
    }
    scoreLabel->setText("SCORE: " + std::to_string(score));
    scoreLabel->sizeToFitText();
}

void UIFieldBackground::setHighscore(int highscore) {
    if (highscoreLabel == nullptr) {
        return;
    }
    highscoreLabel->setText("HIGHSCORE: " + std::to_string(highscore));
    highscoreLabel->sizeToFitText();
}
