//
//  Blocker.h
//  MagicWars
//
//  Created by nordsoft on 31.10.15.
//
//

#ifndef MagicWars_Blocker_h
#define MagicWars_Blocker_h

#include <map>

namespace MagicWars_NS {
    enum class Pause
    {
        Animation, Interface, Intellect, Message
    };
    
    class Blocker
    {
    private:
        Blocker() = default;
        
        std::map<Pause, std::pair<bool, float>> d_pauseMap;
        
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
        static void block(const Pause& i_p)
        {
            get().d_pauseMap[i_p].first = true;
            get().d_pauseMap[i_p].second = -1;
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
