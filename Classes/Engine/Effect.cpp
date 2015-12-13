//
//  Effect.cpp
//  MagicWars
//
//  Created by nordsoft on 26.10.14.
//
//

#include "Effect.h"
#include <Common/Consts.h>
#include "Blocker.h"

using namespace MagicWars_NS;


Effect::Effect(const std::string i_spr, int i_frames)
{
    int efW = Consts::get("effectFrameWidth");
    int efH = Consts::get("effectFrameHeight");
    
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    for(int i=0; i<i_frames; ++i)
    {
        frames.pushBack(cocos2d::SpriteFrame::create(RES("effects",i_spr), cocos2d::Rect((i%5)*efW, (i/5)*efH, efW, efH)));
    }
    d_animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1, 1);
    Blocker::block(Pause::Animation);
    //ignoreAnchorPointForPosition(true);
}

Effect::~Effect()
{

}

Effect* Effect::create(const std::string i_spr, int i_frames, cocos2d::Vec2 i_start, cocos2d::Vec2 i_goal)
{
    Effect *pRet = new Effect(i_spr, i_frames);
    if (pRet && pRet->init(i_start, i_goal, double(i_frames) / 10.))
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

bool Effect::init(cocos2d::Vec2 i_start, cocos2d::Vec2 i_goal, double i_time)
{
    if(!cocos2d::Sprite::init())
        return false;
    
    setPosition(i_start);
	setZOrder(10000);
    runAction(cocos2d::Animate::create(d_animation));
    if(i_goal!=cocos2d::Vec2::ZERO)
    {
        cocos2d::Vec2 vec = i_goal - i_start;
        cocos2d::Vec2 axis(1,0);
        float angle = vec.y>=0 ? cocos2d::Vec2::angle(vec, axis)*180./3.1415 : 360.-cocos2d::Vec2::angle(vec, axis)*180./3.1415 ;
        setRotation(180-angle + 90);
        auto i_move = cocos2d::MoveTo::create(i_time, i_goal);
        runAction(i_move);
    }
    scheduleUpdateWithPriority(10);
    return true;
}

void Effect::update(float delta)
{
	cocos2d::BlendFunc func;
	func.src = GL_ONE;
	func.dst = GL_ONE_MINUS_SRC_COLOR;
	setBlendFunc(func);
    if(!getNumberOfRunningActions())
    {
        removeFromParent();
        Blocker::release(Pause::Animation);
    }
}
