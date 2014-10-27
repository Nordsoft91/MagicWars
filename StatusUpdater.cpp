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
    if(d_value>d_status)
    {
        setVisible(true);
        clear();
        for(float i=0; i<6.283 * d_value/d_maximum; i+=3.14/50)
        {
            drawSolidCircle(cocos2d::Vec2(35*cos(i), 35*sin(i)), 3, 0.5, 6, cocos2d::Color4F(1.,0.,0.,0.2) );
        }
        d_value-=(d_value-d_status)/30+0.001f;
    }
    else
        setVisible(d_force);
}

bool StatusUpdater::init()
{
    if(!cocos2d::DrawNode::init())
        return false;
    
    scheduleUpdate();
    for(float i=0; i<6.283 * d_value/d_maximum; i+=3.14/50)
    {
        drawSolidCircle(cocos2d::Vec2(35*cos(i), 35*sin(i)), 3, 0.5, 6, cocos2d::Color4F(1.,0.,0.,0.2) );
    }
    d_value-=(d_value-d_status)/30+0.001f;
    setVisible(false);
    return true;
}

void StatusUpdater::setStatus(float stt)
{
    d_status = stt;
}

