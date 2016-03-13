//
//  MapObject.h
//  MagicWars
//
//  Created by nordsoft on 14.03.16.
//
//

#ifndef __MagicWars__MapObject__
#define __MagicWars__MapObject__

#include "GameObj.h"
#include "Animated.h"

namespace MagicWars_NS {
    class AnimatedObject: public GameObj
    {
    public:
        AnimatedObject(const std::string& i_animation);
        virtual ~AnimatedObject() = default;
            
    protected:
        Animated *anim;
    };
}

#endif /* defined(__MagicWars__MapObject__) */
