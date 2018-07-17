//
//  UIBaseView.hpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIBaseView_hpp
#define UIBaseView_hpp

#include <functional>

#include "UIView.hpp"


/**
 * Base layer class.
 * 
 */
class UIBaseView: public UIView {
public:
    UIBaseView(int zIndex);
    ~UIBaseView();
    
    bool handleTouchEvent(const TouchEvent& touchEvent) override;
    void close();
    bool isClosed() const;
    void setCallbackClosed(std::function<void(void)> callbackClosed);
    
    void addChild(UIComponent* child) override;
private:
    bool _isClosed;
    
    std::function<void(void)> callbackClosed;
};

#endif /* UIBaseView_hpp */
