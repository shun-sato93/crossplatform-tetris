//
//  UIComponent.hpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIComponent_hpp
#define UIComponent_hpp

#include <string>
#include <vector>

#include "Anchor.hpp"
#include "ColorDefinition.hpp"
#include "Drawable.hpp"
#include "Vector2d.hpp"
#include "Size.hpp"
//#include "TouchEvent.hpp"

class TouchEvent;

class UIComponent: public Drawable {
public:
    UIComponent(int width, int height);
    virtual ~UIComponent();
    
    virtual void draw() const override;
    virtual bool handleTouchEvent(const TouchEvent& touchEvent);
    
    const vec2d& getRelativeCoordinates() const;
    vec2d getAbsoluteCoordinates() const;
    
    void setBackgroundColor(Color::Types color);
    
    virtual void addChild(UIComponent* child);
    void removeChild(UIComponent* child);
    
    void removeAllChildren();
    
    void setParent(UIComponent* parent);
    
    void setCoordinates(const vec2d& coordinates);
    void setCoordinates(const vec2d& coordinates, Anchor::Types anchor);
    
    const Size& getSize() const;
    
    const std::string& getClassName() const;
    
    void setZIndex(int zIndex) override;
    
    void setAnchor(Anchor::Types anchor);
    Anchor::Types getAnchor() const;
protected:
    bool isTouchEventInside(const TouchEvent& touchEvent) const;
    
    // relative coordinates to its parent's
    vec2d coordinates;
    Size size;
    
    Anchor::Types anchor;
    
    std::vector<UIComponent*> children;
    UIComponent* parent;
    
    std::string className;
    
    Color::Types backgroundColor;
};

#endif /* UIComponent_hpp */
