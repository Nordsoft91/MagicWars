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
        scheduleUpdateWithPriority(1);
    }
    
    void Trigger::deactivate()
    {
        d_active = false;
    }
    
    void Trigger::update(float i_delta)
    {
        if(MagicWars_NS::Blocker::state() || !d_active)
            return;
        
        if(d_thrown || !d_event)
        {
            removeFromParent();
            return;
        }
        
        if(!d_condition || d_condition->get())
        {
            d_event->throwEvent();
            removeFromParent();
        }
    }
    
    void Trigger::releaseResources()
    {
        d_controlRes = false;
    }
    
    Trigger::Trigger()
    {
        //cocos2d::log("Trigger constructor");
    }

    Trigger::~Trigger()
    {
        //cocos2d::log("Trigger destructor");
        
        if(d_controlRes)
        {
            if(d_condition) delete d_condition;
            if(d_event) delete d_event;
            d_condition = nullptr;
            d_event = nullptr;
        }
    }
}