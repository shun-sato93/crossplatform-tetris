//
//  Random.hpp
//  tetris
//
//  Created by Shun Sato on 7/3/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Random_hpp
#define Random_hpp

#include <random>

/**
 * Random class that wraps platform independent random generator.
 */
class Random {
public:
    Random(int seed);
    int getInt();
    void setSeed(int seed);
private:
    std::mt19937 m_mt;
};

#endif /* Random_hpp */
