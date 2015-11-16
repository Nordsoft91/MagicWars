//
//  UIEvent.h
//  MagicWars
//
//  Created by nordsoft on 14.11.15.
//
//

#ifndef __MagicWars__UIEvent__
#define __MagicWars__UIEvent__

#include "UICondition.h"
#include "UIMessageSequence.h"
#include "TouchControl.h"

namespace UI_NS {
    class Event
    {
    public:
        virtual ~Event() = default;
        
        virtual void throwEvent() = 0;
    };
    
    
    //EventSequence
    class EventSequence: public Event
    {
    public:
        EventSequence(std::list<Event*> i_events): d_events(i_events) {}
        
        virtual void throwEvent() override
        {
            for(auto* i : d_events)
                i->throwEvent();
        }
        
        virtual ~EventSequence()
        {
            for(auto* i : d_events)
                delete i;
        }
        
    private:
        std::list<Event*> d_events;
    };
    
    //EventMessage
    class EventMessage: public Event
    {
    public:
        EventMessage(cocos2d::Node* io_scene, const std::list<std::string>& i_message): d_scene(io_scene), d_message(i_message)
        {}
        
        virtual void throwEvent() override
        {
            cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
            cocos2d::Vec2 screenCenter(visibleSize.width/2, visibleSize.height/2);
            d_scene->addChild(UI_NS::MessageSequence::create(screenCenter, cocos2d::Color4F{0,0,0,0.5}, d_message));
        }
        
    protected:
        cocos2d::Node* d_scene = nullptr;
        const std::list<std::string> d_message;
    };
    
    class EventDialog: public Event
    {
    public:
        EventDialog(cocos2d::Node* io_character, const std::list<std::string>& i_message): d_owner(io_character), d_message(i_message)
        {}
        
        virtual void throwEvent() override
        {
            MagicWars_NS::TouchControl::instance().centralizeOn(d_owner->getPosition());
            d_owner->addChild(UI_NS::MessageSequence::create(d_owner->getPosition(), cocos2d::Color4F{1,1,1,0.5}, d_message));
        }
        
    protected:
        cocos2d::Node* d_owner = nullptr;
        const std::list<std::string> d_message;
    };
    
    //EventCondition
    class EventCondition: public Event, public Condition
    {
    public:
        
        virtual bool get() const override
        {
            return d_active;
        }
        
        virtual void throwEvent() override
        {
            d_active = true;
        }
        
    protected:
        bool d_active = false;
    };
}

#endif /* defined(__MagicWars__UIEvent__) */
