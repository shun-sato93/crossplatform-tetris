//
//  Hookable.hpp
//  tetris
//
//  Created by Shun Sato on 7/11/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Hookable_hpp
#define Hookable_hpp

#include <functional>

template<typename T>
class hookable {
public:
    hookable(const T& value, std::function<void(const T& oldValue, const T& newValue)> hook)
    :value(value)
    ,hook(hook)  {}
    
    hookable(const T& value)
    :value(value)
    ,hook(nullptr)  {}
    
    hookable(const hookable& rhs)
    :value(rhs.value)
    ,hook(nullptr)
    {}
    
    void setHook(std::function<void(const T& oldValue, const T& newValue)> hook) {
        this->hook = hook;
    }
    
    T& operator=(const T& rhs) {
        T old = value;
        value = rhs;
        if (hook) {
            hook(old, value);
        }
        return value;
    }
    
    void operator=(const hookable& rhs) {
        value = rhs.value;
    }
    
    const T& get() const {
        return value;
    }
private:
    
    
    T value;
    std::function<void(const T& oldValue, const T& newValue)> hook;
};


#endif /* Hookable_hpp */
