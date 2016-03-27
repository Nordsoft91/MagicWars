//
//  CharacterAnimated.cpp
//  MagicWars
//
//  Created by nordsoft on 22.11.14.
//
//

#include "CharacterAnimated.h"

using namespace MagicWars_NS;

//const double speed = 0.01;
const double speed = 0.4;

CharacterAnimated::CharacterAnimated(const std::string& i_group): Magican(i_group), d_group(i_group)
{
    if(std::string(Consts::get("spriteType", i_group)) != "ANIMATED")
        throw std::runtime_error("not animated object!");
    
    std::string prms = Consts::get("animationParams", d_group);
    std::vector<Param> __seq;
    seqDown = Consts::get("goDown", prms).toVector<int>();
    seqLeft = Consts::get("goLeft", prms).toVector<int>();
    seqRight = Consts::get("goRight", prms).toVector<int>();
    seqUp = Consts::get("goUp", prms).toVector<int>();
    
    d_animation = Animated::create(RES("persons",(std::string)Consts::get("animationName", d_group)), prms, 0, 1);
    d_highAnimation = Animated::create(RES("persons",(std::string)Consts::get("animationName", d_group)), prms, 0, 1);
    d_highAnimation->setOpacity(96);
    d_sprite->addChild(d_animation);
    d_highSprite->addChild(d_highAnimation);
}

cocos2d::Sprite* CharacterAnimated::createPicture()
{
    return Animated::create(RES("persons", (std::string)Consts::get("animationName", d_group)), Consts::get("animationParams", d_group), { 0 });
}

void CharacterAnimated::move(const std::list<int>& i_list)
{
    cocos2d::Vector<cocos2d::FiniteTimeAction*> seq, seqHigh;
    std::vector<int> animSeq;
    
    Blocker::block(Pause::Animation, speed*i_list.size());
    
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
        
        seq.pushBack(cocos2d::MoveTo::create(speed, cocos2d::Point(x*globalStepX,y*globalStepY)));
        seq.pushBack(cocos2d::CallFuncN::create(CC_CALLBACK_0(GameObj::onEndOfMove, this, x, y)));
        seqHigh.pushBack(cocos2d::MoveTo::create(speed, cocos2d::Point(x*globalStepX,y*globalStepY)));
    }
    d_sprite->runAction(cocos2d::Sequence::create(seq));
    d_highSprite->runAction(cocos2d::Sequence::create(seqHigh));
    
    if(d_animation)
        d_animation->removeFromParent();
    if(d_highAnimation)
        d_highAnimation->removeFromParent();
    
	d_animation = Animated::create(RES("persons", (std::string)Consts::get("animationName", d_group)), Consts::get("animationParams", d_group), animSeq);
    d_highAnimation = Animated::create(RES("persons", (std::string)Consts::get("animationName", d_group)), Consts::get("animationParams", d_group), animSeq);
    d_highAnimation->setOpacity(96);
    d_sprite->addChild(d_animation);
    d_highSprite->addChild(d_highAnimation);
}

void CharacterAnimated::kill()
{
    d_animation->runAction(
                    cocos2d::Sequence::create(
                                              cocos2d::FadeOut::create(3),
                                              cocos2d::CallFuncN::create(CC_CALLBACK_0(CharacterAnimated::onDeath, this)),
                                              NULL));
    
    d_highAnimation->runAction(
                           cocos2d::Sequence::create(
                                                     cocos2d::FadeOut::create(3),
                                                     cocos2d::CallFuncN::create(CC_CALLBACK_0(CharacterAnimated::onDeath, this)),
                                                     NULL));
}
                    
void CharacterAnimated::onDeath()
{
    Magican::kill();
}