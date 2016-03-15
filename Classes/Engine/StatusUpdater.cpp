//
//  StatusUpdater.cpp
//  MagicWars
//
//  Created by nordsoft on 27.10.14.
//
//

#include "StatusUpdater.h"

#include <Interface/UIIcon.h>

using namespace MagicWars_NS;

StatusUpdater* StatusUpdater::create(double i_cicrleRadius, cocos2d::Color4F i_color)
{
    StatusUpdater *pRet = new StatusUpdater(i_cicrleRadius, i_color);
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

void StatusUpdater::update(float delta)
{
    if(fabs(d_value-d_status)>0.03f || !delta)
    {
        setVisible(true);
        clear();
        double dPI = Consts::get("math2PI");
        double step = double(Consts::get("mathPI")) / 40;
        for(float i=0; i<dPI * d_value/d_maximum; i+=step)
        {
            drawSolidCircle(cocos2d::Vec2(d_circleRadius*cos(i), d_circleRadius*sin(i)), 6, 0.6, 6, d_color );
        }
        d_value-=(d_value-d_status)/100+0.0001f;
        d_force = true;
        d_forceTime = 2;
    }
    else
    {
        setVisible(d_force);
        if(d_forceTime>0)
            d_forceTime-=delta;
        else
        {
            d_force = false;
            removeAllChildren();
        }
    }
}

bool StatusUpdater::init()
{
    if(!cocos2d::DrawNode::init())
        return false;
    
    scheduleUpdateWithPriority(10);
    update(0);
    setVisible(false);
    return true;
}

void StatusUpdater::setStatus(float stt)
{
    d_status = stt;
}

void StatusUpdater::show(bool i_force, double i_time)
{
    d_force = i_force;
    d_forceTime = i_time;
}

StateNotify* StateNotify::create(const std::string& i_state, int i_value)
{
    StateNotify *pRet = new StateNotify;
    if (pRet && pRet->init(i_state, i_value))
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

bool StateNotify::init(const std::string &i_state, int i_value)
{
    if(!cocos2d::Node::init())
        return false;
    
    auto back = cocos2d::Sprite::create(RES("Interface","roundButton.png"));
    auto icon = UI_NS::Icon::createFromConsts(i_state);
    //auto numb = cocos2d::Label::createWithTTF(std::to_string(i_value), RES("fonts", "Washington.ttf"), 24);
    
    icon->setAnchorPoint({0.5,0.5});
    icon->setScale(0.09);
    
    //numb->setColor(cocos2d::Color3B::BLACK);
    //numb->setOpacity(140);
    
    addChild(back);
    addChild(icon);
    //addChild(numb);
    
    setScale(0.7);
    
    return true;
}

void StateNotify::setPositionAround(float i_radius, size_t i_max, size_t n)
{
    if(n>=i_max)
        throw std::logic_error("cannot place around with zero maximum elements");
    
    if(i_max==1)
        setPosition(0, i_radius);
    else
    {
        double angle = double(n)/double(i_max) * (double)Consts::get("math2PI") + (double)Consts::get("mathPI2");
        setPosition(i_radius*cos(angle), i_radius*sin(angle));
    }
}
