//
//  TouchEvent.hpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef TouchEvent_hpp
#define TouchEvent_hpp

#include "Vector2d.hpp"

/**
 * TouchEvent class
 * A touch event should be passed down as this class.
 */
class TouchEvent {
public:
    enum EventType {
        DOWN,
        MOVE,
        UP,
    };
    
    TouchEvent(EventType eventType, const vec2d& coordinates);
    ~TouchEvent();
    
    TouchEvent::EventType getEventType() const;
    const vec2d& getCoordinates() const;
private:
    const EventType eventType;
    const vec2d coordinates;
};

#endif /* TouchEvent_hpp */
