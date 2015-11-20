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
    
    std::string prms = Consts::get("animationParams", d_group);
    std::vector<Param> __seq;
    seqDown = Consts::get("goDown", prms).toVector<int>();
    seqLeft = Consts::get("goLeft", prms).toVector<int>();
    seqRight = Consts::get("goRight", prms).toVector<int>();
    seqUp = Consts::get("goUp", prms).toVector<int>();
    
    anim = Animated::create(Consts::get("animationName", d_group), prms, 0, 1);
    d_sprite->addChild(anim, 2);
}

void CharacterAnimated::move(const std::list<int>& i_list)
{
    cocos2d::Vector<cocos2d::FiniteTimeAction*> seq;
    std::vector<int> animSeq;
    
    Blocker::block(Pause::Animation, 0.4*i_list.size());
    
    for(int i : i_list)
    {
        int tx = 0, ty = 0;
        switch (i)
        {
            case 0: tx = 1; animSeq.insert(animSeq.end(), seqRight.begin(), seqRight.end() ); break;
            case 1: ty = 1; animSeq.insert(animSeq.end(), seqUp.begin(), seqUp.end()); break;
            case 2: tx = -1; animSeq.insert(animSeq.end(), seqLeft.begin(), seqLeft.end()); break;
            case 3: ty = -1; animSeq.insert(animSeq.end(), seqDown.begin(), seqDown.end()); break;
        }
        x += tx; y += ty;
        
        seq.pushBack(cocos2d::MoveTo::create(0.4, cocos2d::Point(x*globalStepX,y*globalStepY)));
        
    }
    d_sprite->setZOrder(1000-y);
    auto action = cocos2d::Sequence::create(seq);
    d_sprite->runAction(action);
    
    if(anim)
    {
        anim->removeFromParent();
    }
    anim = Animated::create(Consts::get("animationName", d_group), Consts::get("animationParams", d_group), animSeq);
    d_sprite->addChild(anim, 2);
    
}