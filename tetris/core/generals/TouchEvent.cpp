//
//  TouchEvent.cpp
//  tetris
//
//  Created by Shun Sato on 7/9/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "TouchEvent.hpp"


TouchEvent::TouchEvent(EventType eventType, const vec2d& coordinates)
:eventType(eventType)
,coordinates(coordinates)
{}

TouchEvent::~TouchEvent() {
    
}

TouchEvent::EventType TouchEvent::getEventType() const {
    return eventType;
}

const vec2d& TouchEvent::getCoordinates() const {
    return coordinates;
}
