//
//  ColorDefinition.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef ColorDefinition_hpp
#define ColorDefinition_hpp

/**
 * Definition of color types
 */
namespace Color {
    enum Types {
        NONE,
        _1,
        _2,
        _3,
        _4,
        BLACK,
        WHITE,
        GREY,
    };
    
    /**
     * @return random color type
     */
    Types getRandomColor();
}

#endif /* ColorDefinition_hpp */
