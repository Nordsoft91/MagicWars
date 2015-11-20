//
//  StatusUpdater.cpp
//  MagicWars
//
//  Created by nordsoft on 27.10.14.
//
//

#include "StatusUpdater.h"

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
    if(fabs(d_value-d_status)>0.05f || !delta)
    {
        setVisible(true);
        clear();
        double dPI = Consts::get("math2PI");
        double step = double(Consts::get("mathPI")) / 30;
        for(float i=0; i<dPI * d_value/d_maximum; i+=step)
        {
            drawSolidCircle(cocos2d::Vec2(d_circleRadius*cos(i), d_circleRadius*sin(i)), 4, 0.6, 6, d_color );
        }
        d_value-=(d_value-d_status)/30+0.001f;
    }
    else
    {
        setVisible(d_force);
        if(d_forceTime>0)
            d_forceTime-=delta;
        else
            d_force = false;
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

