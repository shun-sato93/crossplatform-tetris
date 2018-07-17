//
//  UIManager.hpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIManager_hpp
#define UIManager_hpp

#include <vector>

#include "Singleton.hpp"
#include "Updatable.hpp"

class UIComponent;
class TouchEvent;
class UIBaseView;

/**
 *
 */
class UIManager: Updatable, public Singleton<UIManager> {
public:
    ~UIManager();
    
    void update() override;
    void handleTouchEvent(const TouchEvent& touchEvent);
    void addNewBaseUI(UIBaseView*);
    void clearAllBaseUI();
    const std::vector<UIBaseView*>& getBaseViews() const;
private:
    friend class Singleton<UIManager>;
    UIManager();
    
    std::vector<UIBaseView*> baseViews;
};

#endif /* UIManager_hpp */
