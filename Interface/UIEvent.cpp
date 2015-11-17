//
//  UIEvent.cpp
//  MagicWars
//
//  Created by nordsoft on 14.11.15.
//
//

#include "UIEvent.h"
#include "UITrigger.h"

namespace UI_NS {
    void EventActivateTrigger::throwEvent()
    {
        d_trigger->activate();
    }
    
    void EventHeap::throwEvent()
    {
        for(auto* i : d_events)
            i->throwEvent();
    }
    
    EventHeap::~EventHeap()
    {
        for(auto* i : d_events)
        {
            if(std::find(d_preventRelease.begin(), d_preventRelease.end(), i)==d_preventRelease.end())
                delete i;
        }
    }
    
    void EventMessage::throwEvent()
    {
        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        cocos2d::Vec2 screenCenter(visibleSize.width/2, visibleSize.height/2);
        d_scene->addChild(UI_NS::MessageSequence::create(screenCenter, cocos2d::Color4F{0,0,0,0.5}, d_message));
    }
    
    void EventDialog::throwEvent()
    {
        MagicWars_NS::TouchControl::instance().centralizeOn(d_owner->getPosition());
        d_owner->addChild(UI_NS::MessageSequence::create(cocos2d::Vec2(64,128), cocos2d::Color4F{1,1,1,0.5}, d_message));
    }
    
    bool EventCondition::get() const
    {
        return d_active;
    }
        
    void EventCondition::throwEvent()
    {
        d_active = true;
    }
}
