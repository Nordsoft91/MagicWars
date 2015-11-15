//
//  UITrigger.cpp
//  MagicWars
//
//  Created by nordsoft on 14.11.15.
//
//

#include "UITrigger.h"

namespace UI_NS {
    void Trigger::setActivationCondition( Condition* i_condition )
    {
        d_condition = i_condition;
    }
    
    void Trigger::setThrowEvent( Event* i_event )
    {
        d_event = i_event;
    }
    
    void Trigger::activate()
    {
        d_active = true;
        scheduleUpdate();
    }
    
    void Trigger::deactivate()
    {
        d_active = false;
    }
    
    void Trigger::update(float i_delta)
    {
        if(MagicWars_NS::Blocker::state() || !d_active || !d_condition || !d_event)
            return;
        
        if(d_thrown)
            return;
        
        if(d_condition->get())
        {
            d_event->throwEvent();
            removeFromParent();
        }
    }
    
    void Trigger::releaseResources()
    {
        d_controlRes = false;
    }
    
    Trigger::~Trigger()
    {
        if(d_controlRes)
        {
            if(d_condition) delete d_condition;
            if(d_event) delete d_event;
        }
    }
}