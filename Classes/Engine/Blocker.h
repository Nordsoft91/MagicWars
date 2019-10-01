//
//  Blocker.h
//  MagicWars
//
//  Created by nordsoft on 31.10.15.
//
//

#ifndef MagicWars_Blocker_h
#define MagicWars_Blocker_h

//#include <Interface/UIEvent.h>
#include <cocos2d.h>
#include <map>
#include <deque>

namespace UI_NS {
    class Event;
}

namespace MagicWars_NS {
    enum class Pause
    {
        Animation, Interface, Intellect, Message, Map, Tutorial
    };
    
    class Blocker
    {
    private:
        Blocker() = default;
        
        std::map<Pause, std::pair<bool, float>> d_pauseMap;
        
        std::set<cocos2d::Node*> d_activeNodes;
        std::set<UI_NS::Event*> d_activeEvents;
        
        static Blocker& get()
        {
            static Blocker blocker;
            
            return blocker;
        }
        
        static void update()
        {
            for(auto& i : get().d_pauseMap)
                if(i.second.second<=0 && i.second.second>-1)
                {
                    i.second.first = false;
                    i.second.second = -1;
                }
        }
        
    public:
        static void setActive(cocos2d::Node* i_n)
        {
            get().d_activeNodes.insert(i_n);
        }
        
        static const std::set<cocos2d::Node*> getActive() 
        {
            return get().d_activeNodes;
        }
        
        static void resetActive(cocos2d::Node* i_n)
        {
            get().d_activeNodes.erase(i_n);
        }
        
        static void setEvent(UI_NS::Event* i_event)
        {
            get().d_activeEvents.insert(i_event);
        }
        
        static void resetEvent(UI_NS::Event* i_event)
        {
            get().d_activeEvents.erase(i_event);
        }
        
        static bool isLocked()
        {
            return !get().d_activeNodes.empty() || !get().d_activeEvents.empty();
        }
        
        static void block(const Pause& i_p)
        {
            get().d_pauseMap[i_p].first = true;
            get().d_pauseMap[i_p].second = -1;

            switch(i_p)
            {
                case Pause::Animation: cocos2d::log("Pause::Animation - block"); break;
                case Pause::Interface: cocos2d::log("Pause::Interface - block"); break;
                case Pause::Intellect: cocos2d::log("Pause::Intellect - block"); break;
                case Pause::Message: cocos2d::log("Pause::Message - block"); break;
                case Pause::Map: cocos2d::log("Pause::Map - block"); break;
                case Pause::Tutorial: cocos2d::log("Pause::Tutorial - block"); break;
            }
        }
        
        static void block(const Pause& i_p, float i_time)
        {
            get().d_pauseMap[i_p].first = true;
            get().d_pauseMap[i_p].second = i_time;
        }
        
        static void release(const Pause& i_p)
        {
            get().d_pauseMap[i_p].first = false;
            get().d_pauseMap[i_p].second = -1;
            
            switch(i_p)
            {
                case Pause::Animation: cocos2d::log("Pause::Animation - release"); break;
                case Pause::Interface: cocos2d::log("Pause::Interface - release"); break;
                case Pause::Intellect: cocos2d::log("Pause::Intellect - release"); break;
                case Pause::Message: cocos2d::log("Pause::Message - release"); break;
                case Pause::Map: cocos2d::log("Pause::Map - release"); break;
                case Pause::Tutorial: cocos2d::log("Pause::Tutorial - release"); break;
            }
        }
        
        static bool state(const Pause& i_p)
        {
            return get().d_pauseMap[i_p].first;
        }
        
        static bool state()
        {
            for(auto& i : get().d_pauseMap)
                if(i.second.first==true)
                    return true;
            return false;
        }
        
        static bool stateIgnore(const Pause& i_p)
        {
            for(auto& i : get().d_pauseMap)
                if(i.first != i_p && i.second.first==true)
                    return true;
            return false;
        }
        
        static bool stateIgnore(const std::list<Pause>& i_p)
        {
            for(auto& i : get().d_pauseMap)
            {
                if(std::find(i_p.begin(), i_p.end(), i.first) == i_p.end() && i.second.first==true)
                    return true;
            }
            return false;
        }
        
        static void timer( float d_time )
        {
            Blocker& b = get();
            for(auto& i : b.d_pauseMap)
                if(i.second.second>0)
                {
                    i.second.second -= d_time;
                    b.update();
                }
        }
    };
}


#endif
