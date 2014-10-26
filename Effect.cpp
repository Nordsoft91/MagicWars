//
//  Effect.cpp
//  MagicWars
//
//  Created by nordsoft on 26.10.14.
//
//

#include "Effect.h"
#include "Consts.h"

using namespace MagicWars_NS;


Effect::Effect(const std::string i_spr, int i_frames)
{
    int efW = Consts::get("effectFrameWidth");
    int efH = Consts::get("effectFrameHeight");
    
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    for(int i=0; i<i_frames; ++i)
    {
        frames.pushBack(cocos2d::SpriteFrame::create(i_spr, cocos2d::Rect((i%5)*efW, (i/5)*efH, efW, efH)));
    }
    d_animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1, 1);
    //ignoreAnchorPointForPosition(true);
}

Effect::~Effect()
{

}

Effect* Effect::create(const std::string i_spr, int i_frames, cocos2d::Vec2 i_start, cocos2d::Vec2 i_goal)
{
    Effect *pRet = new Effect(i_spr, i_frames);
    if (pRet && pRet->init(i_start, i_goal))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Effect::init(cocos2d::Vec2 i_start, cocos2d::Vec2 i_goal)
{
    if(!cocos2d::Sprite::init())
        return false;
    
    setPosition(i_start);
    runAction(cocos2d::Animate::create(d_animation));
    scheduleUpdate();
    return true;
}

void Effect::update(float delta)
{
    if(!getNumberOfRunningActions())
        removeFromParent();
}
