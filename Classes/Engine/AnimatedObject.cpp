//
//  MapObject.cpp
//  MagicWars
//
//  Created by nordsoft on 14.03.16.
//
//

#include "AnimatedObject.h"

namespace MagicWars_NS {
    
AnimatedObject::AnimatedObject(const std::string& i_group): GameObj("stub.png")
{
    if(std::string(Consts::get("spriteType", i_group)) != "ANIMATED")
        throw std::runtime_error("not animated object!");
    
    auto seq = Consts::get("sequence", i_group).toVector<int>();
    if(seq.empty())
    {
        anim = Animated::create((std::string)Consts::get("animationName", i_group), i_group, 0, (size_t)Consts::get("sizeX", i_group) * (size_t)Consts::get("sizeY", i_group), true);
    }
    else
        anim = Animated::create((std::string)Consts::get("animationName", i_group), i_group, seq, true);
    
    d_sprite->addChild(anim, 2);
}
    
}
