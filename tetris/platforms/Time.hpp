//
//  Time.hpp
//  tetris
//
//  Created by Shun Sato on 7/20/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Time_hpp
#define Time_hpp

#ifdef _WIN32

#include <windows.h>

#else

#include <mach/mach.h>
#include <mach/clock.h>
static clock_serv_t clk;
static bool clk_initialized = false;

#endif

/**
 * namespace Time defines time related functions and properties.
 * It should be made platform independent.
 */
namespace Time {
    /**
     * @return current time in miliscond.
     */
    static inline double now_ms() {
#ifdef _WIN32
        SYSTEMTIME time;
        GetSystemTime(&time);
        return (time.wSecond * 1000) + time.wMilliseconds;
#else
        if (!clk_initialized) {
            host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &clk);
            clk_initialized = true;
        }
        
        mach_timespec_t res;
        
        clock_get_time(clk, &res);
        
        return (1000.0 * res.tv_sec) + (0.000001 * res.tv_nsec);
#endif
    }
}

#endif /* Time_hpp */
