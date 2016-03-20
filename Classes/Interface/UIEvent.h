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
#include "Interface/Interface.h"


namespace UI_NS {
    
    class Trigger;

    class Event
    {
    public:
        Event() {} //cocos2d::log("Constructor"); };
        
        virtual ~Event() {} //cocos2d::log("Destructor"); }
        
        virtual void throwEvent() = 0;
    };
    
    //EventCreate
    template<class T>
    class EventCreate: public Event
    {
    public:
        EventCreate(cocos2d::Node* io_scene, const std::pair<int, int>& i_pos): d_scene(io_scene), d_x(i_pos.first), d_y(i_pos.second) {}
        EventCreate(cocos2d::Node* io_scene, const std::string& i_name, int i_relX = 0, int i_relY = 0): d_scene(io_scene), d_name(i_name), d_x(i_relX), d_y(i_relY) {}
        
        virtual void throwEvent() override
        {
            cocos2d::Node* obj = nullptr;
            if(!d_name.empty())
                obj = T::create(d_name, d_x, d_y);
            else
                obj = T::create(cocos2d::Vec2(d_x,d_y));
            
            d_scene->addChild(obj);
        }
        
    private:
        cocos2d::Node* d_scene = nullptr;
        const std::string d_name;
        int d_x, d_y;
    };
    
    class EventOneButtonAllow: public Event
    {
    public:
        EventOneButtonAllow(cocos2d::Node* io_scene, const MagicWars_NS::Interface::Button i_but, size_t i_idx): d_scene(io_scene), d_but(i_but), d_idx(i_idx) {}
        
        virtual void throwEvent() override;
        
    private:
        cocos2d::Node* d_scene = nullptr;
        MagicWars_NS::Interface::Button d_but;
        size_t d_idx;
    };
    
    //EventHeap
    class EventHeap: public Event
    {
    public:
        EventHeap(std::list<Event*> i_events): d_events(i_events) {} //cocos2d::log("Heap constructor"); }
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
        EventDialog(const std::string& i_name, const std::list<std::string>& i_message): d_name(i_name), d_message(i_message)
        {}
        
        virtual void throwEvent() override;
        
    protected:
        const std::string d_name;
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
    
    //Event win
    class EventWin: public Event
    {
    public:
        EventWin() = default;
        virtual void throwEvent() override;
    };
    
    //Event lose
    class EventLose: public Event
    {
    public:
        EventLose() = default;
        virtual void throwEvent() override;
    };
    
    //Event loadPersond
    class EventLoadPersons: public Event
    {
    public:
        EventLoadPersons() = default;
        virtual void throwEvent() override;
    };
    
    //EventMove
    class EventMove: public Event
    {
    public:
        EventMove(const std::string& i_name, int i_relX, int i_relY): d_name(i_name), d_x(i_relX), d_y(i_relY) {}
        virtual void throwEvent() override;
        
    protected:
        const std::string d_name;
        int d_x, d_y;
    };
    
    //EventBorn
    class EventBorn: public Event
    {
    public:
        EventBorn(int i_relX, int i_relY, const std::string& i_name, const std::string& i_group, const std::string& i_obj): d_obj(i_obj), d_x(i_relX), d_y(i_relY), d_name(i_name), d_group(i_group) {}
        
        EventBorn(int i_relX, int i_relY, const std::string& i_name, const std::string& i_group, const std::string& i_team, const std::string& i_obj): d_obj(i_obj), d_x(i_relX), d_y(i_relY), d_name(i_name), d_group(i_group), d_team(i_team), d_addToTurn(true) {}
        
        virtual void throwEvent() override;
        
    protected:
        const std::string d_obj;
        int d_x, d_y;
        const std::string d_name, d_group, d_team;
        bool d_addToTurn = false;
    };
    
    class EventKill: public Event
    {
    public:
        EventKill(const std::string& i_obj): d_obj(i_obj) {}
        
        virtual void throwEvent() override;
        
    protected:
        const std::string d_obj;
    };
    
    //EventSpell
    class EventSpell: public Event
    {
    public:
        EventSpell(const std::string& i_name, const std::string& i_spell, int i_relX, int i_relY): d_name(i_name), d_spell(i_spell), d_x(i_relX), d_y(i_relY) {}
        
        virtual void throwEvent() override;
        
    protected:
        const std::string d_name, d_spell;
        int d_x, d_y;
    };
    
    //EventCentralize
    class EventCentralize: public Event
    {
    public:
        EventCentralize(const std::string& i_name): d_name(i_name) {}
        
        virtual void throwEvent() override;
        
    protected:
        const std::string d_name;
    };

}

#endif /* defined(__MagicWars__UIEvent__) */
