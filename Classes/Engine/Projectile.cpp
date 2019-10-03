//
//  Projectile.cpp
//  MagicWars
//
//  Created by nordsoft on 03/10/2019.
//

#include "Projectile.h"

namespace MagicWars_NS
{

Projectile* Projectile::create()
{
    Projectile *pRet = new Projectile();
    if (pRet && pRet->init())
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

bool Projectile::init()
{
    if(!cocos2d::Node::init()) return false;
    return true;
}

void Projectile::setTarget(int x, int y)
{
    d_target.x = x;
    d_target.y = y;
}

//delay = 0: immediately start follwing
//delay = -1: start following at the end of animation
//delay > 0: delay in ms
void Projectile::setBegin(Animated* i_animated, int delay)
{
    d_begin = i_animated;
    d_delay = delay;
}
void Projectile::setIdle(Animated* i_animated, int speed, bool oriented)
{
    d_idle = i_animated;
    d_speed = speed;
    d_oriented = oriented;
}
void Projectile::setEnd(const std::function<void()>& callback, Animated* i_animated)
{
    d_end = i_animated;
    d_callback = callback;
}

void Projectile::run()
{
    setLocalZOrder(10000);

    if(d_begin) { addChild(d_begin); d_begin->setIgnoreAnchorPointForPosition(false); }
    if(d_idle) { addChild(d_idle); d_idle->setIgnoreAnchorPointForPosition(false); d_idle->pause(); }
    if(d_end) { addChild(d_end); d_end->setIgnoreAnchorPointForPosition(false); d_end->pause(); }
    
    if(d_idle && d_oriented)
    {
        cocos2d::Vec2 axis(1,0);
        cocos2d::Vec2 vec = d_target - getPosition();
        
        float angle = vec.y>=0 ? cocos2d::Vec2::angle(vec, axis)*180./M_PI : 360.-cocos2d::Vec2::angle(vec, axis)*180./M_PI ;
        setRotation(180-angle + 90);
    }
    
    if(d_delay == 0) d_callback();
    if(d_delay == -1)
    {
        d_listener = cocos2d::EventListenerCustom::create("Animation end", std::bind(&Projectile::onEvent, this, std::placeholders::_1));
        cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(d_listener, 44);
    }
    if(d_delay > 0)
    {
        runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(d_delay), cocos2d::CallFunc::create(std::bind(&Projectile::onEvent, this, nullptr)), NULL));
    }
}

void Projectile::onEvent(cocos2d::EventCustom* i_event)
{
    if(i_event)
    {
        auto* a = reinterpret_cast<Animated*>(i_event->getUserData());
        if((!d_finalStage && a!=d_begin) || (d_finalStage && a!=d_end))
            return;
    }
    if(d_finalStage)
    {
        destroy();
    }
    else
    {
        if(d_begin) removeChild(d_begin);
        if(d_idle) d_idle->resume();
    
        if(d_speed == 0)
        {
            setPosition(getPosition() + d_target);
            onEnd();
        }
        else
        {
            runAction(cocos2d::Sequence::create(cocos2d::MoveTo::create((d_target-getPosition()).length() / d_speed, d_target), cocos2d::CallFunc::create(std::bind(&Projectile::onEnd, this)), NULL));
        }
    }
}

void Projectile::onEnd()
{
    d_finalStage = true;
    d_callback();

    if(d_idle) removeChild(d_idle);
    if(d_end)
    {
        d_end->resume();
        if(!d_listener)
        {
            d_listener = cocos2d::EventListenerCustom::create("Animation end", std::bind(&Projectile::onEvent, this, std::placeholders::_1));
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(d_listener, 44);
        }
    }
    else
    {
        onEvent(nullptr);
    }
    
}

void Projectile::destroy()
{
    if(d_listener)
        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(d_listener);
    removeFromParent();
}

}
