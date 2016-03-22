//
//  CharacterAnimated.h
//  MagicWars
//
//  Created by nordsoft on 22.11.14.
//
//

#ifndef __MagicWars__CharacterAnimated__
#define __MagicWars__CharacterAnimated__

#include "Magican.h"
#include "Animated.h"

namespace MagicWars_NS {
    class CharacterAnimated: public Magican
    {
    public:
        CharacterAnimated(const std::string& i_group);
        virtual ~CharacterAnimated() {};
        
        virtual void move(const std::list<int>& i_list);
        //virtual void born(cocos2d::Layer *io_layer, size_t ix, size_t iy);
        virtual void kill() override;
        
        void onDeath();
        
    protected:
        Animated *d_animation = nullptr;
        Animated *d_highAnimation = nullptr;
        std::vector<int> seqDown, seqLeft, seqRight, seqUp;
        std::string d_group;
    };
}

#endif /* defined(__MagicWars__CharacterAnimated__) */
