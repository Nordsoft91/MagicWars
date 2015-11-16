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
    
    class Trigger;

    class Event
    {
    public:
        virtual ~Event() = default;
        
        virtual void throwEvent() = 0;
    };
    
    
    //EventHeap
    class EventHeap: public Event
    {
    public:
        EventHeap(std::list<Event*> i_events): d_events(i_events) {}
        
        void releaseResourceControl(Event* i_event) {d_preventRelease.push_back(i_event);}
        
        virtual void throwEvent() override
        {
            for(auto* i : d_events)
                i->throwEvent();
        }
        
        virtual ~EventHeap()
        {
            for(auto* i : d_events)
            {
                if(std::find(d_preventRelease.begin(), d_preventRelease.end(), i)==d_preventRelease.end())
                    delete i;
            }
        }
        
    private:
        std::list<Event*> d_events;
        std::list<Event*> d_preventRelease;
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
            d_owner->addChild(UI_NS::MessageSequence::create(cocos2d::Vec2(64,128), cocos2d::Color4F{1,1,1,0.5}, d_message));
        }
        
    protected:
        cocos2d::Node *d_owner = nullptr, *d_scene = nullptr;
        const std::list<std::string> d_message;
    };
    
    //trigger activation
    class EventActivateTrigger: public Event
    {
    public:
        EventActivateTrigger(Trigger* i_trigger): d_trigger(i_trigger) {}
        
        virtual void throwEvent() override;
        
    protected:
        Trigger* d_trigger = nullptr;
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
