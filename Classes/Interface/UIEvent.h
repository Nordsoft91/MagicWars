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


namespace UI_NS {
    
    class Trigger;

    class Event
    {
    public:
        Event() { cocos2d::log("Constructor"); };
        
        virtual ~Event() { cocos2d::log("Destructor"); }
        
        virtual void throwEvent() = 0;
    };
    
    
    //EventHeap
    class EventHeap: public Event
    {
    public:
        EventHeap(std::list<Event*> i_events): d_events(i_events) { cocos2d::log("Heap constructor"); }
        void releaseResourceControl(Event* i_event) {d_preventRelease.push_back(i_event);}
        virtual void throwEvent() override;
        virtual ~EventHeap();
        
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
        
        virtual void throwEvent() override;
        
    protected:
        cocos2d::Node* d_scene = nullptr;
        const std::list<std::string> d_message;
    };
    
    //EventDialog
    class EventDialog: public Event
    {
    public:
        EventDialog(cocos2d::Node* io_character, const std::list<std::string>& i_message): d_owner(io_character), d_message(i_message)
        {}
        
        virtual void throwEvent() override;
        
    protected:
        cocos2d::Node *d_owner = nullptr;
        const std::list<std::string> d_message;
    };
    
    //EventChain
    class EventChain: public Event
    {
    public:
        EventChain(cocos2d::Node* io_scene, const std::list<Event*>& i_chain);
        
        virtual void throwEvent() override;
        
    protected:
        Trigger* d_trigger = nullptr;
        const std::list<Event*> d_chain;
    };
    
    //trigger activation
    class EventActivateTrigger: public Event
    {
    public:
        EventActivateTrigger(Trigger* i_trigger);
        virtual void throwEvent() override;
        
    protected:
        Trigger* d_trigger = nullptr;
    };
    
    //EventCondition
    class EventCondition: public Event, public Condition
    {
    public:
        virtual bool get() const override;
        virtual void throwEvent() override;
        
    protected:
        bool d_active = false;
    };

}

#endif /* defined(__MagicWars__UIEvent__) */
