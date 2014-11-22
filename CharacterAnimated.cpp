//
//  CharacterAnimated.cpp
//  MagicWars
//
//  Created by nordsoft on 22.11.14.
//
//

#include "CharacterAnimated.h"

using namespace MagicWars_NS;

CharacterAnimated::CharacterAnimated(std::string i_group): Magican(i_group), d_group(i_group)
{
    if(std::string(Consts::get("spriteType", i_group)) != "ANIMATED")
        throw std::runtime_error("not animated object!");
    
    anim = Animated::create(Consts::get("animationName", d_group), Consts::get("animationParams", d_group), 0, 1);
    d_sprite->addChild(anim, 2);
}

void CharacterAnimated::move(const std::list<int>& i_list)
{
    cocos2d::Vector<cocos2d::FiniteTimeAction*> seq;
    std::vector<int> animSeq;
    for(int i : i_list)
    {
        int tx = 0, ty = 0;
        switch (i)
        {
            case 0: tx = 1; animSeq.insert(animSeq.end(), {6,7,8,7}); break;
            case 1: ty = 1; animSeq.insert(animSeq.end(), {9,10,11,10}); break;
            case 2: tx = -1; animSeq.insert(animSeq.end(), {3,4,5,4}); break;
            case 3: ty = -1; animSeq.insert(animSeq.end(), {0,1,2,1}); break;
        }
        x += tx; y += ty;
        
        seq.pushBack(cocos2d::MoveTo::create(0.4, cocos2d::Point(x*globalStepX,y*globalStepY)));
        
    }
    auto action = cocos2d::Sequence::create(seq);
    d_sprite->runAction(action);
    
    if(anim)
    {
        anim->removeFromParent();
    }
    anim = Animated::create(Consts::get("animationName", d_group), Consts::get("animationParams", d_group), animSeq);
    d_sprite->addChild(anim, 2);
    
}