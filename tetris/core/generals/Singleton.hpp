//
//  Singleton.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Singleton_hpp
#define Singleton_hpp

/**
 * Singleton base class.
 * By inheriting this class, a class doesn't have to have its own get() method and static instance.
 */
template<class T>
class Singleton
{
protected:
public:
    static T& get(){
        static T* s_singleton = T::createInstance();
        return getReference(s_singleton);
    }
private:
    typedef T* singleton_pointer_type;
    inline static T* createInstance() { return new T(); }
    inline static T& getReference(const singleton_pointer_type& ptr){
        return *ptr;
    }
protected:
    Singleton(){}
private:
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

#endif /* Singleton_hpp */
