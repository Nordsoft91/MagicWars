//
//  CurrentTurnLight.cpp
//  MagicWars
//
//  Created by nordsoft on 28.10.14.
//
//

#include "CurrentTurnLight.h"

using namespace MagicWars_NS;

void CurrentTurnLight::update(float delta)
{
    if(d_shown)
    {
        setVisible(true);
        clear();
        
        drawSolidCircle(cocos2d::Vec2::ZERO, 26, 0.5, 24, cocos2d::Color4F(1.,1.,1.,d_status*0.5) );
        
        if(d_status>=0.9 || d_status<=0.1)
            d_statusDir*=-1;
        
        d_status+=d_statusDir*0.02;
    }
}

bool CurrentTurnLight::init()
{
    if(!cocos2d::DrawNode::init())
        return false;
    
    scheduleUpdate();
    show();
    return true;
}


void CurrentTurnLight::show(bool i_show)
{
    d_shown = i_show;
    if(d_shown)
    {
        d_status = 0.9;
        d_statusDir = 1;
    }
    else
    {
        setVisible(false);
    }
}