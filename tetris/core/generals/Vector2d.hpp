//
//  Vector2d.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Vector2d_hpp
#define Vector2d_hpp

#include <math.h>

/**
 * 2 dimentional vector class which contains a lot of convenient vector related calculations.
 */
template <class T>
class vec2 {
public:
    T x, y;
    
    vec2() :x(0), y(0) {}
    vec2(T x, T y) : x(x), y(y) {}
    vec2(const vec2& v) : x(v.x), y(v.y) {}
    
    bool operator<(const vec2& v) const{
        if(x != v.x){
            return x < v.x;
        }
        return y < v.y;
    }
    
    bool operator!=(const vec2& v) const{
        return (x != v.x || y != v.y);
    }
    
    bool operator==(const vec2& v) const{
        return (x == v.x && y == v.y);
    }
    
    vec2& operator=(const vec2& v) {
        x = v.x;
        y = v.y;
        return *this;
    }
    
    vec2 operator+(const vec2& v) const{
        return vec2(x + v.x, y + v.y);
    }
    vec2 operator-(const vec2& v) const{
        return vec2(x - v.x, y - v.y);
    }
    vec2& operator+=(const vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    vec2& operator-=(const vec2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    vec2 operator+(const T& s) const {
        return vec2(x + s, y + s);
    }
    vec2 operator-(const T& s) const {
        return vec2(x - s, y - s);
    }
    vec2 operator*(const T& s) const {
        return vec2(x * s, y * s);
    }
    vec2 operator/(const T& s) const {
        return vec2(x / s, y / s);
    }
    
    
    vec2& operator+=(const T& s) {
        x += s;
        y += s;
        return *this;
    }
    vec2& operator-=(const T& s) {
        x -= s;
        y -= s;
        return *this;
    }
    vec2& operator*=(const T& s) {
        x *= s;
        y *= s;
        return *this;
    }
    vec2& operator/=(const T& s) {
        x /= s;
        y /= s;
        return *this;
    }
    
    void set(T x, T y) {
        this->x = x;
        this->y = y;
    }
    
    void rotate(double deg) {
        double theta = deg / 180.0 * 3.14159265;
        double c = cos(theta);
        double s = sin(theta);
        double tx = x * c - y * s;
        double ty = x * s + y * c;
        x = tx;
        y = ty;
    }
    
    vec2& normalize() {
        if (length() == 0) return *this;
        *this *= (1.0 / length());
        return *this;
    }
    
    float distance(vec2 v) const {
        vec2 d(v.x - x, v.y - y);
        return d.length();
    }
    
    float sqrDistance(vec2 v) const {
        vec2 d(v.x - x, v.y - y);
        return d.sqrLength();
    }
    
    float length() const {
        return sqrtf(x * x + y * y);
    }
    
    float sqrLength() const {
        return (x * x + y * y);
    }
    
    void truncate(double length) {
        double angle = atan2f(y, x);
        x = length * cos(angle);
        y = length * sin(angle);
    }
    
    vec2 ortho() const {
        return vec2(y, -x);
    }
    
    static float dot(vec2 v1, vec2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    static float cross(vec2 v1, vec2 v2) {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }
    
};

typedef vec2<int> vec2n;
typedef vec2<float> vec2f;
typedef vec2<double> vec2d;

#endif /* Vector2d_hpp */
