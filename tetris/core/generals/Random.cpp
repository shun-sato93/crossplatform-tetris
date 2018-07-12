//
//  Random.cpp
//  tetris
//
//  Created by Shun Sato on 7/3/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "Random.hpp"

Random::Random(int seed)
:m_mt(seed){
    
}

int Random::getInt(){
    return abs(static_cast<int>(m_mt()));
}

void Random::setSeed(int seed){
    m_mt.seed(seed);
}
