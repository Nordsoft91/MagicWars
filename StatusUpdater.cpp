//
//  StatusUpdater.cpp
//  MagicWars
//
//  Created by nordsoft on 27.10.14.
//
//

#include "StatusUpdater.h"

using namespace MagicWars_NS;

void StatusUpdater::update(float delta)
{
    if(d_value>d_status || !delta)
    {
        setVisible(true);
        clear();
        double dPI = Consts::get("math2PI");
        double step = double(Consts::get("mathPI")) / 50;
        for(float i=0; i<dPI * d_value/d_maximum; i+=step)
        {
            drawSolidCircle(cocos2d::Vec2(35*cos(i), 35*sin(i)), 4, 0.5, 6, cocos2d::Color4F(1.,0.,0.,0.2) );
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
    
    scheduleUpdate();
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

