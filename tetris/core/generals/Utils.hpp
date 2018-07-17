//
//  Utils.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <mach/mach.h>
#include <mach/clock.h>
#include <vector>
static clock_serv_t clk;
static bool clk_initialized = false;

/**
 * Utils.hpp defines utility functions that are used from entire project.
 */

/**
 * Delete pointers. Use this function instead of delete to avoid deleting same pointers twice.
 */
template<class T>
static inline void SafeDelete( T*& p ){
    delete (p);
    (p) = nullptr;
}

/**
 * @return current time in miliscond.
 */
static inline double now_ms() {
    // TODO: cross-platform time function
    if( !clk_initialized ) {
        host_get_clock_service( mach_host_self(), CALENDAR_CLOCK, &clk );
        clk_initialized = true;
    }
    
    mach_timespec_t res;
    
    clock_get_time( clk, &res );
    
    return (1000.0 * res.tv_sec) + (0.000001 * res.tv_nsec);
}

#endif /* Utils_hpp */
