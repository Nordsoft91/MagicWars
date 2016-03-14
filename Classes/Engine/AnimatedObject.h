//
//  MapObject.h
//  MagicWars
//
//  Created by nordsoft on 14.03.16.
//
//

#ifndef __MagicWars__MapObject__
#define __MagicWars__MapObject__

#include "Magican.h"
#include "Animated.h"

namespace MagicWars_NS {
    class AnimatedObject: public GameObj
    {
    public:
        AnimatedObject(const std::string& i_animation);
        virtual ~AnimatedObject() = default;
            
    protected:
        AnimatedObject();
        
        void switchAnimation(const std::string& i_animation);
        
        Animated *anim;
    };
    
    class ObjectFire: public AnimatedObject
    {
    public:
        ObjectFire(const std::string& i_fireDescription, int stage = 0);
        
        void collisionWithMagican( Magican* i_magican );
        bool turn(); //add one turn to live and return true if should be killed
        
    private:
        const std::string d_description;
        int d_liveTime = 0;
    };
}

#endif /* defined(__MagicWars__MapObject__) */
